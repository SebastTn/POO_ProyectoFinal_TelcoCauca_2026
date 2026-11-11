#include "DispositivoRed.h"

DispositivoRed::DispositivoRed(const std::string& _ip, const std::string& _mac, bool _estado)
    : direccionIP(_ip), direccionMAC(_mac), estadoOperativo(_estado) {}

std::string DispositivoRed::getDireccionIP() const { return direccionIP; }
std::string DispositivoRed::getDireccionMAC() const { return direccionMAC; }
bool DispositivoRed::getEstadoOperativo() const { return estadoOperativo; }
void DispositivoRed::setEstadoOperativo(bool _estado) { estadoOperativo = _estado; }
