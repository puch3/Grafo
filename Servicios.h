#ifndef SERVICIOS_H_INCLUDED
#define SERVICIOS_H_INCLUDED
#include "Grafo.h"

template <typename C> void dfs_forest(const Grafo<C> & grafo, list<int> & orden);

template <typename C> void dfs(const Grafo<C> & grafo, list<int> & orden, int origen, bool visitado[]);

template <typename C> void bfs_forest(const Grafo<C> & grafo, list<int> & orden);

template <typename C> void bfs(const Grafo<C> & grafo, int origen, bool visitado[]);

template <typename C> void caminos(const Grafo<C> & grafo, int origen, int destino, int limite, list<list<int>> & caminos);

template <typename C> void devolver_caminos(const Grafo<C> & grafo, int origen, int destino, list<int> & camino, set <int> visitados, list<list<int>> & caminos, int l, int nivel)


#endif // SERVICIOS_H_INCLUDED
