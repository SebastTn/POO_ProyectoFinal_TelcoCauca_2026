#ifndef SOCKETCOMPAT_H
#define SOCKETCOMPAT_H

#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET TipoSocket;
typedef int LongitudDireccion;
#define SOCKET_INVALIDO INVALID_SOCKET
#define CERRAR_SOCKET closesocket
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int TipoSocket;
typedef socklen_t LongitudDireccion;
#define SOCKET_INVALIDO (-1)
#define CERRAR_SOCKET close
#endif

bool iniciarRed();
void finalizarRed();
void configurarTimeout(TipoSocket s, int milisegundos);
bool esperarConexion(TipoSocket s, int milisegundos);

#endif
