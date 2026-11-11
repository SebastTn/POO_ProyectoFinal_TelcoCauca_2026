#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <thread>
#include <functional>

#include "Tecnico.h"
#include "Antena.h"
#include "Torre.h"
#include "ExcepcionNodoRed.h"
#include "NodoRedInteligente.h"
#include "DispositivoComunicacion.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "TareaTransmision.h"
#include "SupervisorRed.h"
#include "EventoIngenieria2027.h"
#include "Registro.h"
#include "SocketCompat.h"
#include "ServidorCentral.h"
#include "ClienteNodo.h"

int main() {
    std::cout << "===== MODULO 1: INFRAESTRUCTURA FISICA =====" << std::endl;
    Tecnico tecnico1(1, "Carlos Mera", "Radiofrecuencia");
    Tecnico tecnico2(2, "Laura Ruiz", "Fibra optica");

    Antena antena1(101, 3500.0, "5G", &tecnico1);
    Antena antena2(102, 1800.0, "4G", &tecnico2);

    Torre torre(1, "Popayan, Cauca", 30.0);
    torre.agregarAntena(&antena1);
    torre.agregarAntena(&antena2);

    tecnico1.mostrarInformacion();
    tecnico2.mostrarInformacion();
    torre.mostrarInformacion();

    std::cout << std::endl << "===== MODULO 2: NODOS INTELIGENTES Y EXCEPCIONES =====" << std::endl;
    try {
        NodoRedInteligente nodoA("192.168.1.10", "AA:BB:CC:DD:EE:01", "Temperatura", 25.5, 40);
        NodoRedInteligente nodoB("192.168.1.11", "AA:BB:CC:DD:EE:02", "Humedad", 60.0, 35);

        std::cout << nodoA << std::endl;
        std::cout << nodoB << std::endl;

        NodoRedInteligente suma = nodoA + nodoB;
        std::cout << "Carga total de procesamiento: " << suma.getCargaProcesamiento() << std::endl;

        NodoRedInteligente nodoMalo("IP-INVALIDA", "AA:BB:CC:DD:EE:03", "Voltaje", 12.0, 10);
        std::cout << nodoMalo << std::endl;
    }
    catch (const ExcepcionNodoRed& e) {
        std::cout << "EXCEPCION NODO RED: " << e.what() << std::endl;
    }

    std::cout << std::endl << "===== MODULO 3: DISPOSITIVOS POLIMORFICOS =====" << std::endl;
    std::vector<DispositivoComunicacion*> red;
    red.push_back(new RouterWiFi("RTR-01", 12, "192.168.10.1"));
    red.push_back(new GatewayLoRa("GW-868", 868.1f, "192.168.10.2"));
    red.push_back(new SwitchFibra("SW-FO-01", 24, "192.168.10.3"));
    red.push_back(nullptr);

    for (std::size_t i = 0; i < red.size(); ++i) {
        try {
            if (red[i] == nullptr) {
                throw std::invalid_argument("ERROR: Puntero nulo en el vector de dispositivos.");
            }
            std::cout << "Dispositivo: " << red[i]->serializar() << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "EXCEPCION: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "===== MODULO 4: HILOS Y EXCLUSION MUTUA =====" << std::endl;
    int transmisionesExitosas = 0;
    int nodosSanos = 0;
    SupervisorRed supervisor;

    std::vector<NodoRedInteligente> nodos;
    nodos.push_back(NodoRedInteligente("192.168.1.10", "AA:BB:CC:DD:EE:01", "Temperatura", 25.5, 40));
    nodos.push_back(NodoRedInteligente("192.168.1.11", "AA:BB:CC:DD:EE:02", "Humedad", 60.0, 35));
    nodos.push_back(NodoRedInteligente("192.168.1.12", "AA:BB:CC:DD:EE:03", "Voltaje", 150.0, 20));

    std::vector<EventoIngenieria2027> agenda;
    agenda.push_back(EventoIngenieria2027("IEEE ANDESCON 2027 (por confirmar)", "Segundo semestre 2027", "Latinoamerica", "Congreso IEEE Region 9"));
    agenda.push_back(EventoIngenieria2027("Congreso ACIEM de Telecomunicaciones", "2027 (por confirmar)", "Colombia", "Congreso nacional de ingenieria"));
    agenda.push_back(EventoIngenieria2027("Simposio de Redes IoT", "2027 (por confirmar)", "Virtual/Presencial", "Redes IoT, LoRaWAN y 5G"));

    std::vector<std::thread> hilos;
    for (std::size_t i = 0; i < red.size(); ++i) {
        hilos.push_back(std::thread(tareaTransmisionHilo, red[i], std::ref(transmisionesExitosas)));
    }
    for (std::size_t i = 0; i < nodos.size(); ++i) {
        hilos.push_back(std::thread(&SupervisorRed::supervisarNodo, &supervisor, &nodos[i], std::ref(nodosSanos)));
    }
    hilos.push_back(std::thread(procesarAgendaEventos2027, std::cref(agenda)));

    for (std::size_t i = 0; i < hilos.size(); ++i) {
        if (hilos[i].joinable()) {
            hilos[i].join();
        }
    }

    registrarEventoSeguro("Transmisiones exitosas: " + std::to_string(transmisionesExitosas));
    registrarEventoSeguro("Nodos supervisados sin errores: " + std::to_string(nodosSanos));

    std::cout << std::endl << "===== MODULO 5: RED CLIENTE-SERVIDOR (TCP/UDP) =====" << std::endl;
    iniciarRed();
    int tramasEnviadas = 0;
    try {
        ServidorCentral servidor(5000, 5001);
        servidor.iniciar();

        ClienteNodo cliente1("NODO-01", "Temperatura", 25.5, 5000, 5001, false);
        ClienteNodo cliente2("NODO-02", "Humedad", 60.0, 5000, 5001, false);
        ClienteNodo cliente3("NODO-03", "Voltaje", 12.0, 5000, 5001, true);

        std::thread hiloServidor(&ServidorCentral::aceptarClientes, &servidor, 3);
        std::thread hiloUDP(&ServidorCentral::recibirTelemetriaUDP, &servidor, 3);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::thread hiloC1(&ClienteNodo::ejecutar, &cliente1, std::ref(tramasEnviadas));
        std::thread hiloC2(&ClienteNodo::ejecutar, &cliente2, std::ref(tramasEnviadas));
        std::thread hiloC3(&ClienteNodo::ejecutar, &cliente3, std::ref(tramasEnviadas));

        hiloC1.join();
        hiloC2.join();
        hiloC3.join();

        hiloServidor.join();
        hiloUDP.join();

        registrarEventoSeguro("Clientes que terminaron su envio: " + std::to_string(tramasEnviadas));
        registrarEventoSeguro("Tramas validas recibidas por el servidor: " + std::to_string(servidor.getTramasRecibidas()));
    }
    catch (const ExcepcionNodoRed& e) {
        registrarEventoSeguro(std::string("EXCEPCION EN RED: ") + e.what());
    }

    finalizarRed();

    // Limpieza de memoria polimorfica
    for (std::size_t i = 0; i < red.size(); ++i) {
        delete red[i];
    }
    red.clear();

    std::cout << "Sistema finalizado correctamente." << std::endl;
    return 0;
}
