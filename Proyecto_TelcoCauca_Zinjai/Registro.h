#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <mutex>

extern std::mutex mtx_consola;
extern std::mutex mtx_contador;

void registrarEventoSeguro(const std::string& mensaje);

#endif
