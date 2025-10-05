#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <queue>
#include <sstream>

#include "GrafosDir.hpp"

template <typename T>
void GrafosDir<T>::agregarArco(const T& origen, const T& destino, const double& peso) 
{
   
    std::vector<NodoVertice<T>*> vertices = this->irDosVertices(origen, destino);
    NodoVertice<T> * origenVertice = vertices[0];
    NodoVertice<T> * destinoVertice = vertices[1];

    //Agregamos el nuevo arco
    NodoArco<T> * nuevoArco = new NodoArco<T>(peso, destinoVertice, NULL);
    nuevoArco->setSig(origenVertice->getArco());
    origenVertice->setArco(nuevoArco);
    this->nArcos++;
}


template <typename T>
void GrafosDir<T>::eliminarArco(const T& origen, const T& destino) 
{
    NodoVertice<T> * target = this->irVertice(origen);
    if(target == NULL)
        throw std::runtime_error("Origen no encontrado");
    
    
    //recorremos la lista de arcos del vertice y lo eliminamos
    NodoArco<T> * arco = target->getArco();
    NodoArco<T> * prevArco = NULL;
    NodoArco<T> * borrar = NULL;
    bool encontrado = false;
    // recorremos la lista de arcos del vertice y lo eliminamos
    while (arco != NULL && !encontrado) {

        // Si el arco es el primer arco
        if(prevArco == NULL && arco->getInfo()->getInfo() == destino) {
            borrar = arco;
            target->setArco(arco->getSig());
            arco = arco->getSig();
            this->nArcos--;
            delete borrar;
            encontrado = true;
            
            // Si el arco no es el primer arco
        } else if(arco->getInfo()->getInfo() == destino) {
            borrar = arco;
            prevArco->setSig(arco->getSig());
            arco = arco->getSig();
            this->nArcos--;
            delete borrar;
            encontrado = true;
            
        } else {
            prevArco = arco;
            arco = arco->getSig();
        }
    }

    if(!encontrado){
        std::ostringstream oss;
        oss << "Arco no encontrado en el vertice " << target->getInfo();
        throw std::runtime_error(oss.str());
    }
}


template <typename T>
void GrafosDir<T>::eliminarArco(const T& origen, const T& destino, const double& peso) 
{
    NodoVertice<T> * current = this->irVertice(origen);
    if(current == NULL)
    {
        throw std::runtime_error("Origen no encontrado");
    }
    
    //recorremos la lista de arcos del vertice y lo eliminamos
    NodoArco<T> * arco = current->getArco();
    NodoArco<T> * prevArco = NULL;
    NodoArco<T> * borrar = NULL;
    bool encontrado = false;
    // recorremos la lista de arcos del vertice y lo eliminamos
    while (arco != NULL && !encontrado) {

        // Si el arco es el primer arco
        if(prevArco == NULL && arco->getInfo()->getInfo() == destino && arco->getPeso() == peso) {
            borrar = arco;
            current->setArco(arco->getSig());
            arco = arco->getSig();
            this->nArcos--;
            delete borrar;
            encontrado = true;

            // Si el arco no es el primer arco
        } else if(arco->getInfo()->getInfo() == destino && arco->getPeso() == peso) {
            borrar = arco;
            prevArco->setSig(arco->getSig());
            arco = arco->getSig();
            this->nArcos--;
            delete borrar;
            encontrado = true;
        } else {
            prevArco = arco;
            arco = arco->getSig();
        }
    }
    
    if(!encontrado){
        std::ostringstream oss;
        oss << "Arco no encontrado en el vertice " << current->getInfo();
        throw std::runtime_error(oss.str());
    }
}

template <typename T>
void GrafosDir<T>::setPesoArco(const T& origen, const T& destino, const double& peso) 
{
    NodoVertice<T> * current = this->irVertice(origen);
    if(current == NULL)
    {
        throw std::runtime_error("Origen no encontrado");
    }
    
    //recorremos la lista de arcos del vertice y lo eliminamos
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        if(arco->getInfo()->getInfo() == destino)
        {
            arco->setPeso(peso);
            return;
        }
        arco = arco->getSig();
    }
    throw std::runtime_error("Arco no encontrado");
}


template <typename T>
void GrafosDir<T>::setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo) 
{
    NodoVertice<T> * current = this->irVertice(origen);
    if(current == NULL)
    {
        throw std::runtime_error("Origen no encontrado");
    }

    //recorremos la lista de arcos del vertice y lo eliminamos
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        if(arco->getInfo()->getInfo() == destino && arco->getPeso() == pesoAnterior)
        {
            arco->setPeso(pesoNuevo);
            return;
        }
        arco = arco->getSig();
    }
    throw std::runtime_error("Arco con el peso anterior no encontrado");
}



template <typename T>
std::vector<T> GrafosDir<T>::getSucesores(const T& info) const
{
    std::vector<T> sucesores;

    NodoVertice<T> * current = this->irVertice(info);
    if(current == NULL)
    {
        throw std::runtime_error("Vertice no encontrado");
    }
    
    //recorremos la lista de arcos del vertice y lo eliminamos
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        sucesores.push_back(arco->getInfo()->getInfo());
        arco = arco->getSig();
    }
    return sucesores;
}


template <typename T>
std::vector<T> GrafosDir<T>::getPredecesores(const T& info) const
{
    std::vector<T> predecesores;

    //recorremos la lista de vertices
    NodoVertice<T> * current = this->primerVertice;
    while(current != NULL)
    {
        //recorremos la lista de arcos del vertice y lo eliminamos
        NodoArco<T> * arco = current->getArco();
        while(arco != NULL)
        {
            if(arco->getInfo()->getInfo() == info)
            {
                predecesores.push_back(current->getInfo());
            }
            arco = arco->getSig();
        }
        current = current->getSig();
    }
    return predecesores;
}

template <typename T>
std::vector<T> GrafosDir<T>::getAdyacentes(const T& nodo) const 
{
    return this->getSucesores(nodo);
}


template <typename T> 
GrafosDir<int> GrafosDir<T>::mapeado()
{
    GrafosDir<int> mapeado;
    
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
    
} 