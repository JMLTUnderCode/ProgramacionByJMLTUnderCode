/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Good Bye 2014 - A. New Year Transportation

	Idea General: 
	
	Se lee una linea N-1 elementos en el cual el indice i contiene un numero el cual representa 
	el valor de desplazamiento que este debe realizar. Aplicando una vision de grafos, notemos que
	siempre se parte del indice 1, es decir NODO 1, en esta posicion de la "linea de N-1" contiene
	un valor el cual debes aumentar el indice 1, por tanto, no quiere decir que ahora nos "transportamos"
	al nodo i + a_i, asi sucesivamente hasta llegar a la celda N-1. 

	De esta forma, armamos un grafo cuya raiz sea el nodo 1. Se aplica DFS sobre este grafo y cuando
	se este procesando los nodos entonces verificamos que efectivamente la "celda destino" esta incluida
	en el recorrido DFS y podremos dar afirmacion de que las personas puedes ir a la celda T con existo,
	de lo contrario en el grafo formado no existe el nodo/celda T por tanto no existe camino posible.

*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef vector<int> vi;
typedef list<int> li;
typedef vector<list<int> > vli;
int N, T;						// Variables basicas del problema.
int v;							// Nodo extraido de la pila.
int	aux = 1;					// Recreador del camino formado por la transportacion.
int maximo = 3*1e4+5;			// Cota maxima para el N.
li ady;							// Lista de adyacencia para la celda en cuestion.

// Estructuras de datos.
vi visitados(maximo, 0);		// Vector de visitados para cada nodo procesado.
vi transportation(maximo, 0);	// Vector de indices de desplazamiento para cada nodo.
vli Graph(maximo);				// Grafo formado por el camino posible partiendo de celda 1.
stack<int> Pila;				// Estructura stack para el uso del DFS.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Funcion DFS para el tracking de indices desplazados por la transportacion de cada indice(nodo).
void DFS(int raiz){
	
	Pila.push(raiz);
	visitados[raiz] = 1;

	while (!Pila.empty()) {
		v = Pila.top();
		Pila.pop();
		
		ady = Graph[v];
		for ( auto it : ady ) {
			if (visitados[it] == 0) {
				visitados[it] = 1;
				Pila.push(it);			
			}
			if (it == T) {
				printf("%s\n", "Yes"); return;
			}
		}
	}
	printf("%s\n", "No"); return;
}

int main() {
	
	// Lectura de datos.
	init_code();

	scanf("%d%d", &N, &T);

	for (int k = 1; k < N; k++) scanf("%d", &transportation[k]);
	// Fin lectura de datos.

	while (aux < N) {
		Graph[aux].push_back(aux+transportation[aux]);
		aux += transportation[aux];
	}
	
	// Llamamos DFS para el primer nodo/celda 1.
	DFS(1);

	return 0;
}