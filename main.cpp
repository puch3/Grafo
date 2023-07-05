#include "Grafo.h"
#include "iostream"
#include <iostream>
#include <fstream>

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    E" << *v << "-> E" << ady->devolver_adyacente() << " (" << ady->devolver_costo() << "kms)\n";
			ady++;
		}
		v++;
	}
	return salida;
}

//GREEDY///////////////////////////////////////////////
/*void prim (Grafo<int> & g, Grafo<int> & t, int & costo, int & costo_computacional)
{
    int n = g.devolver_longitud()+1;
    int visitado[n];
    for (int i=1; i<n; i++){ // INICIALIZACION
        visitado[i]=0;
    }
    int dis[n];
    for (int i=1; i<n; i++){ // INICIALIZACION
        dis[i]=100000;
    }
    costo_computacional = n*n;
    visitado[1]=1;
    dis[1]= 0;
    int actual = 1;
    int recorrido = 1; // ME PARO EN UNO Y LO MARCO COMO VISITADO
    int pos[n];
    while (recorrido < n){ // ARRANCO EL RECORRIDO PRIM
        t.agregar_vertice(actual);
        for (int i=1; i<n; i++){
            costo_computacional+=3;
            if (g.existe_arco(actual,i)){
                if(visitado[i]==0){
                    if(dis[i] > (g.costo_arco(actual,i))){ // SI DONDE ESTOY PARADO ES MEJOR LO PONGO EN DIS[]
                        dis[i] = g.costo_arco(actual,i);
                        pos[i] = actual;
                    }
                }
            }
        }
        int distancia = 10000;
        for(int i=1; i<n; i++){
            if (visitado[i]==0){
                if (dis[i] < distancia){
                    distancia = dis[i]; ///DECLARO NUEVO ACTUAL
                    actual = i;
                }
            }
        }
        costo_computacional+=1;
        if (!t.existe_arco(pos[actual],actual)){
            t.agregar_arco(pos[actual], actual, dis[actual]); /// SI NO ESTA AGREGADO AL ARBOL DE RECUBRIMIENTO LO AGREGO
            costo += dis[actual];
        }
        visitado[actual] = 1; // MARCO COMO VISITADO
        recorrido ++; // CONTINUO EL RECORRIDO
    }
}*/
/*
PRIM ( G (V, A) ) {
//inicialización
S[1] = 1; // vértice 1 (inicial)
T // árbol de recubrimiento
for (i=2; i<=n; i++) {
MENOR_COSTO [i]= Costo [1,i]; //costo de la arista (i, MAS_CERCANO[i])
MAS_CERCANO [i]= 1; // vértice más cercano a i en el árbol
S[i]= 0; } // vértice i ϵ V-S
for (i=2; i<=n; i++) {
elegir w | MENOR_COSTO [w] sea mínimo y S[w]=0; // W ϵ V-S
S[w] = 1;
T = T U {w, MAS_CERCANO[W]};
for (j=2; j<=n; j++)
if (S[j]==0 && (Costo [w,j] < MENOR_COSTO [j])){ //actualizar costos
MENOR_COSTO [j]= Costo [w,j];
MAS_CERCANO [j]= w;
}
}
} //end*/

void prim(Grafo<int> & g, Grafo<int> & T, int menor_costo[], int & costo_computacional){
    int n = g.devolver_longitud();
    int S[n];
    S[1]=1;
    int mas_cercano[n];
    for (int i=2; i<=n; i++){
        costo_computacional++;
        if (g.existe_arco(1,i)){
            costo_computacional++;
            menor_costo[i]= g.costo_arco(1,i);
            mas_cercano[i]= 1;
            S[i]=0;
        }
    }
    int w=1;
    for (int i=2; i<=n; i++){
        int costos_act = 10000;
        for (int j=2; j<=n; j++){
            if ((costos_act > menor_costo[i]) && (S[j]==0)){
                w=j;
                costos_act = menor_costo[j];
            }
            S[w]=1;
            T.agregar_vertice(w);
            T.agregar_arco(w, mas_cercano[w], menor_costo[w]);
            for (int k=2; k<=n; k++){
                costo_computacional++;
                if (g.existe_arco(w,k)){
                    costo_computacional++;
                    if ((S[k]==0)&&(g.costo_arco(w,k)< menor_costo[k])){
                        costo_computacional++;
                        menor_costo[k]= g.costo_arco(w,k);
                        mas_cercano[k]=w;
                    }
                }
            }
        }
    }
}

//BACKTRACKING/////////////////////////////////////////////////////////////////////////
// si es menos costosa es mejor.
bool es_mejor(int solucion[], int sol_actual[], int n, int costos[], int costos_act[]){
    for (int i=1; i<=n; i++){
        if ((costos[i]>=costos_act[i])||(solucion[i]==-1)){
            if (sol_actual[n]!=(-1) || sol_actual[n-1]!=-1){
                return true;
            }
        }
    }
    return false;
}

//reemplazo mi solucion optima por la actual.
bool reemplazar(int solucion[], int sol_actual[], int n, int costos_act[], int costos[]){
    for (int i=1; i<=n; i++){
        solucion[i]=sol_actual[i];
        costos[i]= costos_act[i];
    }
}

