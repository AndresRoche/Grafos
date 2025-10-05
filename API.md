# Documentación de la API de Grafos

Este documento describe las clases y métodos de la librería ubicada en `grafoDir/`.

- Ubicación:
  - Base: `grafoDir/Grafos.hpp`, `grafoDir/Grafos.tpp`
  - Dirigidos: `grafoDir/GrafosDir.hpp`, `grafoDir/GrafosDir.tpp`
  - No dirigidos: `grafoDir/GrafosNoDir.hpp`, `grafoDir/GrafosNoDir.tpp`
  - Nodos: `grafoDir/NodoVertice.hpp/.tpp`, `grafoDir/NodoArco.hpp/.tpp`

Notas generales:
- Todas las clases son plantillas (templates) parametrizadas por `T`, el tipo almacenado en cada vértice.
- Las estructuras internas usan listas enlazadas para vértices y arcos.
- Muchas operaciones lanzan `std::runtime_error` cuando no encuentran vértices/arcos.

---

## Clase base: `Grafos<T>`

Representa la estructura y operaciones comunes. Es abstracta; los métodos de arcos son virtuales puros y se implementan en las derivadas (`GrafosDir`, `GrafosNoDir`).

Atributos (protegidos):
- `NodoVertice<T>* primerVertice` – cabeza de la lista de vértices.
- `int nVertices` – cantidad de vértices.
- `int nArcos` – cantidad de arcos (en no dirigidos cuenta pares como 1).

Constructores y asignación:
- `Grafos()` – inicializa grafo vacío.
- `Grafos(const Grafos<T>& other)` – copia profunda (usa `copiar`).
- `Grafos<T>& operator=(const Grafos<T>& other)` – asignación.
- `virtual ~Grafos()` – destructor, invoca `clear()`.

Operaciones sobre vértices:
- `void agregarVertice(const T& info)`
  - Agrega un vértice al inicio de la lista.
  - Efectos: `nVertices`++.
- `void eliminarVertice(const T& info)`
  - Elimina el vértice y todos los arcos salientes y entrantes hacia él.
  - Excepciones: `runtime_error("Vertice no encontrado")` si no existe.

Operaciones sobre arcos (virtuales puras):
- `virtual void agregarArco(const T& origen, const T& destino, const double& peso) = 0`
- `virtual void eliminarArco(const T& origen, const T& destino) = 0`
- `virtual void eliminarArco(const T& origen, const T& destino, const double& peso) = 0`
- `virtual void setPesoArco(const T& origen, const T& destino, const double& peso) = 0`
- `virtual void setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo) = 0`

Consultas y utilidades:
- `double getPesoArco(const T& origen, const T& destino)`
  - Retorna el peso del primer arco que conecta `origen -> destino`.
  - Excepciones: `runtime_error("Origen no encontrado")`, `runtime_error("Arco no encontrado")`.
- `std::vector<double> getsPesosArcos(const T& origen, const T& destino)`
  - Retorna todos los pesos de arcos `origen -> destino`.
  - Excepciones: `runtime_error("Origen no encontrado")`.
- `std::vector<T> getVertices()`
  - Retorna una copia de la lista de vértices (orden de inserción inversa).
- `std::vector<T> getArcos(const T& verticeInfo)`
  - Retorna los destinos adyacentes desde `verticeInfo`.
  - Excepciones: `runtime_error("Vertice no encontrado")`.
- `bool esVacio() const`
- `int getOrden() const` – cantidad de vértices.
- `int getNVertices() const`
- `int getNArcos() const`
- `bool existeVertice(const T& verticeInfo)`
- `std::string getTipo()` – nombre de tipo `T`.
- `bool existeArco(const T& origen, const T& destino)`
  - Excepciones: `runtime_error("Vertice no encontrado")` si no está `origen`.

Recorridos y propiedades:
- `std::vector<T> DFS(T verticeInicio)`
  - Recorrido en profundidad. Exige que el vértice exista.
- `std::vector<T> BFS(T verticeInicio)`
  - Recorrido en amplitud. Exige que el vértice exista.
- `bool esConexo()`
  - Verdadero si todos los vértices son alcanzables desde el primero.
- `bool esCiclico(T verticeInicio)` y `bool esCiclico()`
  - Detección de ciclo por BFS desde un vértice o desde el primero.
- `bool esArbol()`
  - Verdadero si `|V| = |E| + 1`, es conexo y acíclico.

Gestión y acceso interno:
- `void copiar(const Grafos<T>& other)` – copia profunda (vértices y arcos).
- `void clear()` – libera toda la memoria.
- `NodoVertice<T>& operator[](int index)` / `NodoVertice<T>& at(int index)`
  - Acceso por índice en la lista de vértices; lanza `runtime_error` si es inválido.

Métodos a implementar por derivados:
- `virtual std::vector<T> getAdyacentes(const T& nodo) const = 0`

---

## Grafos dirigidos: `GrafosDir<T>`

Hereda de `Grafos<T>` e implementa arcos dirigidos.

Operaciones sobre arcos:
- `void agregarArco(const T& origen, const T& destino, const double& peso)`
  - Inserta un arco dirigido `origen -> destino` con `peso`.
  - Excepciones: `runtime_error("Origen/Destino no encontrado")` si falta alguno.
