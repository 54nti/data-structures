template<class T>
ColaPrior<T>::ColaPrior()
: _elems(0), _tam(0) {}

template<class T>
int ColaPrior<T>::tam() const {
	return _tam;
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
    _elems.push_back(elem);
    _tam++;
    subir(_tam-1);
}

template<class T>
const T& ColaPrior<T>::proximo() const {
    return _elems[0];
}

template<class T>
void ColaPrior<T>::desencolar() {
    _elems[0] = _elems[_elems.size() - 1];
    _elems.pop_back();
    _tam--;
    bajar(0);
}

/*
template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems) {}
*/

// --------------------------------------------------------------------------------

template<class T>
void ColaPrior<T>::subir(int index) {
    T e = _elems[index];
    while(index != 0 and _elems[padre(index)] < e) {
        intercambiar(index, padre(index));
        index = padre(index);
    }
}

template<class T>
T ColaPrior<T>::padre(int index) {
    return (index-1)/2;
}

template<class T>
void ColaPrior<T>::intercambiar(int index, int pindex) {
    T temp = _elems[index];
    _elems[index] = _elems[pindex];
    _elems[pindex] = temp;
}

/*
template<class T>
void ColaPrior<T>::bajar(int index) {
    if(!hoja(index)) {
        if(tiene_hijo_der(index) && (_elems[hijo_izq(index)] < _elems[hijo_der(index)])) {
            intercambiar(index, hijo_der(index));
            index = hijo_der(index);
            bajar(index);
        }
        else {
            if(_elems[index] < _elems[hijo_izq(index)]) {
                intercambiar(index, hijo_izq(index));
                index = hijo_izq(index);
                bajar(index);
            }
        }
    }
}
*/

template<class T>
bool ColaPrior<T>::hoja(int index) {
    return _elems.size() <= ((index*2)+1);
}

template<class T>
bool ColaPrior<T>::tiene_hijo_der(int index) {
    return ((index*2)+2) <= (_elems.size() - 1);
}

template<class T>
int ColaPrior<T>::hijo_izq(int index) {
    return (index*2)+1;
}

template<class T>
int ColaPrior<T>::hijo_der(int index) {
    return (index*2)+2;
}


template<class T>
void ColaPrior<T>::bajar(int index) {
    while(!hoja(index) && tiene_hijo_mayor(index)) {
        if(tiene_hijo_der(index) && (_elems[hijo_izq(index)] < _elems[hijo_der(index)])) {
            intercambiar(index, hijo_der(index));
            index = hijo_der(index);
        }
        else {
            /* do not check because in the while we already know that
             * we have a greater node below
            if(_elems[index] < _elems[hijo_izq(index)]) {
                intercambiar(index, hijo_izq(index));
                index = hijo_izq(index);
            }
             */
            intercambiar(index, hijo_izq(index));
            index = hijo_izq(index);
        }
    }
}

template<class T>
bool ColaPrior<T>::tiene_hijo_mayor(int index) {
    return (tiene_hijo_der(index) && (_elems[index] < _elems[hijo_der(index)]))
            or
            (_elems[index] < _elems[hijo_izq(index)]);
}





