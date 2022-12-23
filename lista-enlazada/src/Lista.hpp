#include "Lista.h"

Lista::Lista() :
        _inicio(nullptr),
        _fin(nullptr),
        _longitud(0) {}

Lista::Lista(const Lista& l) :
        Lista() {
    *this = l;
}

Lista::~Lista() {
    Nodo* temp = _inicio;
    while(temp != nullptr) {
        temp = _inicio->_siguiente;
        delete _inicio;
        _inicio = temp;
    }
    this->_longitud = 0;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    Nodo* temp = this->_inicio;
    while(temp != nullptr) {
        temp = this->_inicio->_siguiente;
        delete this->_inicio;
        this->_inicio = temp;
    }
    this->_fin = nullptr;
    this->_longitud = 0;
    for(int i = 0; i < aCopiar.longitud(); i++) {
        this->agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* temp = new Nodo;
    temp->_anterior = nullptr;
    temp->_data = elem;
    temp->_siguiente = this->_inicio;
    if(this->_longitud == 0) {
        this->_fin = temp;
    } else {
        this->_inicio->_anterior = temp;
    }
    this->_inicio = temp;
    this->_longitud++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* temp = new Nodo;
    temp->_anterior = this->_fin;
    temp->_data = elem;
    temp->_siguiente = nullptr;
    if(this->_longitud == 0) {
        this->_inicio = temp;
    } else {
        this->_fin->_siguiente = temp;
    }
    this->_fin = temp;
    this->_longitud++;
}

void Lista::eliminar(Nat i) {
    if(this->_longitud == 1) {
        Nodo* temp = this->_inicio;
        this->_inicio = nullptr;
        this->_fin = nullptr;
        delete temp;
    }
    else {
        if(i == 0 || i == this->_longitud - 1) {
            if(i == 0) {
                Nodo* temp = this->_inicio;
                this->_inicio = this->_inicio->_siguiente;
                this->_inicio->_anterior = nullptr;
                delete temp;
            }
            else {
                Nodo* temp = this->_fin;
                this->_fin = this->_fin->_anterior;
                this->_fin->_siguiente = nullptr;
                delete temp;
            }
        }
        else {
            Nodo* temp = this->_inicio;
            for(int j = 0; j != i;  j++) {
                temp = temp->_siguiente;
            }
            temp->_anterior->_siguiente = temp->_siguiente;
            temp->_siguiente->_anterior = temp->_anterior;
            delete temp;
        }
    }
    this->_longitud--;
}

int Lista::longitud() const {
    return this-> _longitud;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* temp = this->_inicio;
    for(int j = 0; j != i;  j++) {
        temp = temp->_siguiente;
    }
    return temp->_data;
    assert(false);
}

int& Lista::iesimo(Nat i) {
    Nodo* temp = this->_inicio;
    for(int j = 0; j != i;  j++) {
        temp = temp->_siguiente;
    }
    return temp->_data;
    assert(false);
}


void Lista::mostrar(std::ostream& o) {
    for(int i = 0; i < this->_longitud; i++) {
        o << this->iesimo(i) << " " ;
    }
}





