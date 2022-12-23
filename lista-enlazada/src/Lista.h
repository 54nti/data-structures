#ifndef _LISTA_ALUMNOS_H_
#define _LISTA_ALUMNOS_H_

#include <iostream>
#include <string>
#include <ostream>

typedef unsigned long Nat;

class Lista {
public:
    Lista();
    Lista(const Lista& l);
    ~Lista();
    Lista& operator=(const Lista& aCopiar);
    void agregarAdelante(const int& elem);
    void agregarAtras(const int& elem);
    void eliminar(Nat i);
    int longitud() const;
    const int& iesimo(Nat i) const;
    int& iesimo(Nat i);
    void mostrar(std::ostream& o);
    friend std::ostream& operator<<(std::ostream& os, Lista& l) {
        l.mostrar(os);
        return os;
    }
private:
    struct Nodo {
        Nodo* _anterior;
        int _data;
        Nodo* _siguiente;
    };
    Nodo* _inicio;
    Nodo* _fin;
    int _longitud;
};

#include "Lista.hpp"

#endif





