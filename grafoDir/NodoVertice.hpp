#ifndef NODOVERTICE_H
#define NODOVERTICE_H

#include <iostream>

template <typename T>
class NodoArco;



/*
 * @brief Clase que representa un vertice en el grafo
 * @tparam T Tipo de dato del vertice
 */
template <typename T>
class NodoVertice {
    private:
        T info;                      // Informacion del vertice
        NodoVertice<T> * sig;        // Puntero al siguiente vertice
        NodoArco<T> * arco;          // Puntero al arco del vertice

    public:
        /**
         * @brief Constructor de la clase
         * @param info Informacion del vertice
         * @param sig Puntero al siguiente vertice
         * @param arco Puntero al arco del vertice
         */
        NodoVertice(const T& info, NodoVertice<T> * sig, NodoArco<T> * arco) : info(info), sig(sig), arco(arco) {}

        /**
         * @brief Getters
         */
        inline T getInfo() const { return info; }
        inline NodoVertice<T> * getSig() const { return sig; }
        inline NodoArco<T> * getArco() const { return arco; }

        /**
         * @brief Setters
         */
        inline void setInfo(const T& info) { this->info = info; }
        inline void setSig(NodoVertice<T> * sig) { this->sig = sig; }
        inline void setArco(NodoArco<T> * arco) { this->arco = arco; }

        /**
         * @brief Destructor
         */
        ~NodoVertice();
        
        /**
         * @brief Operador de salida para imprimir el vertice
         * @param os Stream de salida
         * @param nodo Vertice a imprimir
         * @return Referencia al stream de salida
         */
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const NodoVertice<U>& nodo);


        /**
         * @brief Operador de comparación para igualdad
         * @param other Otro arco a comparar
         * @return true si los arcos tienen el mismo destino y peso
         */
        inline bool operator==(const NodoVertice<T>& other) const;

        /**
         * @brief Operador de [] para obtener los arcos adyacentes
         * @param index Índice del arco a obtener
         * @return Referencia al arco en la posición index
         * @throw std::runtime_error Si el índice es inválido
         */
        NodoArco<T>& operator[](int index);
};

#include "NodoVertice.tpp"


#endif // NODOVERTICE_H
