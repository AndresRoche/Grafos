# Grafos en C++ (listas de adyacencia)

Implementación de grafos en C++ con listas de adyacencia basadas en nodos enlazados. El proyecto incluye grafos dirigidos y no dirigidos, con soporte para pesos en aristas, y ejemplos de entrada para probar distintas topologías.

## Estructura del proyecto

- **`main.cpp`**: Programa principal con ejemplos de uso/ejecución.
- **`grafoDir/`**: Implementación de la librería de grafos en C++ (plantillas y cabeceras):
  - `GrafosDir.hpp`, `GrafosDir.tpp`: Implementación para grafos dirigidos.
  - `GrafosNoDir.hpp`, `GrafosNoDir.tpp`: Implementación para grafos no dirigidos.
  - `NodoVertice.hpp`, `NodoVertice.tpp`: Nodo de vértice (info del vértice, punteros y adyacencias).
  - `NodoArco.hpp`, `NodoArco.tpp`: Nodo/arista (destino, peso y punteros).

## Documentación de API

Consulta la referencia completa de clases y métodos en [API.md](API.md):

- `Grafos<T>`: base y utilidades comunes.
- `GrafosDir<T>`: arcos dirigidos, sucesores/predecesores, mapeado.
- `GrafosNoDir<T>`: arcos no dirigidos, vecinos, mapeado.

## Requisitos

- Compilador C++ (GCC/Clang) con soporte C++17 o superior.
- `make` (para usar el Makefile del proyecto).
- Linux/WSL o entorno similar.

```bash
make
```

Esto generará el ejecutable `grafos` en la raíz del proyecto (según las reglas del Makefile). Si existe más de un `makefile/Makefile`, `make` tomará el primero aplicable.

Limpieza (si está definida la regla):

```bash
make clean
```

## Ejecución

El programa puede leer grafos desde los archivos de ejemplo. Algunos ejemplos:

- Ejecutar con redirección de entrada desde un archivo de ejemplo:

```bash
./grafos < grafo_estrella_peq.in
./grafos < grafo_ciclo_peq.in
./grafos < grafo_rueda_med.in
```

- Ejecutar con un archivo personalizado:

```bash
./grafos < entrada.txt
```

Revisa `main.cpp` para conocer el formato exacto de entrada/salida admitido por el programa.

## Características principales (librería)

- Representación con listas de adyacencia mediante nodos enlazados.
- Grafos dirigidos (`GrafosDir`) y no dirigidos (`GrafosNoDir`).
- Soporte de pesos en aristas (`NodoArco`).
- Operaciones típicas de grafos (alta/baja de vértices y aristas, sucesores/predecesores, etc.).

Consulta las cabeceras en `grafoDir/` para la API disponible y sus detalles.

## Datos de ejemplo incluidos

- `grafo_estrella_*.in`: grafos en estrella (pequeño/mediano/grande).
- `grafo_ciclo_*.in`: grafos cíclicos.
- `grafo_rueda_*.in`: grafos tipo rueda.
- `grafo_hipercubo_*.in`: hipercubos 3D/4D.
- `entrada.txt`, `entrada_1.txt`: archivos de entrada adicionales.

## Desarrollo y contribución

- Sugerencias:
  - Mantener separadas las interfaces (`.hpp`) y las plantillas/implementaciones (`.tpp`).
  - Añadir pruebas en `tests/` y ejemplos mínimos en `main.cpp`.
- Pull requests y issues son bienvenidos.

## Licencia

A definir. Si necesitas una licencia específica (MIT, Apache-2.0, etc.), indícalo y la añadimos.
