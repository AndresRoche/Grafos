#ifndef GRAFOS_DIR_HPP
#define GRAFOS_DIR_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Grafos.hpp"

template <typename T>
class GrafosDir : public Grafos<T> {
    
  public:

    /**
    * @brief Constructor de la clase
    */
    GrafosDir() : Grafos<T>() {}

    /**
    * @brief Agrega un arco al grafo
    * @param origen Informacion del vertice origen
    * @param destino Informacion del vertice destino
    * @param peso Peso del arco
    */
    void agregarArco(const T& origen, const T& destino, const double& peso) override;

    /**
     * @brief Elimina todos los arco que conecta a dos vertices
     * @param origen Informacion del vertice origen
     * @param destino Informacion del vertice destino
     */
    void eliminarArco(const T& origen, const T& destino) override;
 
    /**
     * @brief Elimina un arco con un peso especifico
     * @param origen Informacion del vertice origen
     * @param destino Informacion del vertice destino
     * @param peso Peso del arco
     */
    void eliminarArco(const T& origen, const T& destino, const double& peso) override;
 
    /**
     * @brief Setea el peso del primer arco que conecta a dos vertices
     * @param origen Informacion del vertice origen
     * @param destino Informacion del vertice destino
     * @param peso Peso del arco
     */
    void setPesoArco(const T& origen, const T& destino, const double& peso) override;
 
    /**
     * @brief Setea el peso del arco que coincida con el peso anterior y lo setea con el nuevo peso
     * @param origen Informacion del vertice origen
     * @param destino Informacion del vertice destino
     * @param pesoAnterior Peso del arco
     * @param pesoNuevo Peso del arco
     */
    void setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo) override;

    /**
     * @brief Obtiene los sucesores de un vertice
     * @param info Informacion del vertice
     * @return Vector de sucesores
     */
    std::vector<T> getSucesores(const T& info) const;

    /**
     * @brief Obtiene los predecesores de un vertice
     * @param info Informacion del vertice
     * @return Vector de predecesores
     */
    std::vector<T> getPredecesores(const T& info) const;

    
    /**
     * @brief Obtiene los adyacentes de un vertice
     * @param nodo Vertice
     * @return Vector de adyacentes
     */
    std::vector<T> getAdyacentes(const T& nodo) const override;


    /**
     * @brief Obtiene el mapeado del grafo
     * @return GrafosDir<int> 
     */
    GrafosDir<int> mapeado();
};


#include "GrafosDir.tpp"


#endif // GRAFOS_DIR_HPP