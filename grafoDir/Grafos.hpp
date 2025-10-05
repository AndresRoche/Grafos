#ifndef GRAFOS_HPP
#define GRAFOS_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <map>
#include <queue>
#include "NodoVertice.hpp"
#include "NodoArco.hpp"


/* 
 * @brief Clase que representa un grafo
 * @tparam T Tipo de dato del vertice
 */
template <typename T>
class Grafos {

    protected:
        NodoVertice<T> * primerVertice;     // Puntero al primer vertice
        int nVertices;                       // Numero de vertices
        int nArcos;                          // Numero de arcos

        /** 
         * @brief Busca un vertice y lo retorna, Si no lo encuentra lanza una excepcion
         * @param info Informacion del vertice
         * @return Puntero al vertice
         */
        NodoVertice<T> * irVertice(const T& info) const;

        /** 
         * @brief Busca los dos vertices y los retorna en un vector, Si no lo encuentra lanza una excepcion
         * @param origen Informacion del vertice origen
         * @return Vector de vertices
         */
        std::vector<NodoVertice<T>*>  irDosVertices(const T& origen, const T& destino);

        /**
         * @brief Helper DFS recursivo
         */
        void DFS(T verticeInicio, std::vector<T> &result, std::map<T,bool> &visitado);


    public:

        /**
         * @brief Constructor
         */
        Grafos() : primerVertice(NULL), nVertices(0), nArcos(0) {}

        /**
         * @brief Constructor de copia
         */
        Grafos(const Grafos<T>& other);

        /* setters */
        void setPrimerVertice(NodoVertice<T> *primerVertice) { this->primerVertice = primerVertice; }
        void setNVertices(int nVertices) { this->nVertices = nVertices; }
        void setNArcos(int nArcos) { this->nArcos = nArcos; }

        /* getters */
        NodoVertice<T> * getPrimerVertice() const { return this->primerVertice; }
        int getNVertices() const { return this->nVertices; }
        int getNArcos() const { return this->nArcos; }

        /**
         * @brief Agrega un vertice
         * @param info Informacion del vertice
         */
        void agregarVertice(const T& info);

        /**
         * @brief Elimina un vertice
         * @param info Informacion del vertice
         */
        void eliminarVertice(const T& info);

        /**
        * @brief Agrega un arco al grafo
        * @param origen Informacion del vertice origen
        * @param destino Informacion del vertice destino
        * @param peso Peso del arco
        */
        virtual void agregarArco(const T& origen, const T& destino, const double& peso) = 0;

        /**
        * @brief Elimina todos los arco que conecta a dos vertices
        * @param origen Informacion del vertice origen
        * @param destino Informacion del vertice destino
        */
        virtual void eliminarArco(const T& origen, const T& destino) = 0;
    
        /**
        * @brief Elimina un arco con un peso especifico
        * @param origen Informacion del vertice origen
        * @param destino Informacion del vertice destino
        * @param peso Peso del arco
        */
        virtual void eliminarArco(const T& origen, const T& destino, const double& peso) = 0;
    
        /**
        * @brief Setea el peso del primer arco que conecta a dos vertices
        * @param origen Informacion del vertice origen
        * @param destino Informacion del vertice destino
        * @param peso Peso del arco
        */
        virtual void setPesoArco(const T& origen, const T& destino, const double& peso) = 0;
    
