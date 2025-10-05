#ifndef GRAFO_NODIR_H
#define GRAFO_NODIR_H

#include "Grafos.hpp"

template <typename T>
class GrafosNoDir : public Grafos<T> {

  public:

    /**
     * @brief Agrega un arco al grafo
     * @param origen Informacion del vertice origen
     * @param destino Informacion del vertice destino
     * @param peso Peso del arco
     */
    void agregarArco(const T& origen, const T& destino, const double& peso) override;

    /**
     * @brief Elimina un Todos los arcos que conectan a dos vertices
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
     * @brief Obtiene los vecinos de un vertice
     * @param verticeInfo Informacion del vertice
     * @return Vector de vecinos
     */
    std::vector<T> getVecinos(const T& verticeInfo) const;

    
    /**
     * @brief Obtiene los adyacentes de un vertice
     * @param nodo Vertice
     * @return Vector de adyacentes
     */
    std::vector<T> getAdyacentes(const T& nodo) const override;


    /**
     * @brief Obtiene el mapeado del grafo
     * @return GrafosNoDir<int> Mapeado del grafo
     */
    GrafosNoDir<int> mapeado();
    
};

#include "GrafosNoDir.tpp"

#endif // GRAFO_NODIR_H
