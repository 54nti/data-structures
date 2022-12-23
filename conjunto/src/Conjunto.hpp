template <class T>
Conjunto<T>::Conjunto() :
        raiz_(nullptr)
{}


template <class T>
Conjunto<T>::~Conjunto()
{
    eliminar(raiz_);
}


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
    return pertenece_sub(clave, raiz_);
}

template <class T>
void Conjunto<T>::insertar(const T& clave)
{
    if(!pertenece(clave))
    {
        if(raiz_ == nullptr)
        {
            raiz_ = new Nodo(clave);
        }
        else
        {
            Nodo* tmp = raiz_;
            while(!(clave < tmp->valor_ and tmp->izq_ == nullptr)  and
                  !(clave > tmp->valor_ and tmp->der_ == nullptr))
            {
                if(clave < tmp->valor_)
                {
                    tmp->cant_++;
                    tmp = tmp->izq_;
                }
                else
                {
                    tmp->cant_++;
                    tmp = tmp->der_;
                }
            }
            if(clave < tmp->valor_)
            {
                tmp->cant_++;
                tmp->izq_ = new Nodo(clave);
            }
            else
            {
                tmp->cant_++;
                tmp->der_ = new Nodo(clave);
            }
        }
    }
}


template <class T>
unsigned int Conjunto<T>::cardinal() const
{
    int c = 0;
    if(raiz_ != nullptr)
    {
        c = contar(raiz_);
    }
    unsigned int d = 0;
    d = (unsigned int)c;
    return d;
}

template <class T>
void Conjunto<T>::remover(const T& clave)
{
    if(cardinal() == 1 and pertenece(clave))
    {
        delete(raiz_);
        raiz_ = nullptr;
    }
    if(1 < cardinal() and pertenece(clave))
    {
        if(es_hoja(clave, raiz_))
        {
            if(es_hijo_izq(clave))
            {
                Nodo* alias = padre(clave, raiz_)->izq_;
                padre(clave, raiz_)->izq_ = nullptr;
                delete alias;
            }
            else
            {
                Nodo* alias = padre(clave, raiz_)->der_;
                padre(clave, raiz_)->der_ = nullptr;
                delete alias;
            }
        }
        else
        {
            Nodo* alias = raiz_;
            while(alias->valor_ != clave)
            {
                if(clave < alias->valor_)
                {
                    alias = alias->izq_;
                }
                else
                {
                    alias = alias->der_;
                }
            }
            if(alias->izq_ != nullptr)
            {
                Nodo* tmp = maximo_desde(alias->izq_);
                if( tmp == alias->izq_)
                {
                    alias->izq_ = tmp->izq_;
                }
                else
                {
                    padre(tmp->valor_, alias)->der_ = tmp->izq_;
                }
                alias->valor_ = tmp->valor_;
                delete tmp;
            }
            else
            {
                Nodo* tmp = minimo_desde(alias->der_);
                if( tmp == alias->der_)
                {
                    alias->der_ = tmp->der_;
                }
                else
                {
                    padre(tmp->valor_, alias)->izq_ = tmp->der_;
                }
                alias->valor_ = tmp->valor_;
                delete tmp;
            }
        }
    }
}


template <class T>
const T& Conjunto<T>::minimo() const
{
    Nodo* p = minimo_desde(raiz_);
    return p->valor_;
}


template <class T>
const T& Conjunto<T>::maximo() const
{
    Nodo* p = maximo_desde(raiz_);
    return p->valor_;
}


template <class T>
const T& Conjunto<T>::siguiente(const T& clave)
{
    Nodo* tmp = raiz_;
    while(tmp->valor_ != clave)
    {
        if(clave < tmp->valor_)
        {
            tmp = tmp->izq_;
        }
        else
        {
            tmp = tmp->der_;
        }
    }
    if(tmp->der_ != nullptr)
    {
        tmp = minimo_desde(tmp->der_);
    }
    else
    {
        while(!es_hijo_izq(tmp->valor_))
        {
            tmp = padre(tmp->valor_, raiz_);
        }
        tmp = padre(tmp->valor_, raiz_);
    }
    return tmp->valor_;
}


//--------------------------------------------------

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v) :
        valor_(v),
        izq_(nullptr),
        der_(nullptr),
        cant_(0)
{}


template <class T>
void Conjunto<T>::eliminar(Nodo* p)
{
    if(p != nullptr)
    {
        eliminar(p->izq_);
        eliminar(p->der_);
        delete p;
    }
}


template <class T>
bool Conjunto<T>::pertenece_sub(const T& clave, Nodo* p) const
{
    bool in = false;
    if(p != nullptr)
    {
        in = p->valor_ == clave;
        if(p->izq_ != nullptr)
        {
            in = in or pertenece_sub(clave, p->izq_);
        }
        if(p->der_ != nullptr)
        {
            in = in or pertenece_sub(clave, p->der_);
        }
    }
    return in;
}


template <class T>
int Conjunto<T>::contar(Nodo* p) const
{
    int  c = 0;
    if(p->izq_ == nullptr and p->der_ == nullptr)
    {
        return 1;
    }
    else
    {
        c++;
        if(p->izq_ != nullptr)
        {
            c += contar(p->izq_);
        }
        if(p->der_ != nullptr)
        {
            c += contar(p->der_);
        }
    }
    return c;
}


template <class T>
bool Conjunto<T>::es_hoja(const T& clave, Nodo* p)
{
    while(p->valor_ != clave)
    {
        if(clave < p->valor_)
        {
            p = p->izq_;
        }
        else
        {
            p = p->der_;
        }
    }
    return (p->izq_ == nullptr) and (p->der_ == nullptr);
}


template <class T>
bool Conjunto<T>::es_hijo_izq(const T& clave)
{
    return (padre(clave, raiz_)->izq_ != nullptr) and
           (padre(clave, raiz_)->izq_->valor_ == clave);
}


template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::padre(const T& clave, Nodo* p)
{
    while(p->izq_ != nullptr or p->der_ != nullptr)
    {
        if(p->izq_ != nullptr)
        {
            if(p->izq_->valor_ == clave)
            {
                return p;
            }
        }
        if(p->der_ != nullptr)
        {
            if(p->der_->valor_ == clave)
            {
                return p;
            }
        }
        if(clave < p->valor_)
        {
            p = p->izq_;
        }
        else
        {
            p = p->der_;
        }
    }
    return p;
}


template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::minimo_desde(Nodo* p) const
{
    while(p->izq_ != nullptr)
    {
        p = p->izq_;
    }
    return p;
}


template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::maximo_desde(Nodo* p) const
{
    while(p->der_ != nullptr)
    {
        p = p->der_;
    }
    return p;
}









