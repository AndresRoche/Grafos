#include <iostream>
#include <vector>
#include <stdexcept>

#include "GrafosNoDir.hpp"

template <typename T>
void GrafosNoDir<T>::agregarArco(const T& origen, const T& destino, const double& peso)  {
    std::vector<NodoVertice<T>*> vertices = this->irDosVertices(origen, destino);
    NodoVertice<T> * origenVertice = vertices[0];
    NodoVertice<T> * destinoVertice = vertices[1];
    this->nArcos++;

    NodoArco<T> * nuevoArco = new NodoArco<T>(peso, destinoVertice, NULL);
    nuevoArco->setSig(origenVertice->getArco());
    origenVertice->setArco(nuevoArco);

    nuevoArco = new NodoArco<T>(peso, origenVertice, NULL);
    nuevoArco->setSig(destinoVertice->getArco());
    destinoVertice->setArco(nuevoArco);

}

template <typename T>
void GrafosNoDir<T>::eliminarArco(const T& origen, const T& destino)  {
    std::vector<NodoVertice<T>*> vertices = this->irDosVertices(origen, destino);
    std::vector<T> verticesInfo;
    verticesInfo.push_back(vertices[1]->getInfo());
    verticesInfo.push_back(vertices[0]->getInfo());
    //origenVertice vertices[0];
    //destinoVertice vertices[1];
    this->nArcos--;

    //recorremos la lista de arcos del vertice origen
    int lenVertices = vertices.size();
    for(int i = 0; i<lenVertices; i++)
    {
        //recorremos la lista de arcos del vertice y lo eliminamos
        NodoArco<T> * arco = vertices[i]->getArco();
        NodoArco<T> * prevArco = NULL;
        NodoArco<T> * borrar = NULL;
        bool encontrado = false;
        // recorremos la lista de arcos del vertice y lo eliminamos
        while (arco != NULL && !encontrado) {

            // Si el arco es el primer arco
            if(prevArco == NULL && arco->getInfo()->getInfo() == verticesInfo[i]) {
                borrar = arco;
                vertices[i]->setArco(arco->getSig());
                arco = arco->getSig();
                delete borrar;
                encontrado = true;

                // Si el arco no es el primer arco
            } else if(arco->getInfo()->getInfo() == verticesInfo[i]) {
                borrar = arco;
                prevArco->setSig(arco->getSig());
                arco = arco->getSig();
                delete borrar;
                encontrado = true;
            } else {
                prevArco = arco;
                arco = arco->getSig();
            }
        }
        
        if(!encontrado) throw std::runtime_error("Arco no encontrado en el vertice " + vertices[i]->getInfo());
    }      
}

template <typename T>
void GrafosNoDir<T>::eliminarArco(const T& origen, const T& destino, const double& peso)  {
    std::vector<NodoVertice<T>*> vertices = this->irDosVertices(origen, destino);
    std::vector<T> verticesInfo;
    verticesInfo.push_back(vertices[1]->getInfo());
    verticesInfo.push_back(vertices[0]->getInfo());
    //origenVertice verticesInfo[0];
    //destinoVertice verticesInfo[1];
    this->nArcos--;

    //recorremos la lista de arcos del vertice origen
    int lenVertices = vertices.size();
    for(int i = 0; i<lenVertices; i++)
    {
        //recorremos la lista de arcos del vertice y lo eliminamos
        NodoArco<T> * arco = vertices[i]->getArco();
        NodoArco<T> * prevArco = NULL;
        NodoArco<T> * borrar = NULL;
        bool encontrado = false;
        // recorremos la lista de arcos del vertice y lo eliminamos
        while (arco != NULL && !encontrado) {    // ERROR EN DESTINOOOOO

            // Si el arco es el primer arco
            if(prevArco == NULL && arco->getInfo()->getInfo() == verticesInfo[i] && arco->getPeso() == peso) {
                borrar = arco;
                vertices[i]->setArco(arco->getSig());
                arco = arco->getSig();
                delete borrar;
                encontrado = true;

                // Si el arco no es el primer arco
            } else if(arco->getInfo()->getInfo() == verticesInfo[i] && arco->getPeso() == peso) {
                borrar = arco;
                prevArco->setSig(arco->getSig());
                arco = arco->getSig();
                delete borrar;
                encontrado = true;
            } else {
                prevArco = arco;
                arco = arco->getSig();
            }
        }
        
        if(!encontrado) throw std::runtime_error("Arco no encontrado en el vertice " + vertices[i]->getInfo());
    }  
}

template <typename T>
void GrafosNoDir<T>::setPesoArco(const T& origen, const T& destino, const double& peso)  {
    std::vector<NodoVertice<T>*> vertices = this->irDosVertices(origen, destino);
    std::vector<T> verticesInfo;
    verticesInfo.push_back(vertices[1]->getInfo());
    verticesInfo.push_back(vertices[0]->getInfo());
    //origenVertice vertices[0];
    //destinoVertice vertices[1];
    int lenVertices = vertices.size();
    for(int i = 0; i < lenVertices; i++)
    {
        NodoArco<T> * arco = vertices[i]->getArco();
        while(arco != NULL)
        {
            if(arco->getInfo()->getInfo() == verticesInfo[i])
            {
                arco->setPeso(peso);
                return;
            }
            arco = arco->getSig();
        }
    }
    
}

/*
    En realidad no se puede usar esta funcion solo lo coloca para no generar fallo
*/
template <typename T>
void GrafosNoDir<T>::setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo) 
{
    std::vector<NodoVertice<T>*> vertices = this->irDosVertices(origen, destino);
    std::vector<T> verticesInfo;
    verticesInfo.push_back(vertices[1]->getInfo());
    verticesInfo.push_back(vertices[0]->getInfo());
    //origenVertice vertices[0];
    //destinoVertice vertices[1];
    int lenVertices = vertices.size();
    for(int i = 0; i < lenVertices; i++)
    {
        NodoArco<T> * arco = vertices[i]->getArco();
        while(arco != NULL)
        {
            if(arco->getInfo()->getInfo() == verticesInfo[i] && arco->getPeso() == pesoAnterior)
            {
                arco->setPeso(pesoNuevo);
                return;
            }
            arco = arco->getSig();
        }
    }
    throw std::runtime_error("Arco con el peso anterior no encontrado");
}


template <typename T>
std::vector<T> GrafosNoDir<T>::getVecinos(const T& verticeInfo) const {
    std::vector<T> sucesores;

    NodoVertice<T> * current = this->irVertice(verticeInfo);
    if(current == NULL)
    {
        throw std::runtime_error("Vertice no encontrado");
    }
    
    //recorremos la lista de arcos del vertice
    NodoArco<T> * arco = current->getArco();
    while(arco != NULL)
    {
        sucesores.push_back(arco->getInfo()->getInfo());
        arco = arco->getSig();
    }
    return sucesores;
}

template <typename T>
std::vector<T> GrafosNoDir<T>::getAdyacentes(const T& verticeInfo) const  {
    return this->getVecinos(verticeInfo);
}


template <typename T> 
GrafosNoDir<int> GrafosNoDir<T>::mapeado()
{
    GrafosNoDir<int> mapeado;
    
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
