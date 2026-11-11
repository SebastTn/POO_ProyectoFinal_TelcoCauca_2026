#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"

static bool ipValida(const std::string& ip) {
    if (ip.empty()) return false;
    int puntos = 0;
    for (std::size_t i = 0; i < ip.size(); ++i) {
        if (ip[i] == '.') ++puntos;
        else if (ip[i] < '0' || ip[i] > '9') return false;
    }
    return puntos == 3;
}

NodoRedInteligente::NodoRedInteligente(const std::string& _ip, const std::string& _mac,
                                       const std::string& _tipoSensor, double _valor, int _carga)
    : DispositivoRed(_ip, _mac, true), SensorIoT(_tipoSensor, _valor), cargaProcesamiento(_carga) {
    if (!ipValida(_ip)) {
        throw ExcepcionNodoRed("Direccion IP invalida: " + _ip);
    }
}

int NodoRedInteligente::getCargaProcesamiento() const { return cargaProcesamiento; }

void NodoRedInteligente::verificarLectura() const {
    double valor = getValorLectura();
    if (valor < 0.0 || valor > 100.0) {
        throw ExcepcionNodoRed("Lectura fuera de rango (0 a 100) en el nodo " + getDireccionIP() + ": " + std::to_string(valor));
    }
}

NodoRedInteligente NodoRedInteligente::operator+(const NodoRedInteligente& otro) const {
    return NodoRedInteligente(getDireccionIP(), getDireccionMAC(), getTipoSensor(),
                               getValorLectura(), cargaProcesamiento + otro.cargaProcesamiento);
}

std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& nodo) {
    os << "Nodo [IP: " << nodo.getDireccionIP()
       << " | MAC: " << nodo.getDireccionMAC()
       << " | Sensor: " << nodo.getTipoSensor()
       << " | Lectura: " << nodo.getValorLectura()
       << " | Carga: " << nodo.cargaProcesamiento << "]";
    return os;
}
