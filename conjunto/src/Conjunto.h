#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Conjunto
{
	public:
		Conjunto();
		~Conjunto();
		bool pertenece(const T&) const;
		void insertar(const T&);
		unsigned int cardinal() const;
		void remover(const T&);
		const T& minimo() const;
		const T& maximo() const;
		const T& siguiente(const T& elem);
	private:
		struct Nodo
		{
			T valor_;
			Nodo* izq_;
			Nodo* der_;
			int cant_;
			Nodo(const T& v);
		};
		Nodo* raiz_;
		//----------------------------------------
		void eliminar(Nodo*);
		bool pertenece_sub(const T&, Nodo*) const;
		int contar(Nodo*) const;
		bool es_hoja(const T&, Nodo*);
		bool es_hijo_izq(const T&);
		Nodo* padre(const T&, Nodo*);
		Nodo* minimo_desde(Nodo*) const;
		Nodo* maximo_desde(Nodo*) const;
};

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
