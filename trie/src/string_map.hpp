template <typename T>
string_map<T>::string_map():
        _raiz(nullptr),
        _size(0)
{}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar):
        string_map()
{
    *this = aCopiar;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d)
{
    if(d._raiz != nullptr)
    {
        _raiz = new Nodo();
        Nodo* p = d._raiz;
        Nodo* q = _raiz;
        copiar(p, q);
    }
    _size = d._size;
    return *this;
}

template <typename T>
string_map<T>::~string_map()
{
    limpiar(_raiz);
}

template <typename T>
int string_map<T>::count(const string& key) const
{
    Nodo* p = _raiz;
    unsigned int i = 0;
    while(i < key.length() and p != nullptr)
    {
        p = p->_siguientes[(int)key[i]];
        i++;
    }
    return (i == key.length()) and (p != nullptr) and (p->_definicion != nullptr);
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& cv)
{
    string c = cv.first;  // evitar la copia
    if(count(c) == 0)
    {
        if(_raiz == nullptr)
        {
            _raiz = new Nodo();
        }
        Nodo* p = _raiz;
        for( unsigned int i = 0; i < c.length(); i++)
        {
            if(p->_siguientes[(int)c[i]] == nullptr)
            {
                p->_siguientes[(int)c[i]] = new Nodo();
            }
            p = p->_siguientes[(int)c[i]];
        }
        p->_definicion = new T(cv.second);
        _size++;
    }
    else
    {
        Nodo* p = _raiz;
        for(unsigned int i = 0; i < c.length(); i++)
        {
            p = p->_siguientes[(int)c[i]];
        }
        delete p->_definicion;
        p->_definicion = new T(cv.second);
    }
}

template <typename T>
const T& string_map<T>::at(const string& key) const
{
    Nodo* p = _raiz;
    for(unsigned int i = 0; i < key.length(); i++)
    {
        p = p->_siguientes[(int)key[i]];
    }
    return *(p->_definicion);
}

template <typename T>
T& string_map<T>::at(const string& key)
{
    Nodo* p = _raiz;
    for(unsigned int i = 0; i < key.length(); i++)
    {
        p = p->_siguientes[(int)key[i]];
    }
    return *(p->_definicion);
}

template <typename T>
void string_map<T>::erase(const string& key)
{
    Nodo* p = _raiz;
    if(_size == 1)
    {
        _raiz = nullptr;
        limpiar(p);
    }
    else
    {
        if(comparte_hacia_abj(key))
        {
            p = buscar_def(key);
            delete p->_definicion;
            p->_definicion = nullptr;
        }
        else
        {
            Nodo* q = _raiz;
            int c = 0;
            for(unsigned int i = 0; i < key.length() - 1; i++)
            {
                if(p->_definicion != nullptr or !unico_caracter(p->_siguientes))
                {
                    q = p;
                    c = (int)key[i];
                }
                p = p->_siguientes[(int)key[i]];
            }
            limpiar(q->_siguientes[c]);
            q->_siguientes[c] = nullptr;
        }
    }
    _size--;
}

template <typename T>
int string_map<T>::size() const
{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const
{
    return _size == 0;
}

//-----------------------------------------------

template <typename T>
string_map<T>::Nodo::Nodo():
        _siguientes(256, nullptr),
        _definicion(nullptr)
{}

template <typename T>
string_map<T>::Nodo::Nodo(T* valor):
        _siguientes(256, nullptr),
        _definicion(valor)
{}

template <typename T>
void string_map<T>::limpiar(Nodo* p)
{
    if(p != nullptr)
    {
        for(unsigned int i = 0; i < p->_siguientes.size(); i++)
        {
            if(p->_siguientes[i] != nullptr)
            {
                limpiar(p->_siguientes[i]);
            }
        }
        if(p->_definicion != nullptr)
        {
            delete p->_definicion;
        }
        delete p;
    }
}

template <typename T>
void string_map<T>::copiar(Nodo* ro, Nodo* rc)
{
    for(unsigned int i = 0; i < ro->_siguientes.size(); i++)
    {
        if(ro->_siguientes[i] != nullptr)
        {
            if(ro->_siguientes[i]->_definicion != nullptr)
            {
                T* v = new T(*(ro->_siguientes[i]->_definicion));
                rc->_siguientes[i] = new Nodo(v);
            }
            else
            {
                rc->_siguientes[i] = new Nodo();
            }
            copiar(ro->_siguientes[i], rc->_siguientes[i]);
        }
    }
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::buscar_def(const string& clave)
{
    Nodo* p = _raiz;
    for(unsigned int i = 0; i < clave.length(); i++)
    {
        p = p->_siguientes[(int)clave[i]];
    }
    return p;
}

template <typename T>
bool string_map<T>::comparte_hacia_abj(string clave)
{
    Nodo* p = _raiz;
    for(unsigned int i = 0; i < clave.length(); i++)
    {
        p = p->_siguientes[(int)clave[i]];
    }
    int contador = 0;
    for(unsigned int i = 0; i < p->_siguientes.size(); i++)
    {
        if(p->_siguientes[i] != nullptr)
        {
            contador++;
        }
    }
    return contador == 0 ? false : true;
}

template<typename T>
bool string_map<T>::unico_caracter(vector<Nodo*>& v)
{
    int contador = 0;
    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(v[i] != nullptr)
        {
            contador++;
        }
    }
    return contador == 1;
}


