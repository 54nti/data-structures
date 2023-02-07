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

/*
template<class T>
void ColaPrior<T>::desencolar() {}

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
