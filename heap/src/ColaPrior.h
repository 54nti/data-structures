#ifndef _COLAPRIOR_H_
#define _COLAPRIOR_H_

#include <vector>

using namespace std;

template<class T>
class ColaPrior {
    public:
        ColaPrior();
        int tam() const;
        //ColaPrior(const vector<T>& elems);
        void encolar(const T& elem);
        const T& proximo() const;
        //void desencolar();
    private:
        vector<T> _elems;
        int _tam;
        //------------------------------
        void subir(int);
        T padre(int);
        void intercambiar(int, int);
};

#include "ColaPrior.cpp"

#endif /*_COLAPRIOR_H_*/
