

template<typename U>
std::ostream& operator<<(std::ostream& os, const NodoArco<U>& nodo)
{
    os << "NodoArco[" << nodo.info << "]\n";
    os << " -> peso: [" << nodo.peso << "]\n";
    os << " -> sig: [" << nodo.sig << "]\n";
    return os;
}

template<typename T>
inline bool NodoArco<T>::operator==(const NodoArco<T>& other) const
{
    return this->info == other.info && this->peso == other.peso;
}

template<typename T>
NodoArco<T>::~NodoArco() {}

