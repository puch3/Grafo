#ifndef GRAFO_H_
#define GRAFO_H_
#include <list>
#include <set>
#include <map>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo() const;
	private:
		int vertice;
		C costo;
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;

	int devolver_cantidad_arcos() const;

	bool existe_vertice(int vertice) const;

	bool existe_arco(int origen, int destino) const;

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

	void devolver_adyacentes_int(int origen, list<int> & adyacentes) const;

	void agregar_vertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);

	void vaciar();

private:
    map <int, list<Arco>> vertices;
}; // class Grafo: la consideramos como un mapa formado por integer (relacionado al numero al nodo corresp), y una lista de arcos(hijos) q pertenecen a este


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco() //declaramos la clase arco inicializada en vacio
{
    this->vertice = nullptr;
    this->costo = nullptr;
}


template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo) //declaramos la clase arco inicializada con un objeto
{
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const //retorna un integer q forma parte de la clase arco
{
    return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const //retorna un objeto q forma parte de la clase arco
{
    return costo;
}

/*
 * Grafo
 */

// O(1) (documentacion cplusplus)
template <typename C> Grafo<C>::Grafo()
{
    //se generan automaticamente con STL (map())
}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo) // ctor con objeto
{
    this->operator = (otroGrafo);
}

// O(n) n = tamaño del map (documentacion cplusplus)
template <typename C> Grafo<C>::~Grafo()
{
    // se generan automaticamente con STL (~map())
}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    return *this;
}

// O(1) (documentacion cplusplus)
template <typename C> bool Grafo<C>::esta_vacio() const
{
    return vertices.size() == 0; // utilizo una funcion de STL para comparar el tamaño esperado con el de la clase
}

// O(1) (documentacion cplusplus)
template <typename C> int Grafo<C>::devolver_longitud() const
{
    return vertices.size(); // utilizo una funcion de STL para devolver el tamaño de la clase
}

// O(n*e) n=cant de vertices e=cant de arcos
template <typename C> int Grafo<C>::devolver_cantidad_arcos() const
{
    int i=0;
    typename map<int, list<Arco> >::const_iterator it = vertices.begin();
    while (it != vertices.end()){
        typename list<Arco>::const_iterator itv = it->second.begin(); // recorro cada valor de cada clave sumando (facil)
        while (itv != it->second.end()){
            i++;
            itv++;
        }
        it++;
    }
    return i;
}

// O(log n) n= cant de objetos del map (documentacion cplusplus)
template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
    bool existe = false;
    if (vertices.find(vertice) != vertices.end()) // recorro cada nodo del map hasta encontrar el dado o llegar al ultimo
        existe = true;
    return existe;
}
// O(max(log n,e)) n= cantidad de vertices e=cantidad de aristas de origen
template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    bool encontrado = false;
    typename map<int, list<Arco> >::const_iterator it = vertices.find(origen);
    if (it != vertices.end()) {
        typename list<Arco>::const_iterator itA = it->second.begin();
        while (!encontrado && (itA != it->second.end())) {
            if (itA->devolver_adyacente() == destino) {
                return true;
            } else
                itA++;
        }
    }
    return encontrado;
}

// O(max(log n,e)) n= cantidad de vertices e=cantidad de aristas de origen
template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
        bool encontrado = false;
        typename map<int, list<Arco> >::const_iterator it = vertices.find(origen);
        if (it != vertices.end()) {
        typename list<Arco>::const_iterator itA = it->second.begin();
        while (!encontrado && (itA != it->second.end())) {
            if (itA->devolver_adyacente() == destino) {
                return (itA->devolver_costo());
            } else
                itA++;
        }
        }
}

// O(n) n=cant de vertices
template <typename C> void Grafo<C>::devolver_vertices(list<int> & result) const
{
    typename map<int, list<Arco> >::const_iterator it = vertices.begin();
    while (it != vertices.end()) {
        result.push_back(it->first);
        it++;
    }
}


// O(max(log n,e)) n= cantidad de vertices e=cantidad de aristas de origen
template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int, list<Arco> >::const_iterator itV = vertices.find(origen);
    typename list<Arco>::const_iterator it = itV->second.begin();
    while (it != itV->second.end()) {
        adyacentes.push_back(*it);
        it++;
    }
}


// O(max(log n,e)) n= cantidad de vertices e=cantidad de aristas de origen
template <typename C> void Grafo<C>::devolver_adyacentes_int(int origen, list<int> & adyacentes) const
{
    typename map<int, list<Arco> >::const_iterator itV = vertices.find(origen);
    typename list<Arco>::const_iterator it = itV->second.begin();
    while (it != itV->second.end()) {
        adyacentes.push_back(it->devolver_adyacente());
        it++;
    }
}

// O(1) declaracion
template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    vertices[vertice] = list<Arco>();
}

// O(log n) n= cant de vertices (documentacion cplusplus: erase(value))
template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    vertices.erase(vertice);
}

