/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #257 (Div. 1) B. Jzzhu and Cities

	Idea General: 
	
	Se pide determinar la cantidad de trenes a eliminar tales que sean ineficientes, es decir que no
	acorten "distancia" para llegar a una ciuidad o como tambien trenes repetidos. Para abordar el problema
	se usa el algoritmo de Dijsktra que permite calcular los caminos de costo minimo desde una fuente, en este 
	caso la "Capital" = nodo 1. El problema es analogo a determinar los costos para cada ciuidad usando
	tanto las "rutas" como los "trenes" en el proceso de Dijsktra. 

	Durante el proceso del algoritmo Dijstra, este marca cuando se obtiene un camino con menor costo al que
	posee actualmente entonces decimos que este nodo posee 1 camino y es minimo, cuando este camino sea realmente
	el optimo entonces cualquier aparicion de otro camino igual decimos que tiene 2 caminos minimos, es decir 
	aumentamos contador de caminos "optimos". 

	Una vez finalizado el calculo de Dijsktra entonces decimos que para la cantidad de trenes dados por el problema,
	procesamos la ciudad destino y verificamos si esta ciudad posee un costo menor al del tren, si es el caso
	entonces el tren es innecesario, por otra parte si se da el caso de tener mismo costo entonces verificamos
	la cantidad de caminos que este posea y mientras sea mayor a uno eliminamos el tren. Basicamente, mientras
	el contador de caminos optimos sea mayor que uno entonces tenemos rutas innecesarias de trenes para ese nodo/
	ciudad.

*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef long long ll;
typedef pair<ll, ll> pi;
int N, M, K;					// Variables basicas del problema.
int n_i; pi aux; ll w_t;		// Auxiliares de lectura de datos.
int maximo = 100005;			// Cota maxima para el N.
int m_maximo = 3*maximo;		// Cota maxima para el M.
ll infty = 10000000000000000;	// "infinito".
int del_trains = 0;				// Trenes a eliminar.

// Estructuras de datos.
vector<list<pi> > Grafo(m_maximo);		// Estructura de datos para almacenar los datos del Grafo. 
vector<int> visitados(maximo, 0);		// Marcador de visitados para cada nodo.
vector<int> cant_opt_road(maximo, 0);	// Contador de caminos "optimos" hacia un nodo.
list<pair<int, ll> > rute_train;		// Estructura de datos para guardar el nodo y el costo del tren.
vector<ll> d(maximo, 0);				// Vector de distancias para cada nodo.
priority_queue<pi, vector<pi>, greater<pi> > P_Q;	// Priority Queue para al Dijkstra.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Funcion que permite, una vez calculado el Dijsktra, los trenes a cerrar. 
void delete_trains() {
	int comp; 
	ll t_weight, d_opt;

	// Revisamos para todas las rutas de trenes cuales son ineficientes.
	for ( auto it : rute_train ) {
		comp = it.first; t_weight = it.second; d_opt = d[comp];
		if (d_opt < t_weight) {		// En caso de tener una ruta de tren con costo mayor al optimo 
			del_trains++;			// del nodo, entonces borramos dicho tren.
		} else {
			if ( d_opt == t_weight && cant_opt_road[comp] > 1)  {	// En caso de tener la mismo costo
				del_trains++; cant_opt_road[comp]--;				// entonces revisamos la cantidad de 
			}														// repeticiones que este posee. 
		}
	}
	printf("%d", del_trains); 		// Mostramos por pantalla la cantidad de trenes a eliminar.
}

// Algoritmo que permite determinar en un grafo caminos de costo minimo desde una fuente(nodo raiz).
void Dijsktra() {
	pi node;
	ll ady, w_arc, n_opt;

	// Seteamos la distancia de todos los nodos, menos el fuente, en infinito.
	for( int t = 2; t-1 < N; t++) d[t] = infty;

	P_Q.push(make_pair(d[1], 1)); // Agregamos a la Priority Queue la fuente/raiz.

	while( !P_Q.empty() ) {
		node = P_Q.top();		// Vemos el elemento con menor distancia.
		n_opt = node.second;
		
		P_Q.pop();				// Eliminamos el nodo con menor distancia.

		// El nodo popeado esta visitado, entonces ya fue procesado.
		if (visitados[n_opt] == 0) {

			for ( auto it : Grafo[n_opt] ) {	// Procesamos en funcion de la lista de adyacencia.
				
				ady = it.first; w_arc = it.second;

				if ( d[ady] > d[n_opt] + w_arc ) {		// Relajamos el arco en caso de poderse. 
					d[ady] = d[n_opt] + w_arc;
					P_Q.push(make_pair(d[ady], ady));	// Agregamos el nodo con la distancia actualizada.
					cant_opt_road[ady] = 1;				// Marcamos la cantidad de caminos existentes.
					
				} else if (d[ady] == d[n_opt] + w_arc ){// Si las distancias son iguales entonces tenemos otros posible
					cant_opt_road[ady]++;				// camino, por ende aumentamos la cantidad de caminos existentes.
				}
			}
		}
		visitados[n_opt] = 1;	// Se marca como visitado/procesado el nodo popeado de la P_Queue
								// con es optimo. Por teorema, la distancia de ese nodo a la fuente
								// es optimo al salir de la P_Queue.
	}

	delete_trains();			// Buscamos los trenes a eliminar del grafo(ciudad).
}

int main() {

	// Lectura de datos.
	init_code();

	scanf("%d%d%d",&N,&M,&K);
	
	// Lectura de rutas y la armar la lista de adyacencia.
	for(int t = 0; t < M; t++) {		
		scanf("%d%d%d", &n_i, &aux.first, &aux.second);
		Grafo[n_i].push_back(aux);
		Grafo[aux.first].push_back(make_pair(n_i, aux.second));
	}

	// Lectura de trenes y pesos.
	for(int t = 0; t < K; t++) {
		scanf("%d%d", &n_i, &w_t);
		rute_train.push_back(make_pair(n_i,w_t));
		Grafo[1].push_back(make_pair(n_i,w_t));
	}
	// Fin lectura de datos.

	// Llamada al Dijsktra.
	Dijsktra();

	return 0;
}