//funcion madre backtracking
void backtracking(Grafo<int> & g, int solucion[], int sol_actual[], int costos_act[], int costos[], int n, int v, int & costo_computacional)
{
    // como es una funcion recursiva elegimos el costo del peor caso para su complejidad(else)
    if (es_mejor(solucion, sol_actual, n, costos, costos_act)){
        reemplazar(solucion, sol_actual, n, costos_act, costos); // SI ES MEJOR MI SOL_ACTUAL LA REEMPLAZO
    }
    else {
        int ady;
        list<int> L_ady;
        L_ady.clear();
        g.devolver_adyacentes_int(v, L_ady); // HAGO UNA LISTA DE ADYACENTES DEL VERTICE DONDE ESTOY PARADO
        costo_computacional++; // voy sumando las veces que utiliza O(e)
        while(!L_ady.empty()){
            ady = L_ady.front();
            costo_computacional++;
            if (g.existe_arco(v,ady)){
                costo_computacional++;
                if (g.costo_arco(v, ady)< costos_act[ady]){ // REEMPLAZO EL ARCO SOLAMENTE SI ES MEJOR AL QUE TENGO ACTUALMENTE
                    costo_computacional++;
                    costos_act[ady]= g.costo_arco(v, ady);
                    sol_actual[ady]= v; // SI ES MEJOR ME CORRO DE VERTICE
                    backtracking(g, solucion, sol_actual, costos_act, costos, n, (v+1), costo_computacional);
                }
            }
            L_ady.pop_front();
        }
    }
}

//menu basico para hacer mas facil la ejecucion
void ejecutar(Grafo<int> & j){
	cout << "insertar algoritmo a utilizar: (0=greedy, 1=backtracking) ";
	int opcion;
	cin >> opcion;
	int costo_computacional;
    int costo = 0;
    cout << "TUNELES A REALIZAR: " << endl;
    int n = j.devolver_longitud();
	if (opcion == 0){
        Grafo<int> t;
        int menor_costo[n];
        cout << endl << "-ALGORITMO PRIM-" <<endl;
        prim(j, t, menor_costo, costo_computacional);
        cout << "\n" << t << "\n";
        for (int i=2; i<=n; i++){
            costo+= menor_costo[i];
        }
	}
	else{
        int solucion[n];
        int sol_actual[n];
        int costos_actual[n];       //INICIALIZACION DE ESTRUCTURAS
        int costos[n];
        int v = 1;
        for (int i=1; i<=n; i++){
            solucion[i]=-1;
            sol_actual[i]=-1;
            costos_actual[i]=10000;
            costos[i]=10000;
        }
        cout << endl << "-BACKTRACKING-" << endl;
        backtracking(j, solucion, sol_actual, costos_actual, costos, n, v, costo_computacional);
        for (int i=2; i<=n; i++){
            cout << endl << " E"<< solucion[i] << "-> E" << i << "(" << costos[i] << "kms)";
            costo+= costos[i];
        }
        cout << endl;
	}
    cout << endl;
    cout << "costo: " << costo << "kms." << endl;
    cout << "costo computacional: e*" << costo_computacional << " (e=cant de aristas del vertice con mas cantidad de estas)";
}

// metodo para procesar el archivo txt y convertirlo en la estructura a convenir (grafo con costos asociados)
void procesar_archivo(string origen, Grafo<int> & g)
{
    ifstream archivo(origen);
    if (!archivo.is_open())
        cout << "No se pudo abrir el archivo: " << origen << endl;
    else {
        string linea;
        getline(archivo, linea);
        int cantidad_tuneles = atoi(linea.c_str());

        cout << "Se cargaran " << cantidad_tuneles << " tuneles." << endl;

        //Leemos de una linea completa por vez (getline).
        while (getline(archivo, linea)) {
            //Primer posición del separador ;
            int pos_inicial = 0;
            int pos_final = linea.find(';'); //Primer posición del separador ;
            int estacion_1 = stoi(linea.substr(pos_inicial+1, pos_final - pos_inicial)); //substr(pos_inicial, cant_caracteres)

            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial); //Primer posición del separador ; buscando desde pos_inicial
            int estacion_2 = stoi(linea.substr(pos_inicial+1, pos_final - pos_inicial));

            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            int distancia = stoi(linea.substr(pos_inicial, pos_final - pos_inicial));
            if (!g.existe_vertice(estacion_1))
                g.agregar_vertice(estacion_1);
            if (!g.existe_vertice(estacion_2))
                g.agregar_vertice(estacion_2);
            g.agregar_arco(estacion_1, estacion_2, distancia);
        }
        cout << "carga completa." << endl;
    }
}


int main(int argc, char **argv)
{
	Grafo<int> g;
/*
	// Cargamos un grafo dirigido
	// Primero los vértices
	g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	g.agregar_vertice(6);
	g.agregar_vertice(7);

	// Luego los arcos
	g.agregar_arco(1, 2, 1);
	g.agregar_arco(1, 3, 1);
	g.agregar_arco(1, 4, 1);
	g.agregar_arco(2, 6, 2);
	g.agregar_arco(3, 5, 3);
	g.agregar_arco(4, 7, 4);
	g.agregar_arco(5, 6, 5);

	// Mostramos el grafo
	cout << "Estructura del grafo:\n" << g << "\n";
*/

    Grafo<int> j;
    procesar_archivo("./datasets/dataset2.txt", j);
	cout << "TUNELES POSIBLES:\n" << j << "\n";
    ejecutar(j);
	return 0;
}