// O(max(log n,e)) n= cantidad de vertices e=cantidad de aristas de origen
template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    bool borrado = false;
    typename map<int, list<Arco> >::iterator it = vertices.find(origen);
    if (it != vertices.end()) {
        typename list<Arco>::iterator itA = it->second.begin();
        while (!borrado && (itA != it->second.end())) {
            if (itA->devolver_adyacente() == destino) {
                typename list<Arco>::iterator itDestructor = itA;//creo un iterador extra para no perder el iterador inicial
                borrado = true;
                it->second.erase(itDestructor);
            } else
                itA++;
        }
    }
    vertices[origen].push_back(Arco(destino, costo));
}

// O(1) (documentacion cplusplus)
template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    vertices[origen].push_back(Arco(destino, costo));
}

// O(e) e=cantidad de adyacentes de origen
template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    bool borrado = false;
    typename map<int, list<Arco> >::iterator it = vertices.find(origen);
    if (it != vertices.end()) {
        typename list<Arco>::iterator itA = it->second.begin();
        while (!borrado && (itA != it->second.end())) {
            if (itA->devolver_adyacente() == destino) {
                typename list<Arco>::iterator itDestructor = itA;//creo un iterador extra para no perder el iterador inicial
                borrado = true;
                it->second.erase(itDestructor);
            } else
                itA++;
        }
    }
}

// O(n) n=cantidad de vertices del grafo (documentacion cplusplus)
template <typename C> void Grafo<C>::vaciar()
{
    vertices.clear();
}

// O(max(n,e)) n=cant de vertices e=cantidad de aristas
template <typename C>
void dfs_forest(const Grafo<C> & grafo, list<int> & orden)
{
    int n = grafo.devolver_longitud();
    bool visitado[n];
    for(int i=1; i<=n; i++)
        visitado[i] = false;

    for(int j=1; j<=n; j++)
        if(!visitado[j])
            DFS(grafo,j, orden, visitado);
}

// O(e) e=cant de aristas ady a v (filminas teoria)
template <typename C>
void DFS(const Grafo<C>& grafo, int v, list<int>& orden, bool visitado[])
{
    visitado[v] = true;
    orden.push_back(v);
    list<int> ady;
    grafo.devolver_adyacentes_int(v, ady);
    list<int> ::iterator it;
    for(it = ady.begin(); it != ady.end(); it++)
        if(!visitado[*it])
            DFS(grafo, *it, orden, visitado);

}

// O(max(n,e)) n=cant de vertices e=cant de aristas (filminas teoria)
template <typename C>
void bfs_forest(const Grafo<C>& grafo, list<int>& orden)
{
    int n = grafo.devolver_longitud();
    bool visitado[n];
    for(int i=1; i<=n; i++)
        visitado[i] = false;

    for(int j=1; j<=n; j++)
        if(!visitado[j])
            BFS(grafo, j, orden, visitado);
}

// O(e) n=cant de vertices e=cant de aristas ady a v (filminas teoria)
template <typename C>
void BFS(const Grafo<C>& grafo, int v, list<int>& orden, bool visitado[])
{
    unsigned int u;
    list<unsigned int> fila;
    list<int> ady;
    list<int>::iterator it;

    visitado[v] = true;
    orden.push_back(v);

    fila.push_back(v);

    while(!fila.empty())
    {
        u = fila.front();
        grafo.devolver_adyacentes_int(u, ady);
        for(it = ady.begin(); it != ady.end(); it++)
        {
            if(!visitado[*it])
            {
                visitado[*it] = true;
                orden.push_back(*it);
                fila.push_back(*it);
            }
        }
        fila.pop_front();
    }
}

//O(#hijos^#niveles)
template <typename C>
void caminos(const Grafo<C> & grafo, int origen, int destino, int l, list<list<int>> & caminos)
{
    set<int> visitados;
    list<int> camino;
    int nivel = l;
    devolver_caminos(grafo, origen, destino, camino, visitados, caminos, l, nivel);
}

// como es una tecnica backtracking O(#hijos^#niveles)
template <typename C>
void devolver_caminos(const Grafo<C> & grafo, int origen, int destino, list<int> & camino, set <int> visitados, list<list<int>> & caminos, int l, int nivel)
{
    visitados.insert(origen);
    camino.push_back(origen);
    nivel--;
    if ((origen == destino) && (nivel<=l))
    {
        caminos.push_back(camino);
        nivel = l;
    }
    else
    {
        list<typename Grafo<C>::Arco> adyacentes;
        grafo.devolver_adyacentes(origen, adyacentes);
        typename list<typename Grafo<C>::Arco>::const_iterator it = adyacentes.begin();
        while (it != adyacentes.end())
        {
            if (visitados.find(it->devolver_adyacente())== visitados.end())
            {
                devolver_caminos(grafo, it->devolver_adyacente(), destino, camino, visitados, caminos, l, nivel);
            }
            it++;
        }
    }
    visitados.erase(visitados.find(origen));
    camino.pop_back();
}

#endif /* GRAFO_H_ */
