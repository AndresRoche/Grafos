#ifndef NODOARCO_H
#define NODOARCO_H

#include <iostream>

template <typename T>
class NodoVertice;


/*
 * @brief Clase que representa un arco/arista en el grafo
 * @tparam T Tipo de dato del vertice
 */
template <typename T>
class NodoArco {
    private:
        double peso;             // Peso del arco
        NodoVertice<T>* info;    // Informacion del vertice
        NodoArco<T>* sig;        // Puntero al siguiente arco

    public:
        /**
         * @brief Constructor de la clase
         * @param peso Peso del arco
         * @param info Informacion del vertice
         * @param sig Puntero al siguiente arco
         */
        NodoArco(const double& peso, NodoVertice<T> * info, NodoArco<T> * sig) : peso(peso), info(info), sig(sig) {}

        /**
         * @brief Getters
         */
        inline double getPeso() const { return peso; }
        inline NodoVertice<T> * getInfo() const { return info; }
        inline NodoArco<T> * getSig() const { return sig; }

        /**
         * @brief Setters
         */
        inline void setPeso(const double& peso) { this->peso = peso; }
        inline void setInfo(NodoVertice<T> * info) { this->info = info; }
        inline void setSig(NodoArco<T> * sig) { this->sig = sig; }

        /**
         * @brief Destructor
         */
        ~NodoArco();

        /**
         * @brief Operador de salida para imprimir el arco
         * @param os Stream de salida
         * @param nodo Arco a imprimir
         * @return Referencia al stream de salida
         */
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const NodoArco<U>& nodo);

        /**
         * @brief Operador de comparación para igualdad
         * @param other Otro arco a comparar
         * @return true si los arcos tienen el mismo destino y peso
         */
        inline bool operator==(const NodoArco<T>& other) const;
};

#include "NodoArco.tpp"

#endif // NODOARCO_H
