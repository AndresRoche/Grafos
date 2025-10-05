#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stdexcept>

#include "Grafos.hpp"

// Busca los dos vertices y los retorna en un vector
template <typename T>
std::vector<NodoVertice<T>*>  Grafos<T>::irDosVertices(const T& origen, const T& destino) {
    std::vector<NodoVertice<T>*> vertices;
    
    NodoVertice<T> * current = this->primerVertice;
    NodoVertice<T> * origenVertice = NULL;
    NodoVertice<T> * destinoVertice = NULL;
    bool encontradoOrigen = false;
    bool encontradoDestino = false;
    
    // Primero buscamos si existe el origen y el destino
    while(current != NULL)
    {
        if(current->getInfo() == origen)
        {
            encontradoOrigen = true;
            origenVertice = current;

            // Si ya se encontro el destino, salimos del bucle y como estamos dentro del bucle
            // significa que el origen ya se encontro
            if(encontradoDestino)
                break;
        }
        if(current->getInfo() == destino)
        {
            encontradoDestino = true;
            destinoVertice = current;

            // Si ya se encontro el origen, salimos del bucle
            if(encontradoOrigen)
                break;
        }
        current= current->getSig();
    }

    // Si no se encontro el origen o el destino
    if(!encontradoOrigen || !encontradoDestino)
    {
        if(!encontradoOrigen)
        {
            throw std::runtime_error("Origen no encontrado");
        }
        if(!encontradoDestino)
        {
            throw std::runtime_error("Destino no encontrado");
        }
        throw std::runtime_error("Vertices no encontrados");
    }

    vertices.push_back(origenVertice);
    vertices.push_back(destinoVertice);
    return vertices;
}


template <typename T>
NodoVertice<T> * Grafos<T>::irVertice(const T& info) const {
    NodoVertice<T> * current = this->primerVertice;
    while (current != NULL) {
        if (current->getInfo() == info) {
            return current;
        }
        current = current->getSig();
    }
    return NULL;
}


template <typename T>
Grafos<T>::Grafos(const Grafos<T>& other) {
    copiar(other);
}


template <typename T>
void Grafos<T>::agregarVertice(const T& info) {
    //basicamente el como se agregar un nodo en una pila 
    NodoVertice<T> * nuevoVertice = new NodoVertice<T>(info, NULL, NULL);
    if (this->esVacio()) {
        this->primerVertice = nuevoVertice;
    } else {
        nuevoVertice->setSig(this->primerVertice);
        this->primerVertice = nuevoVertice;
    }
    this->nVertices++;
}

template <typename T>
void Grafos<T>::eliminarVertice(const T& info) {
    NodoVertice<T> * current = this->primerVertice;
    NodoVertice<T> * target = NULL;
    NodoVertice<T> * prev = NULL;
    bool encontrado = false;

    //recorremos la lista de vertices Para buscar si existe el vertice con la informacion dada
    while (current != NULL && !encontrado) {
        if (current->getInfo() == info) {
            target = current;
            encontrado = true;

            //recorremos la lista de arcos del vertice y lo eliminamos
            NodoArco<T> * arco = target->getArco();
            NodoArco<T> * prevArco = NULL;
            while (arco != NULL) {
                prevArco = arco;
                arco = arco->getSig();
                this->nArcos--;
                delete prevArco;
            }
            target->setArco(NULL);
        }
        if(encontrado)
            break;
        prev = current;
        current = current->getSig();
    }

    //si no se encontro el vertice
    if(!encontrado) {
        throw std::runtime_error("Vertice no encontrado");
    }

    //si el vertice es el primer vertice
    if(prev == NULL) {
        this->primerVertice = target->getSig();
    } else {
        prev->setSig(target->getSig());
    }

    //recorremos la lista de vertices y eliminamos los arcos que apuntan al vertice eliminado
    current = this->primerVertice;
    while (current != NULL) {
        NodoArco<T> * arco = current->getArco();
        NodoArco<T> * prevArco = NULL;
        NodoArco<T> * borrar = NULL;

        // recorremos la lista de arcos del vertice y lo eliminamos
        while (arco != NULL) {

            // Si el arco es el primer arco
            if(prevArco == NULL && arco->getInfo() == target) {
                borrar = arco;
                current->setArco(arco->getSig());
                arco = arco->getSig();
                this->nArcos--;
                delete borrar;

                // Si el arco no es el primer arco
            } else if(arco->getInfo() == target) {
                borrar = arco;
                prevArco->setSig(arco->getSig());
                arco = arco->getSig();
                this->nArcos--;
                delete borrar;
            } else {
                prevArco = arco;
                arco = arco->getSig();
            }
            
        }
        current = current->getSig();   
    }

    //eliminamos el vertice
    delete target;
    this->nVertices--;
}


template <typename T>
double Grafos<T>::getPesoArco(const T& origen, const T& destino)
{
    NodoVertice<T> * current = this->irVertice(origen);
    if(current == NULL)
        throw std::runtime_error("Origen no encontrado");
    
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        if(arco->getInfo()->getInfo() == destino)
        {
            return arco->getPeso();
        }
        arco = arco->getSig();
    }
    throw std::runtime_error("Arco no encontrado");
}


