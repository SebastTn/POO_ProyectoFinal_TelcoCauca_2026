#ifndef TORRE_H
#define TORRE_H

#include <string>
#include <vector>

class Antena; // Declaracion adelantada (Forward Declaration)

class Torre {
private:
    int idTorre;
    std::string ubicacion;
    double alturaMetros;
    std::vector<Antena*> listaAntenas;

public:
    Torre(int _idTorre, const std::string& _ubicacion, double _alturaMetros);
    ~Torre();
    void agregarAntena(Antena* _antena);
    void mostrarInformacion() const;
};

#endif
