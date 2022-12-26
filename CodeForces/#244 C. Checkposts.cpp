/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #244 (Div. 2) C. Checkposts

	Idea General: 
	
	Se solicita buscar el costo minimo a gastar en colocar los Policias de seguridad de las ciudades,
	como tambien la cantidad de formas en que se pueden colocar estos respectivos Policias. Dado que existe
	como propiedad de los Policias poder proteger otras ciuidades siempre y cuando pueden viajar a ellas y 
	poder devolverse. Esto es analogo a encontrar componentes fuertemente conexas dentro de las ciudades, 
	se habla de C.F.C. porque los caminos entre ciudades son "vias dirigas" = Arcos dirigidos. 

	Asi mismo, tener una C.F.C. permite saber por definicion de la misma que todo par de nodo perteneciente 
	a esta permite una conexion (existe un camino). Por tanto, una vez hallada una C.F.C. es determinar
	en ella cual es el nodo con menor costo y cuantas veces aparece este, ya luego es llevar un acumulador
	de esto. 

	Recordamos por el principio fundamental del conteo (Estructuras Discretas 1), se tiene un conjunto de 
	C.F.C. C_1, C_2, ..., C_k y cada una de ellas tiene su dinero minimo y repeticiones, d_i y r_i con 
	1 <= i <= k, decimos entonces que las formas totales se calculan como (Repeticiones de C_1 por 
	repeticiones de C_2, ... por repeticiones de C_K), es decir (r_1 x r_2 x ... x r_k). 
	Asi mismo, para el dinero minimo es la suma (d_1 + d_2 + ... + d_k).

	Finalmente, la respuesta viene dado por Dinero Minimo = \sum_{i=1}^{k} d_i
	y Opciones = \prod_{i=1}^{k} r_i.

*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos
typedef long long ll;
typedef list<int> li;
int N, M;
int maximo = 100005;			// Cota maxima del N.
ll modulo = 1000000007;			// El "Modulo" perdido para determinar el numero para la variable "options".
ll infty = 10000000000000000;	// "Infinito".
ll options = 1;					// Cantidad de formas de colocar los Policias de seguridad.
ll min_money = 0;				// Contiene el dinero minimo usado para colocar los Policias de Seguridad.
int c_time = 1;					// Contador(time) para el uso del algoritmo Tarjan.

// Estructuras de datos.
vector<int> opened(maximo, 0);		// Permite saber si un nodo tiene la llamada recursiva activa.
vector<int> disc(maximo, 0);		// Permite contener la informacion del DISCOVERY de cada nodo.
vector<int> low(maximo, 0);			// Permite contener la informacion del LOW de cada nodo.
vector<int> visited(maximo, 0);		// Permite saber si un nodo esta visitado.
vector<li> Graph(maximo);			// Estructura principal para el Grafo.
stack<int> Pila;					// Pila usada en el Algoritmo de Tarjan.
vector<ll> police_cost(maximo, 0);	// Vector de costos de policias para cada nodo/ciudad.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Algoritmo de Tarjan que determina componentes fuertemente conexas para un Grafo dirigido. 
void Tarjan (int root) {
	opened[root] = 1;		// Marcamos como "abierto" 

	low[root] = c_time++;		// Actualizamos y marcado del Discovery y Low de cada nodo.
	disc[root] = low[root];

	visited[root] = 1;		// Marcado de nodos en el arreglo de visitado en cada llamada al Tarjan.

	Pila.push(root);		// Agregar a la pila el nodo raiz.

	// Nos aseguramos de que hayan nodos adyacentes (de salida/Delta+) a procesar.
	if (!Graph[root].empty()) {
		for(auto it : Graph[root]) {
			if( visited[it] == 0 ) {
				Tarjan(it);								// Llamada recursiva.
				low[root] = min(low[it], low[root]);	// Actualizacion del Low.
			}
			else if ( opened[it] == 1 ) {
				low[root] = min(low[root], disc[it]);	// Actualizacion del Low.
			}
		}
	}
	
	// Cuando tengamos mismo Low a Discovery entonces hemos encontrado una C.F.C.
	if( disc[root] == low[root] ) {	
		
		ll cost_Min = infty;	// Iniciamos contador de costo minimo dentro de la C.F.C.
		ll repetitions = 1;		// Las respeticiones de ese costo minimo.
		int nodo;

		if (!Pila.empty()) {
			while(root != Pila.top() ) {
				nodo = Pila.top();
				Pila.pop();
				opened[nodo] = 0;		// Cerramos la llamada recursiva al nodo poped.

				// En caso de obtener un costo menor actualizamos.
				if( police_cost[nodo] < cost_Min ) {
					cost_Min = police_cost[nodo];
					repetitions = 1;
				// En caso de encontrar en mismo costo entonces aumentamos repetitions.
				} else if ( police_cost[nodo] == cost_Min) {
					repetitions++;
				}
			} 
		}

		Pila.pop();	// Popeamos la root de la stack. Pues esta forma parte de la C.F.C.

		// Realizamos un chequeo del costo minimo y repetitions para este ultimo elemento de la C.F.C.
		if( police_cost[root] < cost_Min ) {
			cost_Min = police_cost[root];
			repetitions = 1;
		} else if ( police_cost[root] == cost_Min) {
			repetitions++;	
		}
		opened[root] = 0;		// Cerramos la llamada recursiva al nodo root.

		// Actualizamos tanto el dinero minimo como las opciones para este caso (C.F.C.) con el modulo.
		min_money += cost_Min;
		options = ((options%modulo)*(repetitions%modulo))%modulo;
	}
}

int main() {
	
	// Lectura de datos
	init_code();

	scanf("%d",&N);
	for (int t = 1; t-1 < N; t++) scanf("%d",&police_cost[t]);

	scanf("%d",&M);
	int a, b;
	for (int t = 0; t < M; t++) {
		scanf("%d%d",&a, &b);
		Graph[a].push_back(b);
	}
	// Fin lectura de datos.

	// En caso de tener M = 0, entonces no existe ningun camino entre los N nodos dados.
	// Por tanto, procedemos a realizar la suma de todos los costos de cada nodo, pues
	// debemos colocar un Policia de seguridad en cada "nodo".
	if ( M > 0 ) {
		for(int root = 1; root-1 < N; root++) {
			if( visited[root] == 0 ) Tarjan(root);	// Realizamos Tarjan para cada nodo no visitado.
		}											// En un Graph puede existir varias componentes conexas.
													// Este for asegura la revision de todos los nodos.
	} else {
		for( int k = 1; k-1 < N; k++ ) min_money += police_cost[k];
	}
	
	// Mostrar datos por pantalla. Dinero minimo seguido de la cantidad de formas de colocar los
	// Policias de Seguridad.
	printf("%lld %lld\n", min_money, options);

	return 0;
}