template <typename T>
std::vector<double> Grafos<T>::getsPesosArcos(const T& origen, const T& destino)
{
    std::vector<double> pesos;
 
    NodoVertice<T> * current = this->irVertice(origen);
    if(current == NULL)
        throw std::runtime_error("Origen no encontrado");
    
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        if(arco->getInfo()->getInfo() == destino)
        {
            pesos.push_back(arco->getPeso());
        }
        arco = arco->getSig();
    }
    return pesos;
}

// Probablemente no funcione bien
template <typename T>
void Grafos<T>::copiar(const Grafos<T>& other)
{
    //primero limpiamos
    this->clear();

    //creamos una lista con los vertices del grafo
    //esto esta porque si lo haciamos directo los vertices quedaria en orden invertido
    //pero los grafo no 
    std::list<T> vertices;
    NodoVertice<T> * current = other.getPrimerVertice();
    while (current != NULL) {
        vertices.push_front(current->getInfo());
        current = current->getSig();
    }
    // despues de esto tenemos nuestro vertices
    // si usando getVertices optenemos algo asi [A,B,C]
    //pero con la lista [C,A,B]


    //recorremos la lista de vertices y vamos agregando los vertices al nuevo grafo
    int lenVertices = vertices.size();
    for(int i = lenVertices - 1; i >= 0; i--) {
        //basicamente el como se agregar un nodo en una pila 
        NodoVertice<T> * nuevoVertice = new NodoVertice<T>(vertices.front(), NULL, NULL);
        vertices.pop_front();
        if (this->esVacio()) {
            this->primerVertice = nuevoVertice;
        } else {
            nuevoVertice->setSig(this->primerVertice);
            this->primerVertice = nuevoVertice;
        }
    }

    //recorremos la lista de vertices
    current = other.getPrimerVertice();
    NodoVertice<T> * thisGrafo = this->primerVertice;
    while (current != NULL) {
        
        //recorremos la lista de arcos del vertice
        //y agregamos los arcos al nuevo grafo
        NodoArco<T> * arco = current->getArco();
        while (arco != NULL) {

            //creamos el arco
            NodoVertice<T> * destino = this->irVertice(arco->getInfo()->getInfo());
            if(destino == NULL)
                throw std::runtime_error("Destino no encontrado");
            
            NodoArco<T> * nuevoArco = new NodoArco<T>(arco->getPeso(), destino, NULL);
            nuevoArco->setSig(thisGrafo->getArco());
            thisGrafo->setArco(nuevoArco);

            arco = arco->getSig();
        }

        thisGrafo = thisGrafo->getSig();
        current = current->getSig();
    }

    this->nArcos = other.getNArcos();
    this->nVertices = other.getNVertices();
}

template <typename T>
void Grafos<T>::clear()
{
    NodoVertice<T> * current = this->primerVertice;
    NodoVertice<T> * prev = NULL;
    // Recorriendo la lista de vertices
    while (current != NULL) {

        NodoArco<T> * arco = current->getArco();
        NodoArco<T> * prevArco = NULL;
        // Recorriendo la lista de arcos
        while (arco != NULL) {
            prevArco = arco;
            arco = arco->getSig();
            this->nArcos--;
            delete prevArco;
        }

        prev = current;
        current = current->getSig();
        this->nVertices--;
        delete prev;
    }
    this->primerVertice = NULL;
}


template <typename T>
std::vector<T> Grafos<T>::getVertices()
{
    std::vector<T> vertices;
    NodoVertice<T> * current = this->primerVertice;
    while (current != NULL) {
        vertices.push_back(current->getInfo());
        current = current->getSig();
    }
    return vertices;
}

template <typename T>
std::vector<T> Grafos<T>::getArcos(const T& verticeInfo)
{
    std::vector<T> arcos;
    NodoVertice<T> * current = this->irVertice(verticeInfo);
    if(current == NULL)
        throw std::runtime_error("Vertice no encontrado");
    
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        arcos.push_back(arco->getInfo()->getInfo());
        arco = arco->getSig();
    }
    return arcos;
}


// (implementations moved below after mapeado)

template <typename T>
bool Grafos<T>::existeArco(const T& origen, const T& destino)
{
    NodoVertice<T> * current = this->irVertice(origen);
    if(current == NULL)
        throw std::runtime_error("Vertice no encontrado");
    
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        if(arco->getInfo()->getInfo() == destino)
            return true;
        arco = arco->getSig();
    }
    return false;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Grafos<T>& g)
{
    NodoVertice<T> * current = g.getPrimerVertice();
    while (current != NULL) {
        os << "Vertice: [" << current->getInfo() << "] conectado a: " << "\n";
        NodoArco<T> * arco = current->getArco();
        while (arco != NULL) {
            os << "- " << arco->getInfo()->getInfo() << " ( peso : " << arco->getPeso() << ")" << "\n";
            arco = arco->getSig();
        }
        current = current->getSig();
    }
    return os;
}


