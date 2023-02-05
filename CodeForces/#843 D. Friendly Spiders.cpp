/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #843 (Div. 2) D. Friendly Spiders

	** Idea General para el problema: **
	Dado que puede haber un densa cantidad de arcos para la condicion planteada para las arañas,
	por ejemplo todas las arañas con patas par se conectan entre si, esto quiere decir que por
	cada araña tendra N-1 amigas, por tanto complex BFS pasa de O(|N|+|E|) -> O(|N|^2). 

	Por tanto, se procede con el uso de un grafo con el numero arañas y un grafo auxiliar 
	que tendrá nodos primos. Los elementos adyacentes en el grafo de arañas serán nodos
	del grafo auxiliar y los elementos adyacentes en el grafo auxiliar serán nodos del
	grafo original. La relacion que estos forman será que los nodos adyacentes a una araña
	seran divisores primos de su cantidad de patas, asi mismo la relacion que presenta el grafo 
	auxiliar es que los adyacentes son arañas a los cuales el nodo divide sus patas.
	Ej. spider -> 1  2  3  4  5  6  7
	    legs   -> 2 14  9  6  8 15 11
	Graph Spiders:			Graph Div. Primes:
	1 -> 2    (Div. primo de  2)	2  -> 1, 2, 4, 5 (Araña div. por  2)
	2 -> 2, 7 (    "      de 14)	3  -> 3, 4, 6	 (Araña div. por  3)
	3 -> 3    (    "      de  9)	5  -> 6		 (Araña div. por  5)
	4 -> 2, 3 (    "      de  6)	7  -> 2 	 (Araña div. por  7)
	5 -> 2    (    "      de  8)	11 -> 7 	 (Araña div. por 11)
	6 -> 3, 5 (    "      de 15)	
	7 -> 11   (    "      de 11)	
	
	Luego es aplicar un BFS sobre estos grafos, claramente ignorando los nodos del grafo de
	primos dado que estos actuan como un auxilizar para el fin de determinar que arañas estan
	conectadas.

	IMPORTANTE: Para efectos de solucion en codeforces, se comentan variables, estructuras 
	de datos, entre otras cosas para evitar el exceso de memoria innecesaria en la corrida
	del programa. Como tambien el comentado de otras funciones que no correran en este caso.
	En esencia se ahorra un 50% en memoria. Por otra parte, tuve que cambiar
	todo a long long debido a problemas con el calculo de primos y funciones de 
	lectura/escritura como scanf/prinft, sigo sin entender porque el "for" de Cribas de
	Eratosthenes terminaba alrededor de cnt = 45k.

	** Actualizacion de Libreria/Class: **
	1. Inclusion de nueva variable en clase NODE, "father" para llevar un tracker del camino
	formado en busquedas de grafos(BFS, DFS). Asi mismo, para la clase Graph se agrego un 
	vector de nodos tackers para el mismo objetivo.

	2. inclusion de una nueva variable en clase NODE, "level" para llevar un nivel de cada nodo
	en las busqueda de grafos (BFS/DFS).

	3. Modificacion ligera de la funcion "add_arc" por condiciones del problema. 
	
	4. Mejora de la funcion "path_between" con el uso de father trackers y quitar la recursion.
	
*/

#include <bits/stdc++.h>

using namespace std;
/*************************************************************************************************/
#define pb push_back
typedef vector<vector<int> > vvi;
typedef vector<int> vi;
typedef vector<vector<long long>> vvll;
typedef vector<long long> vll;
typedef long long ll;

// Class/Struct NODE para informacion de un nodo en grafos. Implementada por Junior Lara.
class NODE{
public:
	ll n;		// Numero del nodo.
	ll visited;	// Identificador de visitado.
	/*
	ll n_ady;	// Numero de nodos adyacentes a n.
	ll min_cost;	// Costo del nodo.
	string color;	// Color del nodo.
	ll range;	// Rango para busqueda BFS/DFS.
	*/
	ll father;	// Nodo padre del nodo n;
	ll level;	// Para saber el nivel de un nodo en la busqueda BFS\DFS.

	// Constructor DEFAULT.
	NODE() {
		n = 0; visited = 0; 
		//n_ady = 0; min_cost = 0; color = ""; range = 0; 
		father = 0; level = 0;
	}
	// Constructor basico.
	NODE(ll _id, ll _vis) : n(_id), visited(_vis) {
		//n_ady = 0; min_cost = 0; color = ""; range = 0; 
		father = 0; level = 0;
	}
	/*// En caso de necesitar Num nodo, isVisitado y color del nodo.
	NODE(ll _id, ll _vis, string _color) : n(_id), visited(_vis), color(_color) {
		n_ady = 0; min_cost = 0; range = 0; father = 0; level = 0;
	}
	// En caso de necesitar Num nodo, isVisitado y costo del nodo.
	NODE(ll _id, ll _vis, ll _cost) : n(_id), visited(_vis), min_cost(_cost) {
		n_ady = 0; color = ""; range = 0; father = 0; level = 0;
	}*/
};

typedef vector<vector<NODE>> vvn;
typedef vector<NODE> vn;

// Fin de la Class//Struct NODE.
/*************************************************************************************************/

// Inicializacion de variables y estructuras de datos.
const ll MaxN= (3*1e5) + 5;	// Numero maximo de nodos(arañas).
ll N;				// Numero de nodos(arañas).
ll S, T;			// Nodos(arañas) en los cuales se transfieren el mensaje.
vll spider_legs(MaxN);		// Vector que contiene el numero de patas de cada añara.
vll legs_divisors(MaxN, 1);	// Vector que contiene el divisor primo para cada indice, el
				// indice simula el numero de patas de una araña.

/*************************************************************************************************/
// Libreria Graph implementada por Junior Lara.

class Graph{
	ll n_nodes;		// Numero de nodos en el grafo.
	ll type_graph;		// Tipo de grafo: 1 = Lista Adyacencia y 2 = Matriz de Adyacencia.
	vvll lists;		// Estructura para la lista de adyacencia.
	vvll Matriz;		// Estructura para la matriz de adyacencia.

public:
	vn Nodes;		// Vector para guardar cada nodo de class NODE.
	ll NoNvis = 0;		// Valor default de No Visitado.
	vll father_tracker;	// Vector de nodos para tener un track de los nodos padres de cada nodo.

	// Constructor principal del grafo. Se espeficica el tamaÑo y el tipo de grafo,
	// 1 para el caso de usar listas de adyacencias, 2 para el caso de matrices.
	Graph(ll type, ll size) : type_graph(type), n_nodes(size) {
		assert(type > 0 && type < 3);
		vll newFatherT(size+1, 0); father_tracker = newFatherT;

		if (type == 1) { 					// Listas de Adyacencias.
			vvll newLists(size+1); lists = newLists;
			vn newNodes(size+1); Nodes = newNodes;

		} else if (type == 2) { 				// Matriz de Adyacencias.
			vvll newMatriz(size+1, vll (size+1));
			Matriz = newMatriz;

		} else {						// Error de tipo.
			printf("%s", "Error: Tipo de grafo especificado (Argument).");
		}
	}

	// Funcion que permite agregar un nodo al grafo, en caso de grafo tipo 1 entonces un pushback
	// de una vector vacio simulando una nueva posicion disponible en la estructura del grafo.
	// Para el caso grafo tipo 2 entonces es recrear una nueva matriz con 1 unidad fila/columna mas
	// y con el contenido de la antigua matriz.
	void add_node() {
		n_nodes++;
		if (type_graph == 1) {
			lists.pb(vll ());
		} else {
			vvll aux(n_nodes+1, vll (n_nodes+1));
			for (ll i = 1; i < n_nodes; i++ ) {
				for (ll j = 1; j < n_nodes; j++ ) aux[i][j] = Matriz[i][j];
			}
			Matriz = aux;
		}
	}

	// Funcion que permite agregar un arco entre dos nodos existentes en el grafo. 
	// En caso de grafo tipo 1 entonces realizamos el pushback del elemento a su respectivo
	// vector de adyacencia. En caso de grafo tipo 2 entonces se marca en la posicion dada en 1.
	// Adicionalmente, se procede agregar el nodo con formado NODE.
	void add_arc(ll n1, ll n2) {
		if ( type_graph == 1 ) {
			lists[n1].pb(n2);
			if(Nodes[n1].n == 0) Nodes[n1] = NODE (n1, 0); //Nodes[n1].n_ady++;
			if(Nodes[n2].n == 0) Nodes[n2] = NODE (n2, 0);
		} else {
			Matriz[n1][n2] = 1;
		}
	}

	// Funcion que permite extraer para un nodo dado x como argumento su vector de elementos
	// adyacentes, en caso de listas se expresa por tipo de grafo 1, en caso de matrices entonces
	// por tipo de grafo 2 extraemos los elementos marcado con 1 en la fila respectiva de la matriz.
	vll get_ady(ll x) {
		if (type_graph == 1) {
			return lists[x];
		} else {
			vll aux;
			for (ll k = 1; k-1 < n_nodes; k++) if (Matriz[x][k] == 1) aux.pb(k);
			return aux;
		}
	}

	// Funcion que retorna el arbol DFS para un elemento root. Este "arbol dfs" consta
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo DFS.
	vn DFS_tree(NODE root) {	
		// Inicializacion, push, marcado de variables y nodos.
		//ll visited[n_nodes+1];
		stack<NODE> S;

		root.visited = 1;
		S.push(root);

		ll cnt = 0;
		vn aux(n_nodes+1);

		// Calculo del arbol DFS mediante la estructura Pila(Stack).
		while ( !S.empty() ) {
			NODE v = S.top();
			S.pop();
			aux[cnt++] = v;

			if(type_graph == 1) {
				for ( auto it : lists[v.n]) {
					if ( Nodes[it].visited != 1 ) {
						Nodes[it].visited = 1; S.push(Nodes[it]);
					}
				}
			} else {
				//Por implementar
			}
		}

		// Se procede a extrar el arbol DFS respectivo del vector aux, esto pautado
		// por la variable cnt.
		vn tree(cnt);
		for(ll k = 0; k < cnt; k++) tree[k] = aux[k];

		return tree;
	}

	// Funcion que retorna el arbol BFS para un elemento root. Este "arbol bfs" consta
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo BFS.
	vn BFS_tree(NODE root) {
		// Inicializacion, push, marcado de variables y nodos.
		//ll visited[n_nodes+1];
		queue<NODE> Q;

		root.visited = 1;
		Q.push(root);

		ll cnt = 0;
		vn aux(n_nodes+1);

		// Calculo del arbol BFS mediante la estructura Cola(Queue).
		while ( !Q.empty() ) {
			NODE v = Q.front();
			Q.pop();
			aux[cnt++] = v;

			if(type_graph == 1) {
				for ( auto it : lists[v.n]) {
					if ( Nodes[it].visited != 1 ) {
						Nodes[it].visited = 1; Q.push(Nodes[it]);
					}
				}
			} else {
				//Por implementar
			}
		}

		// Se procede a extrar el arbol BFS respectivo del vector aux, esto pautado
		// por la variable cnt.
		vn tree(cnt);
		for(ll k = 0; k < cnt; k++) tree[k] = aux[k];

		return tree;
	}

	// Funcion que permite calcular el camino entre dos nodos dados mediante el uso de
	// metodo/algoritmo DFS, esto por implementacion iterativa y tracker de padres.
	// Se retorna true en caso de encontrar el camino y antes de esto se muestra por
	// pantalla, de lo contrario se retorna false.
	bool path_between(ll i, ll f) {
		if( i == f ) print_vi({i}); return true;

		stack<NODE> S;
		Nodes[i].visited = 1;
		Nodes[i].level = 1;
		S.push(Nodes[i]);

		bool finded = false;
		while( !S.empty() ){
			NODE v = S.top();
			S.pop();

			for( auto it : get_ady(v.n)){
				if( Nodes[it].visited != 1 ){
					Nodes[it].visited = 1;
					Nodes[it].level = v.level + 1;
					Nodes[it].father = v.n;
					if( it == f ) finded = true; break;
				}
			}
			if(finded) break;
		}

		if(finded){
			ll sz = Nodes[f].level, curr = f;
			vll path(sz);
			for(ll cnt = sz-1; cnt > -1; cnt--){
				path[cnt] = f;
				curr = Nodes[curr].father;
			}
			print_vi(path); return true;
		} else {
			return false;
		}
	}

	// Funcion que realiza un BFS para una seria de raices "LIMITADO A" un cierto rango de amplitud 
	// de busqueda, es decir se tiene un nodo ROOT con rango DIST por tanto todo nodo a distancia
	// <= DIST del ROOT sera procesado en el BFS. Retorna true en caso de recorrer todos los nodos y
	// que en cada nodo fue visitado al menos 1 vez, en caso de haberse topado con un nodo visitado
	// se llega un conteo de nodos visitados mas de una vez (crashes).
	/*
	bool BFS_lim_to(ll root, ll dist) {
		queue<NODE> C;
		Nodes[root].visited = 1;
		Nodes[root].range = dist;
		C.push(Nodes[root]);

		ll cnt_vis = 1;
		ll crashes = 0;

		while(!C.empty()){
			NODE v = C.front();
			C.pop();

			if( v.range > 0 ){
				for(auto it : lists[v.n]){
					if ( Nodes[it].visited != 1) {
						cnt_vis++;
						Nodes[it].visited = 1;
						Nodes[it].range = v.range - 1;
						C.push(Nodes[it]);
					} else {
						crashes++;
					}
				}
			}
		}
		
		// Sino se visitaron todos los nodos, entonces no cumple la condicion.
		if(cnt_vis < n_nodes) return false;

		return true;
	}
	*/

	// Funcion para determinar si un grafo es bipartito o no. Esto se realiza mediante la
	// coloracion del grafo con 2 colores con recorrido BFS. Si es posible colorear el grafo 
	// tal que dos nodos adyacentes tengan dos colores distllos, en caso afirmativo es bipartito. 
	// Modificacion particular del problema: Se realizan cambios para determinar los arcos
	// posibles que pueden agregarse talque sea un grafo bipartito.
	/*
	ll isBipartito(ll n){
		// Inicializacion de variables, datos y push's.
		queue<NODE> C;
		Nodes[n].visited = 1;
		Nodes[n].color = "Blanco";
		C.push(Nodes[n]);
		ll cnt_n = 0;

		// Inicio del recorrido BFS.
		while( !C.empty() ){
			NODE v = C.front();
			C.pop();

			for(auto it : lists[v.n]){
				if( Nodes[it].visited != 1 ) {
					Nodes[it].visited = 1;
					Nodes[it].color = (v.color == "Blanco") ? "Negro" : "Blanco";
					if (Nodes[it].color == "Negro") cnt_n++;
					C.push(Nodes[it]);
				}

			}

		}
		
		// Conteo de arcos posibles para satisfacer la condificion de Biparticion.
		ll adds_arcs = 0;
		for(ll cnt = 1; cnt-1 < N; cnt++){
			if( Nodes[cnt].color == "Blanco") {
				adds_arcs += (ll)(cnt_n - Nodes[cnt].n_ady);
			}
		}

		return adds_arcs;
	}
	*/

	// Funcion que calcula el camino "optimo" entre un par de nodos, se calcula el camino si existe
	// un camino entre ellos. Mediante el uso de BFS se permite llevar un tracker de padres de cada
	// nodo procesado pro el BFS, esto permite determinar el camino mas corto entre un root y un
	// destino.
	// Modificacion particular del problema: Mediante el uso de un grafo auxiliar dado por argumento
	// se procede con el recorrido BFS para hallar dicho camino pero con la condicion de ignorar
	// los nodos del grafo auxilizar.
	// Se requiere la funcion "setUp_arcs".
	bool optimal_path(ll root, ll dest, Graph G_a){
		// Caso base rot = dest.
		if( root == dest ) {
			cout << 1 << endl; print_vi({root});
			return true;
		}
		// Inicializacion de variables, datos y push's.
		bool finded = false;

		queue<NODE> C;
		Nodes[root].visited = 1;
		Nodes[root].level = 1;
		C.push(Nodes[root]);

		// Inicio del recorrido BFS.
		while( !C.empty() ){
			NODE v = C.front();
			C.pop();

			// Lista de elementos adyacentes del Spiders Graph.
			for( auto it : lists[v.n] ){ 
				// Si el nodo en el grafo de primos ya fue visitado, es porque
				// se agregaron todos sus arañas adyacentes y no es necesario 
				// procesarlo de nuevo.
				if( G_a.Nodes[it].visited == 1 ) continue;
				G_a.Nodes[it].visited = 1;
				
				// Lista de elementos adyacentes del Primes Graph.
				for( auto it_a : G_a.get_ady(it) ){
					if( Nodes[it_a].visited != 1 && spider_legs[it_a] > 1) {
						Nodes[it_a].visited = 1;
						Nodes[it_a].level = v.level + 1;
						Nodes[it_a].father = v.n;

						if( it_a == dest ) {
							finded = true; break;
						}

						C.push(Nodes[it_a]);
					}
				}
				if(finded) break;
			}
			if(finded) break;
		}
		// Mostramos por pantalla el camino.
		if(finded){
			ll sz = Nodes[dest].level, curr = dest;
			vll path(sz);
			for(ll cnt = sz-1; cnt > -1; cnt--){
				path[cnt] = curr;
				curr = Nodes[curr].father;
			}
			cout << sz << endl;
			print_vi(path); return true;
		} else {
			return false;
		}
	}

	// Funcion que arma los arcos para las arañas, se usa un grafo auxiliar con nodos
	// iguales a los numeros primos encontramos durante el proceso Sieve of Erastothenes.
	// Estacion es requerida para el funcionamiento de "optimal_path".
	Graph setUp_arcs() {
		// Aplicamos Sieve of Eratosthenes para determinar los numeros primos.
		for(ll div = 2; div+1 < MaxN; div++) {
			// Si un elemento divisor es = 1 es porque no fue marcando anteriormente
			// como multiplo de un primo, por tanto este elemento es primo.
			if(legs_divisors[div] == 1){
				legs_divisors[div] = div;
				for(ll legs = div*div; legs+1 < MaxN;  legs+=div){
					if(legs_divisors[legs] == 1) legs_divisors[legs] = div;
				}
				
			}
		}
		// Se arman los arcos entre las arañas que cumplen con tener un divisor comun mayor a 1.
		Graph G_a(1, MaxN);		// Grafo auxiliar de primos.
		ll div, legs, last_div;
		
		for(ll spider = 1; spider-1 < N; spider++){
			last_div = 1; div = 0;
			
			// Como en Sieve of Eratosthenes se setearon en cada posicion del vector
			// legs_divisors un numero primo que divide al indice del vector y que a su
			// vez este indice representa el numero de patas. Entonces, al dividir el
			// primo por el indice obtenemos otra posicion del vector que contiene otro
			// numero primo, por tanto seteamos los arcos para cada spider con su primo
			// divisor. 
			legs = spider_legs[spider];
			while( legs > 1 ) {
				div = legs_divisors[legs];
				if( div != last_div ) {
					add_arc(spider, div);
					G_a.add_arc(div, spider);
				}
				legs /= div;
				last_div = div;
			}
		}
		return G_a;
	}

	// Funcion que permite mostrar por pantalla cualquier vector de class NODE dado.
	void print_vn(vn a){
		for (ll k = 0; k < a.size(); k++) cout << a[k].n << " ";
		cout << endl;
	}

	// Funcion que permite mostrar por pantalla cualquier vector de enteros dado.
	void print_vi(vll a){
		for (ll k = 0; k < a.size(); k++) cout << a[k] << " ";
		cout << endl;
	}

};

// Escribir "init_code();" justo despues al comienzo del "ll main() {" para lectura de datos.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Fin de la libreria.
/*************************************************************************************************/

int main() {
	// Mejora de speed para cin/cout.
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// Lectura de datos.
	init_code();
	
	cin >> N;
	for(ll cnt = 1; cnt-1 < N; cnt++) cin >> spider_legs[cnt];
	cin >> S >> T;
	// Fin lectura.

	Graph G(1, MaxN);
	Graph G_a = G.setUp_arcs();

	if(!G.optimal_path(S, T, G_a)) cout << "-1" << endl;

	return EXIT_SUCCESS;
}