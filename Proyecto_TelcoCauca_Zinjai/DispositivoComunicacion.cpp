#include "DispositivoComunicacion.h"

DispositivoComunicacion::DispositivoComunicacion(const std::string& _id, const std::string& _tipo, const std::string& _ip)
    : id(_id), tipo(_tipo), ip(_ip) {}

DispositivoComunicacion::~DispositivoComunicacion() {}

std::string DispositivoComunicacion::serializar() const {
    return id + "|" + tipo + "|" + ip;
}

std::string DispositivoComunicacion::getId() const { return id; }
std::string DispositivoComunicacion::getTipo() const { return tipo; }
std::string DispositivoComunicacion::getIp() const { return ip; }
