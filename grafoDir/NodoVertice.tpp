

template<typename U>
std::ostream& operator<<(std::ostream& os, const NodoVertice<U>& nodo) {
    os << "NodoVertice[" << nodo.info << "]\n";
    os << " -> arco: [" << nodo.arco << "]\n";
    os << " -> sig: [" << nodo.sig << "]\n";
    return os;
}


template<typename U>
bool NodoVertice<U>::operator==(const NodoVertice<U>& other) const {
    return this->info == other.info;
}

template<typename T>
NodoVertice<T>::~NodoVertice() {}


template <typename T>
NodoArco<T>& NodoVertice<T>::operator[](int index)
{
    if (index < 0)
        throw std::runtime_error("Índice no puede ser negativo");
    
    int i = 0;
    NodoArco<T>* current = this->arco;
    while (current != NULL) {
        if (i == index)
            return *current;
        i++;
        current = current->getSig();
    }
    throw std::runtime_error("Índice fuera de rango");
}
