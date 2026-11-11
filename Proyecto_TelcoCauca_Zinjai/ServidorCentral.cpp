#include "ServidorCentral.h"
#include "ExcepcionNodoRed.h"
#include "Trama.h"
#include "Registro.h"
#include <cstring>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

ServidorCentral::ServidorCentral(int _puertoTCP, int _puertoUDP)
    : puertoTCP(_puertoTCP), puertoUDP(_puertoUDP),
      socketTCP(SOCKET_INVALIDO), socketUDP(SOCKET_INVALIDO), tramasRecibidas(0) {}

ServidorCentral::~ServidorCentral() {
    if (socketTCP != SOCKET_INVALIDO) CERRAR_SOCKET(socketTCP);
    if (socketUDP != SOCKET_INVALIDO) CERRAR_SOCKET(socketUDP);
}

void ServidorCentral::iniciar() {
    sockaddr_in direccion;
    std::memset(&direccion, 0, sizeof(direccion));
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = inet_addr("127.0.0.1");
    int opcion = 1;

    socketTCP = socket(AF_INET, SOCK_STREAM, 0);
    if (socketTCP == SOCKET_INVALIDO) {
        throw ExcepcionNodoRed("No se pudo crear el socket TCP del servidor.");
    }
    setsockopt(socketTCP, SOL_SOCKET, SO_REUSEADDR, (const char*)&opcion, sizeof(opcion));
    direccion.sin_port = htons(puertoTCP);

    if (bind(socketTCP, (sockaddr*)&direccion, sizeof(direccion)) != 0) {
        throw ExcepcionNodoRed("bind() fallo en el puerto TCP " + std::to_string(puertoTCP));
    }

    if (listen(socketTCP, 5) != 0) {
        throw ExcepcionNodoRed("listen() fallo en el puerto TCP " + std::to_string(puertoTCP));
    }
    registrarEventoSeguro("Servidor TCP escuchando en el puerto " + std::to_string(puertoTCP));

    socketUDP = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketUDP == SOCKET_INVALIDO) {
        throw ExcepcionNodoRed("No se pudo crear el socket UDP del servidor.");
    }
    direccion.sin_port = htons(puertoUDP);

    if (bind(socketUDP, (sockaddr*)&direccion, sizeof(direccion)) != 0) {
        throw ExcepcionNodoRed("bind() fallo en el puerto UDP " + std::to_string(puertoUDP));
    }
    configurarTimeout(socketUDP, 3000);
    registrarEventoSeguro("Servidor UDP listo en el puerto " + std::to_string(puertoUDP));
}

void ServidorCentral::aceptarClientes(int cantidad) {
    std::vector<std::thread> hilosClientes;
    try {
        for (int i = 0; i < cantidad; ++i) {
            if (!esperarConexion(socketTCP, 5000)) {
                registrarEventoSeguro("Servidor: tiempo de espera agotado esperando clientes.");
                break;
            }
            TipoSocket cliente = accept(socketTCP, NULL, NULL);
            if (cliente == SOCKET_INVALIDO) {
                throw ExcepcionNodoRed("accept() fallo en el servidor.");
            }
            hilosClientes.push_back(std::thread(&ServidorCentral::atenderCliente, this, cliente));
        }
    }
    catch (const ExcepcionNodoRed& e) {
        registrarEventoSeguro(std::string("EXCEPCION EN SERVIDOR: ") + e.what());
    }
    catch (const std::exception& e) {
        registrarEventoSeguro(std::string("EXCEPCION EN HILO: ") + e.what());
    }

    for (std::size_t i = 0; i < hilosClientes.size(); ++i) {
        if (hilosClientes[i].joinable()) {
            hilosClientes[i].join();
        }
    }
}

void ServidorCentral::atenderCliente(TipoSocket cliente) {
    configurarTimeout(cliente, 3000);
    char buffer[256];
    int bytes = recv(cliente, buffer, sizeof(buffer) - 1, 0);
    while (bytes > 0) {
        buffer[bytes] = '\0';
        std::string texto(buffer);
        try {
            Trama trama = Trama::deserializar(texto);
            registrarEventoSeguro("Servidor recibio trama TCP: " + trama.resumen());
            {
                std::lock_guard<std::mutex> lock(mtx_contador);
                ++tramasRecibidas;
            }
            send(cliente, "ACK", 3, 0);
        }
        catch (const ExcepcionNodoRed& e) {
            registrarEventoSeguro(std::string("EXCEPCION EN SERVIDOR: ") + e.what());
            send(cliente, "ERROR", 5, 0);
        }
        catch (const std::exception& e) {
            registrarEventoSeguro(std::string("EXCEPCION EN HILO: ") + e.what());
        }
        bytes = recv(cliente, buffer, sizeof(buffer) - 1, 0);
    }
    CERRAR_SOCKET(cliente);
}

void ServidorCentral::recibirTelemetriaUDP(int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        char buffer[256];
        sockaddr_in origen;
        LongitudDireccion tamanio = sizeof(origen);
        int bytes = recvfrom(socketUDP, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&origen, &tamanio);
        if (bytes <= 0) {
            registrarEventoSeguro("Servidor: tiempo de espera agotado en UDP.");
            break;
        }
        buffer[bytes] = '\0';
        std::string texto(buffer);
        try {
            Trama trama = Trama::deserializar(texto);
            registrarEventoSeguro("Servidor recibio telemetria UDP: " + trama.resumen());
            std::lock_guard<std::mutex> lock(mtx_contador);
            ++tramasRecibidas;
        }
        catch (const ExcepcionNodoRed& e) {
            registrarEventoSeguro(std::string("EXCEPCION EN SERVIDOR: ") + e.what());
        }
        catch (const std::exception& e) {
            registrarEventoSeguro(std::string("EXCEPCION EN HILO: ") + e.what());
        }
    }
}

int ServidorCentral::getTramasRecibidas() const { return tramasRecibidas; }
