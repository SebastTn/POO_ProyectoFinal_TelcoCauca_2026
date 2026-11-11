#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H

#include <string>

class DispositivoRed {
private:
    std::string direccionIP;
    std::string direccionMAC;
    bool estadoOperativo;

public:
    DispositivoRed(const std::string& _ip, const std::string& _mac, bool _estado);
    std::string getDireccionIP() const;
    std::string getDireccionMAC() const;
    bool getEstadoOperativo() const;
    void setEstadoOperativo(bool _estado);
};

#endif
