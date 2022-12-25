/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTunderCode

	Idea General: 
	
	Se solicita buscar el costo minimo a gastar en colocar los Policias de seguridad de las ciudades,
	como tambien la cantidad de formas en que se pueden colocar estos respectivos Policias. Dado que existe
	como propiedad de los Policias poder proteger otras ciuidades siempre y cuando pueden viajar a ellas y 
	poder devolverse. Esto es analogo a encontrar componentes fuertemente conexas dentro de las ciudades, 
	se habla de C.F.C. porque los caminos entre ciudades son "vias dirigas" = Arcos dirigidos. 

	Asi mismo, tener una C.F.C. permite saber por definicion de la misma que todo par de nodo perteneciente 
	a esta permite una conexion (existe un camino). Por tanto, una vez hallada una C.F.C. es determinar
	en ella cual es el nodo con menor costo y cuantas veces aparece este, ya luego es llevar un acumulador
	de esto. Recordamos por el principio fundamental del conteo (Discretas 1), se tiene un conjunto de C.F.C.
	C_1, C_2, ..., C_k y cada una de ellas tiene su dinero minimo y repeticiones, d_i y r_i con 1 <= i <= k, 
	decimos entonces que las formas totales se calculan como repeticiones de C_1 por Repeticiones de C_2, ...
	por repeticiones de C_K, es decir r_1 x r_2 x ... x r_k. Asi mismo, para el dinero minimo es la suma
	d_1 + d_2 + ... + d_k.

	Finalmente, la respuesta viene dado por Dinero Minimo = \sum_{i=1}^{k} d_i y Opciones = \prod_{i=1}^{k} r_i.

*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos
typedef long long ll;
typedef list<int> li;
int N, M;
int maximo = 100005;			// Cota maxima del N.
ll modulo = 1000000007;			// El "Modulo" perdido para determinar el numero para la variable "opciones".
ll infty = 10000000000000000;	// "Infinito".
ll opciones = 1;				// Formas de colocar los Policias de seguridad.
ll dinero_minimo = 0;			// Contiene el dinero minimo usado para colocar los Policias de Seguridad.
int tiempo = 1;

// Estructuras de datos.
vector<int> abierto(maximo, 0);	// Permite saber si un nodo tiene la llamada recursiva activa.
vector<int> disc(maximo, 0);	// Permite contener la informacion del DISCOVERY de cada nodo.
vector<int> low(maximo, 0);		// Permite contener la informacion del LOW de cada nodo.
vector<int> visitado(maximo, 0);// Permite saber si un nodo esta visitado.
vector<li> Grafo(maximo);		// Estructura principal para el Grafo.
stack<int> Pila;				// Pila usada en el Algoritmo de Tarjan.
vector<ll> coste(maximo, 0);	// Vector de costos para cada nodo dado en el problema.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Algoritmo de Tarjan que determina componentes fuertemente conexas para un grafo dirigido. 
void Tarjan (int raiz) {
	abierto[raiz] = 1;		// Marcamos como "abierto" 

	low[raiz] = tiempo++;	// Actualizamos y marcado del Discovery y Low de cada nodo.
	disc[raiz] = low[raiz];

	visitado[raiz] = 1;		// Marcado de nodos en el arreglo de visitado en cada llamada al Tarjan.

	Pila.push(raiz);		// Agregar a la pila el nodo raiz.

	// Nos aseguramos de que hayan nodos adyacentes (de salida - Delta+) a procesar.
	if (!Grafo[raiz].empty()) {
		for(auto it : Grafo[raiz]) {
			if( visitado[it] == 0 ) {
				Tarjan(it);								// Llamada recursiva.
				low[raiz] = min(low[it], low[raiz]);	// Actualizacion del Low.
			}
			else if ( abierto[it] == 1 ) {
				low[raiz] = min(low[raiz], disc[it]);	// Actualizacion del Low.
			}
		}
	}
	
	// Cuando tengamos mismo Low a Discovery entonces hemos encontrado una C.F.C.
	if( disc[raiz] == low[raiz] ) {	
		
		ll cost_Min = infty;	// Iniciamos contador de costo minimo dentro de la C.F.C.
		ll repeticiones = 1;	// Las respeticiones de ese costo minimo.
		int nodo;

		if (!Pila.empty()) {
			while(raiz != Pila.top() ) {
				nodo = Pila.top();
				Pila.pop();
				abierto[nodo] = 0;		// Cerramos la llamada recursiva al nodo popeado.

				// En caso de obtener un costo menor actualizamos.
				if( coste[nodo] < cost_Min ) {
					cost_Min = coste[nodo];
					repeticiones = 1;
				// En caso de encontrar en mismo costo entonces aumentamos repeticiones.
				} else if ( coste[nodo] == cost_Min) {
					repeticiones++;
				}
			} 
		}

		Pila.pop();	// Popeamos la raiz de la stack. Pues esta forma parte de la C.F.C.

		// Realizamos un chequeo del costo minimo y repeticiones para este ultimo elemento de la C.F.C.
		if( coste[raiz] < cost_Min ) {
			cost_Min = coste[raiz];
			repeticiones = 1;
		} else if ( coste[raiz] == cost_Min) {
			repeticiones++;	
		}
		abierto[raiz] = 0;		// Cerramos la llamada recursiva al nodo raiz.

		// Actualizamos tanto el dinero minimo como las opciones para este caso (C.F.C.) con el modulo.
		dinero_minimo += cost_Min;
		opciones = ((opciones%modulo)*(repeticiones%modulo))%modulo;
	}
}

int main() {
	
	// Lectura de datos
	init_code();

	scanf("%d",&N);
	for (int t = 1; t-1 < N; t++) scanf("%d",&coste[t]);

	scanf("%d",&M);
	int a, b;
	for (int t = 0; t < M; t++) {
		scanf("%d%d",&a, &b);
		Grafo[a].push_back(b);
	}
	// Fin lectura de datos.

	// En caso de tener M = 0, entonces no existe ningun camino entre los N nodos datos.
	// Por tanto, procedemos a realizar la suma de todos los costos de cada nodo, pues
	// debemos colocar un Policia de seguridad en cada "nodo".
	if ( M > 0 ) {
		for(int raiz = 1; raiz-1 < N; raiz++) {
			if( visitado[raiz] == 0 ) Tarjan(raiz);	// Realizamos Tarjan para cada nodo no visitado.
		}											// En un grafo puede existen varias componentes conexas.
													// Este for asegura la revision de todos los nodos.
	} else {
		for( int k = 1; k-1 < N; k++ ) dinero_minimo += coste[k];
	}
	
	// Mostrar datos por pantalla. Dinero minimo seguido de la cantidad de formas de colocar los
	// Policias de Seguridad.
	printf("%lld %lld\n", dinero_minimo, opciones);

	return 0;
}