template <typename T>
Grafos<T>& Grafos<T>::operator=(const Grafos<T>& other)
{
    return *this;
}

template <typename T>
NodoVertice<T>& Grafos<T>::operator[](int index)
{
    return this->at(index);
}

template <typename T>
NodoVertice<T>& Grafos<T>::at(int index)
{
    if (index < 0 || index >= nVertices) {
        throw std::runtime_error("Índice de vértice no válido");
    }

    NodoVertice<T>* current = primerVertice;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->getSig();
    }
    
    if (current == NULL) {
        throw std::runtime_error("Error al acceder al vértice");
    }
    
    return *current;
}


/* 
template <typename T<int> Grafos<T>::mapeado()
{<int> mapeado;
    
    std::map<T, int> vertices_mapeados;
    std::vector<T> vertices = this->getVertices();
    int lenVertices = vertices.size();
    for(int i = lenVertices - 1; i >= 0; i--) {
        vertices_mapeados.insert(std::pair<T, int>(vertices[i], i));
        mapeado.agregarVertice(i);
    }

    NodoVertice<T> * current = this->primerVertice;
    NodoVertice<int> * mapeadoGrafo = mapeado.getPrimerVertice();
    while (current != NULL) {

        NodoArco<T> * arco = current->getArco();
        while (arco != NULL) {
            mapeado.agregarArco(mapeadoGrafo->getInfo(), vertices_mapeados[arco->getInfo()->getInfo()], arco->getPeso());
            arco = arco->getSig();
        }

        current = current->getSig();
        mapeadoGrafo = mapeadoGrafo->getSig();
    }

    return mapeado;
    
} */

// Recorrido en profundidad (DFS)
template <typename T>
std::vector<T> Grafos<T>::DFS(T verticeInicio)
{
    std::vector<T> result;
    std::map<T, bool> visitado;

    for(const auto &vertice : this->getVertices())
        visitado.insert(std::pair<T, bool>(vertice, false));

    DFS(verticeInicio, result, visitado);

    return result;
}

// DFS helper recursivo
template <typename T>
void Grafos<T>::DFS(T verticeInicio, std::vector<T> &result, std::map<T,bool> &visitado)
{
    std::vector<T> vertices = this->getAdyacentes(verticeInicio);
    visitado[verticeInicio] = true;
    result.push_back(verticeInicio);

    while(!vertices.empty())
    {
        T vertice = vertices.back();
        vertices.pop_back();
        if(!visitado[vertice])
        {
            DFS(vertice, result, visitado);
        }
    }
}

// Recorrido en amplitud (BFS)
template <typename T>
std::vector<T> Grafos<T>::BFS(T verticeInicio)
{
    std::vector<T> result;
    std::map<T, bool> visitado;

    for(const auto &vertice : this->getVertices())
        visitado.insert(std::pair<T, bool>(vertice, false));

    std::queue<T> cola;
    cola.push(verticeInicio);
    visitado[verticeInicio] = true;

    while(!cola.empty())
    {
        T vertice = cola.front();
        std::vector<T> vertices = this->getAdyacentes(vertice);
        while(!vertices.empty())
        {
            T w = vertices.front();
            if(!visitado[w])
            {
                cola.push(w);
                visitado[w] = true;
            }
            vertices.erase(vertices.begin());
        }
        result.push_back(vertice);
        cola.pop();
    }
    
    return result;
}

// Conectividad
template <typename T>
bool Grafos<T>::esConexo()
{
    if (this->esVacio()) return true;
    std::vector<T> vertices = this->DFS(this->primerVertice->getInfo());
    return vertices.size() == this->getVertices().size();    
}

// Ciclicidad desde vertice
template <typename T>
bool Grafos<T>::esCiclico(T verticeInicio)
{
    std::vector<T> result;
    std::map<T, bool> visitado;

    for(const auto &vertice : this->getVertices())
        visitado.insert(std::pair<T, bool>(vertice, false));

    std::queue<T> cola;
    cola.push(verticeInicio);
    visitado[verticeInicio] = true;

    while(!cola.empty())
    {
        T vertice = cola.front();
        std::vector<T> vertices = this->getAdyacentes(vertice);
        while(!vertices.empty())
        {
            T w = vertices.front();
            if(!visitado[w])
            {
                cola.push(w);
                visitado[w] = true;
            } else
            {
                return true;
            }
            vertices.erase(vertices.begin());
        }
        result.push_back(vertice);
        cola.pop();
    }
    
    return false;
}

// Ciclicidad general (primer vertice)
template <typename T>
bool Grafos<T>::esCiclico()
{
    if (this->esVacio()) return false;
    return this->esCiclico(this->primerVertice->getInfo());
}

// Arbol: n-1 arcos, conexo y acíclico
template <typename T>
bool Grafos<T>::esArbol()
{
    int lenVertices = this->getVertices().size();
    if(lenVertices != this->nArcos + 1)
        return false;
    return this->esConexo() && !this->esCiclico();
}