        /**
        * @brief Setea el peso del arco que coincida con el peso anterior y lo setea con el nuevo peso
        * @param origen Informacion del vertice origen
        * @param destino Informacion del vertice destino
        * @param pesoAnterior Peso del arco
        * @param pesoNuevo Peso del arco
        */
        virtual void setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo) = 0;


        /**
         * @brief Obtiene los adyacentes de un vertice
         * @param nodo Vertice
         * @return Vector de adyacentes
         */
        virtual std::vector<T> getAdyacentes(const T& nodo) const = 0;

        /**
         * @brief Obtiene el peso de un arco
         * @param origen Informacion del vertice origen
         * @param destino Informacion del vertice destino
         * @return Peso del arco
         */
        double getPesoArco(const T& origen, const T& destino);

        /**
         * @brief Obtiene los pesos de los arcos que conectan a dos vertices
         * @param origen Informacion del vertice origen
         * @param destino Informacion del vertice destinos
         * @return Vector de pesos
         */
         std::vector<double> getsPesosArcos(const T& origen, const T& destino);

        
        /**
         * @brief Copia el grafo
         */
        void copiar(const Grafos<T>& other);
        
        /**
         * @brief Limpia el grafo
         */
        void clear();

        /**
         * @brief Obtiene todos los vertices del grafo
         * @return Vector de vertices
         */
        std::vector<T> getVertices();

        /**
         * @brief Obtiene todos los arcos del vertice
         * @param verticeInfo Informacion del vertice
         * @return Vector de arcos
         */
        std::vector<T> getArcos(const T& verticeInfo);

        
        /**
         * @brief Verifica si el grafo esta vacio
         * @return true si esta vacio, false en caso contrario
         */
        inline bool esVacio() const { return this->primerVertice == NULL; }

        /**
         * @brief Obtiene el orden del grafo o numero de vertices
         * @return Orden del grafo
         */
        inline int getOrden() const { return nVertices; }

        /**
         * @brief Verifica si existe un vertice
         * @param verticeInfo Informacion del vertice
         * @return true si existe, false en caso contrario
         */
        inline bool existeVertice(const T& verticeInfo) { return this->irVertice(verticeInfo) != NULL; };

        /**
         * @brief Obtiene el tipo del vertice
         * @return Tipo del vertice
         */
        inline std::string getTipo() { return typeid(T).name(); }

        /**
         * @brief Verifica si existe un arco
         * @param origen Informacion del vertice origen
         * @param destino Informacion del vertice destino
         * @return true si existe, false en caso contrario
         */
        bool existeArco(const T& origen, const T& destino);

        /**
         * @brief Destructor
         */
        virtual ~Grafos() { this->clear(); };

        /**
         * @brief Operador de salida para imprimir el grafo
         * @param os Stream de salida
         * @param g Grafo a imprimir
         * @return Referencia al stream de salida
         */
        // operator<< se define como función libre en el .tpp

        /** Recorridos y propiedades del grafo (no dirigen)
         */

        /**
         * @brief Recorrido en profundidad (DFS)
         * @param verticeInicio Vertice de inicio
         * @return Vector de vertices
         */
        std::vector<T> DFS(T verticeInicio);

        /**
         * @brief Recorrido en amplitud (BFS)
         * @param verticeInicio Vertice de inicio
         * @return Vector de vertices
         */
        std::vector<T> BFS(T verticeInicio);

        /**
         * @brief Verifica si el grafo es conexo
         * @return true si es conexo, false en caso contrario
         */
        bool esConexo();

        /**
         * @brief Verifica si el grafo es ciclico
         * @param verticeInicio Vertice de inicio
         * @return true si es ciclico, false en caso contrario
         */
        bool esCiclico(T verticeInicio);

        /**
         * @brief Verifica si el grafo es ciclico
         * @return true si es ciclico, false en caso contrario
         */
        bool esCiclico();

        /**
         * @brief Verifica si el grafo es un arbol
         * @return true si es un arbol, false en caso contrario
         */
        bool esArbol();

        /**
         * @brief Operador de asignacion
         * @param other Otro grafo a copiar
         * @return Referencia al grafo
         */
        Grafos<T>& operator=(const Grafos<T>& other);

        /**
         * @brief Operador de [] para obtener los vertices
         * @param index Indice del vertice a obtener
         * @return Referencia al vertice en la posicion index
         * @throw std::runtime_error Si el indice es invalido
         */
        NodoVertice<T>& operator[](int index);


        /**
         * @brief Operador de [] para obtener los vertices
         * @param index Indice del vertice a obtener
         * @return Referencia al vertice en la posicion index
         * @throw std::runtime_error Si el indice es invalido
         */
        NodoVertice<T>& at(int index);
        
};

#include "Grafos.tpp"

#endif // GRAFOS_HPP