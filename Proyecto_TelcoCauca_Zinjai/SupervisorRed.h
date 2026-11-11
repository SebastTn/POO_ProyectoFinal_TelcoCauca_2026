#ifndef SUPERVISORRED_H
#define SUPERVISORRED_H

#include "NodoRedInteligente.h"

class SupervisorRed {
public:
    void supervisarNodo(NodoRedInteligente* nodo, int& nodosSanos);
};

#endif