- `void eliminarArco(const T& origen, const T& destino)`
  - Elimina el primer arco `origen -> destino`.
  - Excepciones: `runtime_error("Origen no encontrado")`, `runtime_error("Arco no encontrado en el vertice X")`.
- `void eliminarArco(const T& origen, const T& destino, const double& peso)`
  - Elimina el primer arco `origen -> destino` con `peso` exacto.
  - Excepciones: como arriba.
- `void setPesoArco(const T& origen, const T& destino, const double& peso)`
  - Cambia el peso del primer arco `origen -> destino`.
  - Excepciones: `runtime_error("Origen no encontrado")`, `runtime_error("Arco no encontrado")`.
- `void setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo)`
  - Cambia el peso de un arco que coincida con `pesoAnterior`.
  - Excepciones: `runtime_error("Origen no encontrado")`, `runtime_error("Arco con el peso anterior no encontrado")`.

Consultas:
- `std::vector<T> getSucesores(const T& info) const`
  - Retorna los destinos `info -> *`.
  - Excepciones: `runtime_error("Vertice no encontrado")`.
- `std::vector<T> getPredecesores(const T& info) const`
  - Retorna los vértices que apuntan a `info`.
- `std::vector<T> getAdyacentes(const T& nodo) const override`
  - Alias de `getSucesores`.

Utilidades:
- `GrafosDir<int> mapeado()`
  - Retorna un nuevo grafo con vértices mapeados a enteros `[0..|V|-1]` preservando arcos y pesos.

---

## Grafos no dirigidos: `GrafosNoDir<T>`

Hereda de `Grafos<T>` e implementa arcos no dirigidos (se insertan en ambos extremos). El contador `nArcos` refleja el número lógico de aristas.

Operaciones sobre arcos:
- `void agregarArco(const T& origen, const T& destino, const double& peso)`
  - Inserta arcos en ambas direcciones (origen↔destino) con el mismo `peso`.
  - Excepciones: `runtime_error` si vértices no existen.
- `void eliminarArco(const T& origen, const T& destino)`
  - Elimina la arista lógica (remueve una ocurrencia en cada extremo).
- `void eliminarArco(const T& origen, const T& destino, const double& peso)`
  - Elimina la arista con `peso` específico en ambos extremos.
- `void setPesoArco(const T& origen, const T& destino, const double& peso)`
  - Ajusta el peso de la arista en ambos extremos (primera coincidencia).
- `void setPesoArco(const T& origen, const T& destino, const double& pesoAnterior, const double& pesoNuevo)`
  - Ajusta el peso solo si coincide con `pesoAnterior` (ambos extremos), o lanza excepción.

Consultas:
- `std::vector<T> getVecinos(const T& verticeInfo) const`
  - Retorna vecinos del vértice (adyacentes no dirigidos).
- `std::vector<T> getAdyacentes(const T& nodo) const override`
  - Alias de `getVecinos`.

Utilidades:
- `GrafosNoDir<int> mapeado()`
  - Igual que en dirigidos pero en grafo no dirigido.

---

## Nodos auxiliares

### `NodoVertice<T>`
- Atributos: `T info`, `NodoVertice<T>* sig`, `NodoArco<T>* arco`.
- Constructor: `NodoVertice(const T& info, NodoVertice<T>* sig, NodoArco<T>* arco)`.
- Getters/Setters: `getInfo()`, `getSig()`, `getArco()`, `setInfo(...)`, `setSig(...)`, `setArco(...)`.
- `NodoArco<T>& operator[](int index)` – acceso por índice al arco adyacente, lanza `runtime_error` si fuera de rango.
- Operadores: `operator==` (por `info`), `operator<<` (depuración).

### `NodoArco<T>`
- Atributos: `double peso`, `NodoVertice<T>* info` (destino), `NodoArco<T>* sig`.
- Constructor: `NodoArco(const double& peso, NodoVertice<T>* info, NodoArco<T>* sig)`.
- Getters/Setters: `getPeso()`, `getInfo()`, `getSig()`, `setPeso(...)`, `setInfo(...)`, `setSig(...)`.
- Operadores: `operator==` (mismo destino y peso), `operator<<` (depuración).

---

## Consideraciones de complejidad

- Inserción/eliminación de vértices/arcos: O(1) promedio para insertar al frente; eliminación requiere recorrido O(grado) o O(|V|+|E|) según el caso.
- `getVertices()`: O(|V|).
- `getArcos()/getSucesores()/getVecinos()`: O(grado(v)).
- `DFS/BFS/esConexo`: O(|V|+|E|).
- `esCiclico`: O(|V|+|E|) en la implementación actual basada en BFS.

---

## Ejemplo mínimo (dirigido)

```cpp
#include "grafoDir/GrafosDir.hpp"

int main() {
    GrafosDir<char> g;
    g.agregarVertice('a');
    g.agregarVertice('b');
    g.agregarArco('a','b', 1.0);

    auto succ = g.getSucesores('a');      // => {'b'}
    auto pesos = g.getsPesosArcos('a','b'); // => {1.0}
    auto bfs = g.BFS('a');                // => {'a','b'}
}
```

Para más usos, ver `main.cpp`.
