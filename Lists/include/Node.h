#ifndef NODE_H
#define NODE_H
#pragma once

#include "Date.h"
#include <string>

// En C++ puro esto suele ser privado, pero para que quede idéntico al
// pseudocódigo del pizarrón (donde escribes N.Info y N.Sig), lo dejamos público.
class Node
{
public:
    Date  Info;         // El dato que guarda el nodo (en este caso, una fecha)
    int   Prioridad;    // 1 = Cola, 2 = Ordenada
    Node* Sig;  // Siguiente
    Node* Ant;  // Anterior

    Node(const Date& v, int p) : Info(v), Prioridad(p), Sig(nullptr), Ant(nullptr) {}

    // Las clases no imprimen
    std::string toString() const {
        return "[P" + std::to_string(Prioridad) + "] " + Info.toString();
    }
    
    // Nos sirve para saber si dos nodos son iguales (misma fecha y prioridad)
    bool equals(const Node* otro) const {
        return otro && Info.equals(otro->Info) && Prioridad == otro->Prioridad;
    }
};

#endif // Final de NODE_H
