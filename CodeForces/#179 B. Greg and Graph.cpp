/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #179 (Div. 1) B. Greg and Graph

	Idea General: 
	
	Se desea calcular la suma de todas las distancias minimas para todo par de nodo "SOBRANTES" justo 
	antes de eliminar un nodo del Grafo. Para esto es vital el algoritmo de Floyd_Warshall que determina
	esto, solo que este algoritmo va agregando nodos en sus iteracion k determina un camino de tamaño 
	k de ser posible para todo par de nodos, es decir los tamaños CRECIENTES. Este detalle para el problema
	planteado es importante ya que al "Paso k" Greg elimina un nodo lo que genera tamaños de caminos 
	"DECRECIENTES". 

	Por tanto, una vez iniciada la iteracion principal de Floyd-Warshall (que seria camino de tamaño
	1) debemos tener en cuenta leer el ultimo nodo a borrar que es cuando Greg solo le quedan caminos de
	tamaño 1 y al mismo tiempo marcar como visitado dicho nodo a "borrar". Una vez iniciado los fors aniados 
	internos del algoritmo se determinan los caminos minimos correctos para la iteracion k (paso k inverso)
	lo que permite realizar un chequeo, este chequeo revisa si los nodos actuales ya han sido visitados("borrados") 
	esto dice que para el "nodo siguiente a borrar" (el paso k inverso) ya no hay "mas camino" por tanto actualizar
	con la distancia minima al paso N-K+1 que recordemos el la forma inversa de la ejecucion de Greg.

	Finalmente, el vector de respuestas o bien sea llamado dist_mins (vector de distancias minimas)
	tendra la respuestas para cada paso k que se realizó en el Floyd-Warshall. 
*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef long long ll;
int N;				// Variables basicas del problema.
int maximo = 510;	// Cota maxima para el N.

// Estructuras de datos.
vector<vector<ll> > M_ady_dist(maximo, vector<ll> (maximo, 0)); // Matriz de Distancias del grafo.
vector<ll> dist_mins(maximo, 0);								// Permite llevar el acumulador de cada paso en que se elimina un nodo.
vector<int> visitado(maximo, 0);								// Marcador de visitados de los nodos eliminados
vector<int> node_del(maximo, 0);								// Vector de nodos a eliminados.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Algoritmo/Funcion Floyd-Warshall que determina los costos minimos para todo par de nodos en un grafo.
void Floyd_Warshall() {
	for(int k = 1; k-1 < N; k++) { 	// "Paso k" en el greg elimina un nodo, lo que a su vez permite buscar 
									// el nodo agregar en los caminos.
		
		int n_j = node_del[N-k+1];	// Vemos el nodo eliminado en el paso N-k+1. Cuando k=1, estamos en el ultimo 
									// nodo N-K+1 = N, lo cual es camino de tamaño 1 basicamente.

		visitado[n_j] = 1;			// Marcamos como visitado el nodo a eliminar.

		// Los fors anidados permiten iniciar el calculo de los costos minimo del camino de tamaño k.
		for ( int x = 1; x-1 < N; x++ ) {
			for ( int y = 1; y-1 < N; y++ ) {

				// Actualizar la matriz de distancias en funcion del minimo.
				M_ady_dist[x][y] = min(M_ady_dist[x][n_j] + M_ady_dist[n_j][y], M_ady_dist[x][y] );
				
				// Cuando se hallen dos nodos visitados entonces fueron "eliminados" lo que general 
				// el final del camino por tanto realizamos la actualizacion de la distancia minima
				// calculada hasta el momento.
				if ( (visitado[x] == 1) && (visitado[y] == 1) ) {
					dist_mins[N-k+1] += M_ady_dist[x][y];
				}
			}
		}
	}
}

int main() {
	// Mejora de velocidad para el cin y cout.
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	// Lectura de datos.
	init_code();

	cin >> N;
	for ( int i = 1; i-1 < N; i++ ) {
		for ( int j = 1; j-1 < N; j++ ) cin >> M_ady_dist[i][j];
	}
	
	for ( int i = 1; i-1 < N; i++ ) cin >> node_del[i];
	// Fin lectura de datos.

	// Aplicar Floyd-Warshall para determinar el vector de distancias minimas.
	Floyd_Warshall();
	
	// imprimir datos del vector de distancias minimas.
	for ( int k = 1; k-1 < N; k++ ) cout << dist_mins[k] << " ";

	return 0;
}