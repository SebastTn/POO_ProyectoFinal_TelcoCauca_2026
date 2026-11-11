#include "SocketCompat.h"

bool iniciarRed() {
#ifdef _WIN32
    WSADATA datos;
    return WSAStartup(MAKEWORD(2, 2), &datos) == 0;
#else
    return true;
#endif
}

void finalizarRed() {
#ifdef _WIN32
    WSACleanup();
#endif
}

void configurarTimeout(TipoSocket s, int milisegundos) {
#ifdef _WIN32
    DWORD tiempo = milisegundos;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tiempo, sizeof(tiempo));
#else
    struct timeval tiempo;
    tiempo.tv_sec = milisegundos / 1000;
    tiempo.tv_usec = (milisegundos % 1000) * 1000;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tiempo, sizeof(tiempo));
#endif
}

bool esperarConexion(TipoSocket s, int milisegundos) {
    fd_set conjunto;
    FD_ZERO(&conjunto);
    FD_SET(s, &conjunto);
    struct timeval tiempo;
    tiempo.tv_sec = milisegundos / 1000;
    tiempo.tv_usec = (milisegundos % 1000) * 1000;
    int resultado = select((int)s + 1, &conjunto, NULL, NULL, &tiempo);
    return resultado > 0;
}
