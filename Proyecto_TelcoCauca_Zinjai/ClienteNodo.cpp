#include "ClienteNodo.h"
#include "SocketCompat.h"
#include "ExcepcionNodoRed.h"
#include "Trama.h"
#include "Registro.h"
#include <cstring>
#include <mutex>

ClienteNodo::ClienteNodo(const std::string& _idNodo, const std::string& _tipoSensor, double _valor,
                         int _puertoTCP, int _puertoUDP, bool _tramaCorrupta)
    : idNodo(_idNodo), tipoSensor(_tipoSensor), valor(_valor),
      puertoTCP(_puertoTCP), puertoUDP(_puertoUDP), tramaCorrupta(_tramaCorrupta) {}

void ClienteNodo::ejecutar(int& tramasEnviadas) {
    TipoSocket socketTCP = SOCKET_INVALIDO;
    TipoSocket socketUDP = SOCKET_INVALIDO;
    try {
        sockaddr_in servidor;
        std::memset(&servidor, 0, sizeof(servidor));
        servidor.sin_family = AF_INET;
        servidor.sin_addr.s_addr = inet_addr("127.0.0.1");

        socketTCP = socket(AF_INET, SOCK_STREAM, 0);
        if (socketTCP == SOCKET_INVALIDO) {
            throw ExcepcionNodoRed("No se pudo crear el socket TCP del cliente.");
        }
        servidor.sin_port = htons(puertoTCP);
        if (connect(socketTCP, (sockaddr*)&servidor, sizeof(servidor)) != 0) {
            throw ExcepcionNodoRed("connect() fallo en el cliente " + idNodo);
        }
        registrarEventoSeguro("Cliente " + idNodo + " conectado al servidor");

        Trama tramaValida(idNodo, tipoSensor, valor);
        std::string msg1 = tramaValida.serializar();
        send(socketTCP, msg1.c_str(), msg1.size(), 0);
        char respBuffer[32];
        int bytes = recv(socketTCP, respBuffer, sizeof(respBuffer) - 1, 0);
        if (bytes > 0) {
            respBuffer[bytes] = '\0';
            registrarEventoSeguro("Cliente " + idNodo + " recibio respuesta: " + std::string(respBuffer));
        }

        std::string msg2 = tramaCorrupta ? "TRAMA-DANADA" : Trama(idNodo, tipoSensor, valor + 1.0).serializar();
        send(socketTCP, msg2.c_str(), msg2.size(), 0);
        bytes = recv(socketTCP, respBuffer, sizeof(respBuffer) - 1, 0);
        if (bytes > 0) {
            respBuffer[bytes] = '\0';
            registrarEventoSeguro("Cliente " + idNodo + " recibio respuesta: " + std::string(respBuffer));
        }

        socketUDP = socket(AF_INET, SOCK_DGRAM, 0);
        if (socketUDP != SOCKET_INVALIDO) {
            servidor.sin_port = htons(puertoUDP);
            Trama tramaUDP(idNodo, tipoSensor, valor + 10.0);
            std::string msgUDP = tramaUDP.serializar();
            sendto(socketUDP, msgUDP.c_str(), msgUDP.size(), 0, (sockaddr*)&servidor, sizeof(servidor));
            registrarEventoSeguro("Cliente " + idNodo + " envio telemetria UDP");
        }

        {
            std::lock_guard<std::mutex> lock(mtx_contador);
            ++tramasEnviadas;
        }
    }
    catch (const ExcepcionNodoRed& e) {
        registrarEventoSeguro("EXCEPCION CLIENTE: " + std::string(e.what()));
    }
    catch (const std::exception& e) {
        registrarEventoSeguro("EXCEPCION CLIENTE EN HILO: " + std::string(e.what()));
    }

    if (socketTCP != SOCKET_INVALIDO) CERRAR_SOCKET(socketTCP);
    if (socketUDP != SOCKET_INVALIDO) CERRAR_SOCKET(socketUDP);
}
