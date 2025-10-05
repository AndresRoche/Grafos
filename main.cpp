#include <iostream>
#include "GrafosDir.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <map>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & vec)
{
    typename std::vector<T>::const_iterator it;

    for(it = vec.begin(); it != vec.end(); ++it){
        os << *it << " ";
    }
    return os;
}


void test()
{
    
    GrafosDir<char> grafo;
    grafo.agregarVertice('a');
    grafo.agregarVertice('b');
    grafo.agregarVertice('c');
    grafo.agregarVertice('d');
    grafo.agregarVertice('e');
    grafo.agregarArco('a', 'b', 1);
    grafo.agregarArco('a', 'c', 2);
    grafo.agregarArco('a', 'd', 3);
    grafo.agregarArco('b', 'c', 4);
    grafo.agregarArco('b', 'a', 5);
    grafo.agregarArco('c', 'd', 1);
    grafo.agregarArco('c', 'a', 2);
    grafo.agregarArco('d', 'e', 7);
    grafo.agregarArco('e', 'a', 10);
    std::cout << grafo << std::endl;
    
    std::cout << "Orden del grafo: " << grafo.getOrden() << std::endl;
    std::cout << "NVertices: " << grafo.getNVertices() << std::endl;
    std::cout << "NArcos: " << grafo.getNArcos() << std::endl;


    grafo.eliminarVertice('e');
    std::cout << grafo << std::endl;
    
    std::cout << "Orden del grafo: " << grafo.getOrden() << std::endl;
    std::cout << "NVertices: " << grafo.getNVertices() << std::endl;
    std::cout << "NArcos: " << grafo.getNArcos() << std::endl;

    grafo.agregarVertice('f');
    grafo.agregarArco('f', 'a', 10);
    std::cout << grafo << std::endl;
    
    std::cout << "Orden del grafo: " << grafo.getOrden() << std::endl;
    std::cout << "NVertices: " << grafo.getNVertices() << std::endl;
    std::cout << "NArcos: " << grafo.getNArcos() << std::endl;
    
    grafo.agregarArco('a', 'b', 88);
    grafo.agregarArco('a', 'b', 19);
    grafo.agregarArco('a', 'b', 13);
    std::cout << "Existe arco a-b: " << grafo.existeArco('a', 'b') << std::endl;
    grafo.eliminarArco('a', 'b');
    grafo.eliminarArco('a', 'b', 19);
    std::cout << grafo << std::endl;
    
    std::cout << "Orden del grafo: " << grafo.getOrden() << std::endl;
    std::cout << "NVertices: " << grafo.getNVertices() << std::endl;
    std::cout << "NArcos: " << grafo.getNArcos() << std::endl;


    grafo.setPesoArco('a', 'b', 1);
    std::cout << grafo << std::endl;
    
    std::cout << "Orden del grafo: " << grafo.getOrden() << std::endl;
    std::cout << "NVertices: " << grafo.getNVertices() << std::endl;
    std::cout << "NArcos: " << grafo.getNArcos() << std::endl;

    grafo.setPesoArco('a', 'b', 1, 13);
    std::cout << grafo << std::endl;
    
    std::cout << "Orden del grafo: " << grafo.getOrden() << std::endl;
    std::cout << "NVertices: " << grafo.getNVertices() << std::endl;
    std::cout << "NArcos: " << grafo.getNArcos() << std::endl;

    std::cout << "Peso de a-b: " << grafo.getPesoArco('a', 'b') << std::endl;

    std::cout << "Pesos de a-b: " << grafo.getsPesosArcos('a', 'b') << std::endl; 

    std::cout << "Sucesores de a: " << grafo.getSucesores('a') << std::endl;
    std::cout << "Predecesores de a: " << grafo.getPredecesores('a') << std::endl;
    std::cout << "Vertices: " << grafo.getVertices() << std::endl;
    std::cout << "Arcos: " << grafo.getArcos('a') << std::endl;

    std::cout << "Es vacio: " << grafo.esVacio() << std::endl;
    std::cout << "existe arco a-b: " << grafo.existeArco('a', 'b') << std::endl;
    std::cout << "existe arco b-a: " << grafo.existeArco('b', 'h') << std::endl;

    std::cout << "existe vertice a: " << grafo.existeVertice('a') << std::endl;
    std::cout << "existe vertice g: " << grafo.existeVertice('g') << std::endl;

    std::cout << "Grafo: " << std::endl;
    std::cout << grafo << std::endl;


    GrafosDir<char> grafo_2;

    grafo_2.copiar(grafo);
    std::cout << "Grafo 2: " << std::endl;
    std::cout << grafo_2 << std::endl;

    std::cout << "Vaciar Grafo 1: " << std::endl;
    grafo.clear();
    std::cout << grafo.esVacio() << std::endl;

    std::cout << "Agregamos un arco f -> d con peso 1" << std::endl;
    grafo_2.agregarArco('f', 'd', 1);
    std::cout << "Agregamos un arco d -> f con peso 8" << std::endl;
    grafo_2.agregarArco('d', 'f', 8);
    std::cout << "Grafo 2: " << std::endl;
    std::cout << grafo_2 << std::endl;

    std::cout << "Mapeado: " << std::endl;
    GrafosDir<int> mapeado = grafo_2.mapeado();
    std::cout << mapeado << std::endl;

    std::cout << "Vertice 0: " << std::endl;
    std::cout << grafo_2[0][0].getPeso() << std::endl;

    std::cout << "Tipo de dato del Grafo 2: " << grafo_2.getTipo() << std::endl;
    std::cout << "Tipo de dato del Grafo Mapeado: " << mapeado.getTipo() << std::endl;

    std::cout << "Recorrido en profundidad: " << std::endl;
    std::cout << mapeado.DFS(0) << std::endl;

    std::cout << "Recorrido en amplitud: " << std::endl;
    std::cout << mapeado.BFS(0) << std::endl;

    std::cout << "Recorrido en profundidad: " << std::endl;
    std::cout << grafo_2.BFS('f') << std::endl;

    //probando si es conexo
    std::cout << "Es conexo: " << std::endl;
    std::cout << mapeado.esConexo() << std::endl;

    //probando si es ciclico
    std::cout << "Es ciclico: " << std::endl;
    std::cout << mapeado.esCiclico() << std::endl;

    //probando si es arbol
    std::cout << "Es arbol: " << std::endl;
    std::cout << mapeado.esArbol() << std::endl;

}


int main() {
    test();
    return 0;
}