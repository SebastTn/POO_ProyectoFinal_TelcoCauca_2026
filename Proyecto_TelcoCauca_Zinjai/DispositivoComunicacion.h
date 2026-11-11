#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"

class DispositivoComunicacion : public ITransmisible {
protected:
    std::string id;
    std::string tipo;
    std::string ip;

public:
    DispositivoComunicacion(const std::string& _id, const std::string& _tipo, const std::string& _ip);
    virtual ~DispositivoComunicacion();
    virtual void transmitir() = 0;
    std::string serializar() const override;
    std::string getId() const;
    std::string getTipo() const;
    std::string getIp() const;
};

#endif
