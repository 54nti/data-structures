#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

template<typename T>
class string_map
{
public:
    string_map();
    string_map(const string_map<T>& aCopiar);
    string_map& operator=(const string_map& d);
    ~string_map();
    int count(const string &key) const;
    void insert(const pair<string, T>&);
    const T& at(const string& key) const;
    T& at(const string& key);
    void erase(const string& key);
    int size() const;
    bool empty() const;

private:
    struct Nodo
    {
        vector<Nodo*> _siguientes;
        T* _definicion;
        Nodo();
        Nodo(T*);
    };
    Nodo* _raiz;
    int _size;
    //-----------------------------
    void limpiar(Nodo*);
    void copiar(Nodo*, Nodo*);
    Nodo* buscar_def(const string&);
    bool unico_caracter(vector<Nodo*>&);
    bool comparte_hacia_abj(string);
};

#include "string_map.hpp"

#endif // STRING_MAP_H_