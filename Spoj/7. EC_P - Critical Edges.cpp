/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: jmlt_undercode
	Problema: SPOJ 7. EC_P - Critical Edges
	
	** Idea General para el problema: **

	Se quiere determinar puentes para un grafo conexo dado. Dado que el problema afirma que
	existe una unica componente conexa = a todo el grafo, entonce realizamos una unica llamada
	del algoritmo Tarjan modificado para determinar puentes.

	Mediante el trackeo de padres y la actualizacion del Low respectivo de cada nodo en el
	recorrido DFS si se observa que  disc[root] < low[ady] entonce existe un puente entre
	root y ady, siendo "ady" un nodo adyacente a "root" y por tanto se agrega a la lista
	de bridges encontrados siendo un par de la forma {root, ady} si root < ady, de lo contrario
	se agrega como {ady, root} dado que asi lo pide el problema. 

	Finalmente, antes de mostrar los datos se verifica dicha lista, si el size es 0 entonces
	"Sin bloqueos" como respuesta, de lo contrario se realiza un sorting sobre la lista sobre
	los "firsts elements" de los pares para obtener el formato deseado del problema. 

	** Actualizacion de Libreria/Class: **
	
	1. Integrado de la funcion "Tarjan", que usa la implementacion del Algoritmo de Tarjan.
	Se modifica levemente el algoritmo original para determinar puentes.
	2. Modificacion a la clase Graph, se agregados algunas variables y estructuras de datos
	para el funcionamiento de la funcion Tarjan.

	
*/

#include <bits/stdc++.h>

using namespace std;
/*************************************************************************************************/
#define pb push_back
#define FOR(i, N) for(int i = 1; i-1 < N; i++)
typedef vector<pair<int, int>> vpii;
typedef vector<vector<int> > vvi;
typedef vector<int> vi;
typedef vector<vector<long long>> vvll;
typedef vector<long long> vll;
typedef long long ll;

// Class/Struct NODE para informacion de un nodo en grafos. Implementada por Junior Lara.
class NODE{
public:
	int n;		// Numero del nodo.
	int visited;	// Identificador de visitado.
	int ex_grade;	// Numero de arcos que salen desde el nodo.
	int in_grade;	// Numero de arcos que entran al nodo.
	/*
	int n_ady;	// Numero de nodos adyacentes a n.
	int min_cost;	// Costo del nodo.
	string color;	// Color del nodo.
	int range;	// Rango para busqueda BFS/DFS.
	int father;	// Nodo padre del nodo n;
	int level;	// Para saber el nivel de un nodo en la busqueda BFS\DFS.
	*/
	// Constructor DEFAULT.
	NODE(){
		n = 0; visited = 0; ex_grade = 0; in_grade = 0;
		//n_ady = 0; min_cost = 0; color = ""; range = 0; father = 0; level = 0;
	}
	// Constructor basico.
	NODE(int _id, int _vis) : n(_id), visited(_vis) {
		ex_grade = 0; in_grade = 0;
		//n_ady = 0; min_cost = 0; color = ""; range = 0; father = 0; level = 0;
	}
	/*// En caso de necesitar Num nodo, isVisitado y color del nodo.
	NODE(int _id, int _vis, string _color) : n(_id), visited(_vis), color(_color) {
		n_ady = 0; min_cost = 0; range = 0; father = 0; level = 0;
	}
	// En caso de necesitar Num nodo, isVisitado y costo del nodo.
	NODE(int _id, int _vis, int _cost) : n(_id), visited(_vis), min_cost(_cost) {
		n_ady = 0; color = ""; range = 0; father = 0; level = 0;
	}*/
};

typedef vector<vector<NODE>> vvn;
typedef vector<NODE> vn;

// Fin de la Class//Struct NODE.
/*************************************************************************************************/

// Inicializacion de variables y estructuras de datos.
const int MaxN= 705;		// Numero maximo de nodos(Ciudades)
const int MaxM= MaxN*(MaxN-1)/2;// Numero maximo de arcos(Carreteras)
int T; 				// Numero de casos de prueba.
int N, M; 			// Numero de nodos y de arcos.
int A, B;			// Extremos de un arco, nodo A conecta con nodo B.

/*************************************************************************************************/
// Libreria Graph implementada por Junior Lara.

class Graph{
	int n_nodes;		// Numero de nodos en el grafo.
	int type_graph;		// Tipo de grafo: 1 = Lista Adyacencia y 2 = Matriz de Adyacencia.
	vvi lists;		// Estructura para la lista de adyacencia.
	vvi Matriz;		// Estructura para la matriz de adyacencia.

public:
	vn Nodes;		// Vector para guardar cada nodo de class NODE.
	vi low;			// Vector para marcar el low en algoritmo Tarjan.
	vi disc;		// Vector para marcar el discovery en algoritmo Tarjan.
	vi opened;		// Vector para marcar si un nodo esta abierto en llamado BFS/DFS.
	vvi container_CC;	// Contenedor de Componentes Conexas.
	int c_time, cnt_CC;	// Inicializador y contador para el algoritmo Tarjan.
	stack<int> Pila;	// Stack usada por el algoritmo Tarjan.
	vpii bridges; 		// Vector de arcos que clasifican como puentes.
	vi father_tracker;	// Vector de nodos para tener un track de los nodos padres de cada nodo.

	// Constructor principal del grafo. Se espeficica el tamaÑo y el tipo de grafo,
	// 1 para el caso de usar listas de adyacencias, 2 para el caso de matrices.
	Graph(int type, int size) : type_graph(type), n_nodes(size) {
		assert(type > 0 && type < 3);
		vi newFatherT(size+1, 0); father_tracker = newFatherT;
		vi newLow(size+1, 0); low = newLow;
		vi newDisc(size+1, 0); disc = newDisc;
		vi newOpened(size+1, 0); opened = newOpened;
		vvi newContainer(size+1); container_CC = newContainer;
		c_time = 0; cnt_CC = 0;

		if (type == 1) { 					// Listas de Adyacencias.
			vvi newLists(size+1); lists = newLists;
			vn newNodes(size+1); Nodes = newNodes;

		} else if (type == 2) { 				// Matriz de Adyacencias.
			vvi newMatriz(size+1, vi (size+1));
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
			lists.pb(vi ());
		} else {
			vvi aux(n_nodes+1, vi (n_nodes+1));
			for (int i = 1; i < n_nodes; i++ ) {
				for (int j = 1; j < n_nodes; j++ ) aux[i][j] = Matriz[i][j];
			}
			Matriz = aux;
		}
	}

	// Funcion que permite agregar un arco entre dos nodos existentes en el grafo. 
	// En caso de grafo tipo 1 entonces realizamos el pushback del elemento a su respectivo
	// vector de adyacencia. En caso de grafo tipo 2 entonces se marca en la posicion dada en 1.
	// Adicionalmente, se procede agregar el nodo con formado NODE.
	void add_arc(int n1, int n2) {
		if ( type_graph == 1 ) {
			lists[n1].pb(n2);
			if(Nodes[n1].n == 0 && n1 != 0) Nodes[n1] = NODE (n1, 0);
			Nodes[n1].ex_grade++;
			if(Nodes[n2].n == 0) Nodes[n2] = NODE (n2, 0);
			Nodes[n2].in_grade++;
		} else {
			Matriz[n1][n2] = 1;
		}
	}

	// Funcion que permite extraer para un nodo dado x como argumento su vector de elementos
	// adyacentes, en caso de listas se expresa por tipo de grafo 1, en caso de matrices entonces
	// por tipo de grafo 2 extraemos los elementos marcado con 1 en la fila respectiva de la matriz.
	vi get_ady(int x) {
		if (type_graph == 1) {
			return lists[x];
		} else {
			vi aux;
			for (int k = 1; k-1 < n_nodes; k++) if (Matriz[x][k] == 1) aux.pb(k);
			return aux;
		}
	}

	// Funcion que permite revertir los arcos del grafo.
	void arc_reverse(){
		vvi rev_list(n_nodes+1);
		for(int k = 1; k-1 < n_nodes; k++){
			for(auto it : lists[k]) rev_list[it].pb(k);
		}
		lists = rev_list;
	}

	// Funcion que retorna el arbol DFS para un elemento root. Este "arbol dfs" consta
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo DFS.
	/*vn DFS_tree(NODE root) {	
		// Inicializacion, push, marcado de variables y nodos.
		//int visited[n_nodes+1];
		stack<NODE> S;

		root.visited = 1;
		S.push(root);

		int cnt = 0;
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
		for(int k = 0; k < cnt; k++) tree[k] = aux[k];

		return tree;
	}*/

	// Funcion que retorna el arbol BFS para un elemento root. Este "arbol bfs" consta
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo BFS.
	/*vn BFS_tree(NODE root) {
		// Inicializacion, push, marcado de variables y nodos.
		//int visited[n_nodes+1];
		queue<NODE> Q;

		root.visited = 1;
		Q.push(root);

		int cnt = 0;
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
		for(int k = 0; k < cnt; k++) tree[k] = aux[k];

		return tree;
	}*/

	// Funcion que permite calcular el camino entre dos nodos dados mediante el uso de
	// metodo/algoritmo DFS, esto por implementacion iterativa y tracker de padres.
	// Se retorna true en caso de encontrar el camino y antes de esto se muestra por
	// pantalla, de lo contrario se retorna false.
	/*bool path_between(int i, int f) {
		if( i == f ) {
			print_vi({i}); 
			return true;
		}

		stack<NODE> S;
		Nodes[i].visited = 1;
		//Nodes[i].level = 1;
		S.push(Nodes[i]);

		bool finded = false;
		while( !S.empty() ){
			NODE v = S.top();
			S.pop();

			for( auto it : get_ady(v.n)){
				if( Nodes[it].visited != 1 ){
					//Nodes[it].level = v.level + 1;
					//Nodes[it].father = v.n;
					if( it == f ){
						finded = true; 
						break;
					}
					Nodes[it].visited = 1;
				}
			}
			if(finded) break;
		}
		return false;

		if(finded){
			int sz = Nodes[f].level, curr = f;
			vi path(sz);
			for(int cnt = sz-1; cnt > -1; cnt--){
				path[cnt] = f;
				curr = Nodes[curr].father;
			}
			print_vi(path); return true;
		} else {
			return false;
		}
	}*/

	// Funcion que realiza un BFS para una seria de raices "LIMITADO A" un cierto rango de amplitud 
	// de busqueda, es decir se tiene un nodo ROOT con rango DIST por tanto todo nodo a distancia
	// <= DIST del ROOT sera procesado en el BFS. Retorna true en caso de recorrer todos los nodos y
	// que en cada nodo fue visitado al menos 1 vez, en caso de haberse topado con un nodo visitado
	// se llega un conteo de nodos visitados mas de una vez (crashes).
	/*bool BFS_lim_to(int root, int dist) {
		queue<NODE> C;
		Nodes[root].visited = 1;
		Nodes[root].range = dist;
		C.push(Nodes[root]);

		int cnt_vis = 1;
		int crashes = 0;

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
	}*/

	// Funcion para determinar si un grafo es bipartito o no. Esto se realiza mediante la
	// coloracion del grafo con 2 colores con recorrido BFS. Si es posible colorear el grafo 
	// tal que dos nodos adyacentes tengan dos colores distllos, en caso afirmativo es bipartito. 
	// Modificacion particular del problema: Se realizan cambios para determinar los arcos
	// posibles que pueden agregarse talque sea un grafo bipartito.
	/*int isBipartito(int n){
		// Inicializacion de variables, datos y push's.
		queue<NODE> C;
		Nodes[n].visited = 1;
		Nodes[n].color = "Blanco";
		C.push(Nodes[n]);
		int cnt_n = 0;

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
		int adds_arcs = 0;
		for(int cnt = 1; cnt-1 < N; cnt++){
			if( Nodes[cnt].color == "Blanco") {
				adds_arcs += (int)(cnt_n - Nodes[cnt].n_ady);
			}
		}

		return adds_arcs;
	}*/

	// Funcion que calcula el camino "optimo" entre un par de nodos, se calcula el camino si existe
	// un camino entre ellos. Mediante el uso de BFS se permite llevar un tracker de padres de cada
	// nodo procesado pro el BFS, esto permite determinar el camino mas corto entre un root y un
	// destino.
	// Modificacion particular del problema: Mediante el uso de un grafo auxiliar dado por argumento
	// se procede con el recorrido BFS para hallar dicho camino pero con la condicion de ignorar
	// los nodos del grafo auxilizar.
	// Se requiere la funcion "setUp_arcs".
	/*bool optimal_path(int root, int dest, Graph G_a){
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
			int sz = Nodes[dest].level, curr = dest;
			vi path(sz);
			for(int cnt = sz-1; cnt > -1; cnt--){
				path[cnt] = curr;
				curr = Nodes[curr].father;
			}
			cout << sz << endl;
			print_vi(path); return true;
		} else {
			return false;
		}
	}*/

	// Funcion que arma los arcos para las arañas, se usa un grafo auxiliar con nodos
	// iguales a los numeros primos encontramos durante el proceso Sieve of Erastothenes.
	// Estacion es requerida para el funcionamiento de "optimal_path".
	/*Graph setUp_arcs() {
		// Aplicamos Sieve of Eratosthenes para determinar los numeros primos.
		for(int div = 2; div+1 < MaxN; div++) {
			// Si un elemento divisor es = 1 es porque no fue marcando anteriormente
			// como multiplo de un primo, por tanto este elemento es primo.
			if(legs_divisors[div] == 1){
				legs_divisors[div] = div;
				for(int legs = div*div; legs+1 < MaxN;  legs+=div){
					if(legs_divisors[legs] == 1) legs_divisors[legs] = div;
				}
				
			}
		}
		// Se arman los arcos entre las arañas que cumplen con tener un divisor comun mayor a 1.
		Graph G_a(1, MaxN);		// Grafo auxiliar de primos.
		int div, legs, last_div;
		
		for(int spider = 1; spider-1 < N; spider++){
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
	}*/

	// Funcion que simula el primer DFS que usa el algoritmo de Kosaraju.
	// Se encarga de obtener la stack de nodos.
	/*void DFS_V1(stack<NODE> &S, NODE root){
		for(auto it : lists[root.n]){
			if(!Nodes[it].visited){
				Nodes[it].visited = 1;
				DFS_V1(S, Nodes[it]);
			}
		}
		S.push(root);
	}*/

	// Funcion que simula el segundo DFS que usa el algoritmo de Kosaraju.
	// Se encarga de detectar las C.F.C.
	/*void DFS_V2(vi &vis, NODE root){
		for(auto it : lists[root.n]){
			if(!vis[it]){
				vis[it] = 1;
				DFS_V2(vis, Nodes[it]);
			}
		}
	}*/

	// Funcion que permite calcular componentes fuertemente conexas para un grafo dirigido.
	// Tiene como implementacion base el algoritmo de Kosaraju.
	/*void kosaraju(){
		// Primer DFS para llenar la stack con el recorrido del arbol DFS respectivo.
		stack<NODE> S;
		for(int k = 1; k-1 < n_nodes; k++){
			if(!Nodes[k].visited){
				Nodes[k].visited = 1; DFS_V1(S, Nodes[k]);
			}
		}

		// Segundo DFS para detectar las componentes fuertemente conexas.
		vi visited_k(n_nodes+1, 0);
		arc_reverse();
		while(!S.empty()) {
			NODE v = S.top();
			S.pop();
			if(!visited_k[v.n]) {
				SCC_cnt++;
				visited_k[v.n] = 1;
				DFS_V2(visited_k, v);
			}
		}
		arc_reverse();
	}*/

	// Funcion que aplica Algoritmo de Kahn para orden topologicos. Su uso se basa el tener un
	// grafo con 1 unico nodo raiz cuyo grado interior sea 0, esto es seteando un "nodo fantasma"
	// que conecte con todos los demas nodo que originalmente tengan grado interior en 0.
	// Esta mejora permite realizar una unica llamada al DFS/BFS.
	/*vi kahn(){
		vi order_top;
		int del_arcs = 0;

		// Se usa un Min Heap como cola de prioridad, dado que el problema solicita 
		// hacer la tarea/trabajo con menor numero lo antes posible.
		priority_queue<int, vector<int>, greater<int>> Q;
		Q.push(0);

		while ( !Q.empty() ) {
			int v = Q.top();
			Q.pop();

			order_top.pb(v);
			Nodes[v].visited = 1;

			for ( auto it : lists[v]) {
				if ( !Nodes[it].visited ) {
					Nodes[it].in_grade--;
					del_arcs++;
					if(!Nodes[it].in_grade) Q.push(it);
				}
			}
		}

		// Si al final del BFS tenemos que la cantidad de arcos eliminados es distinto
		// al numero de arcos total M(incluyendo los arcos fantasmas) entonce hay circuitos
		// en el grafo.
		if (del_arcs != M) {
			vi empty_v; return empty_v;
		}

		return order_top;
	}*/

	// Funcion que aplica el algoritmo Tarjan para el calculo de C.F.C de un grafo. Es tambien
	// utilizado para determinar puentes y puntos de articulacion mediante una leve mejora al
	// mismo. 
	void Tarjan (int root) {
		opened[root] = 1;		// Marcamos como "abierto" 

		low[root] = c_time++;		// Actualizamos y marcado del Discovery y Low de cada nodo.
		disc[root] = low[root];

		Nodes[root].visited = 1;	// Marcado de nodos en el arreglo de visitado en cada llamada al Tarjan.

		Pila.push(root);		// Agregar a la pila el nodo raiz.

		// Nos aseguramos de que hayan nodos adyacentes (de salida/Delta+) a procesar.
		if (!lists[root].empty()) {
			for(auto it : lists[root]) {
				if(it == father_tracker[root]) continue;// No se visita al padre.

				if( !Nodes[it].visited ) { 		// Visitamos al hijo de root.
					father_tracker[it] = root;	// Trackeamos el padre de cada nodo.

					Tarjan(it);

					if( disc[root] < low[it]){	// Verificando si es un puente.
						if(root < it){
							bridges.pb(make_pair(root, it));
						} else {
							bridges.pb(make_pair(it, root));
						}
					}

					low[root] = min(low[it], low[root]);	// Actualizacion del Low.

				} else if ( opened[it] ) {
					low[root] = min(low[root], disc[it]);	// Actualizacion del Low.
				}
			}
		}

		// Cuando tengamos mismo Low a Discovery entonces hemos encontrado una C.F.C.
		if( disc[root] == low[root] ) {	
			int nodo;
			cnt_CC++;
			if (!Pila.empty()) {
				while( root != Pila.top() ) {
					nodo = Pila.top();
					Pila.pop();
					opened[nodo] = 0;		// Cerramos la llamada recursiva al nodo pop.
					container_CC[cnt_CC].pb(nodo);	// Agregamos el nodo a la Componente.
				} 
			}

			// Popeamos la root de la stack. Pues esta forma parte de la componente y por tanto
			// esta debe agregarse.
			Pila.pop();		
			container_CC[cnt_CC].pb(root);
			
			// Cerramos la llamada recursiva al nodo root.
			opened[root] = 0;	
		}
	}

	// Funcion que permite mostrar por pantalla cualquier vector de class NODE dado.
	void print_vn(vn a){
		for (int k = 0; k < a.size(); k++) cout << a[k].n << " ";
		cout << endl;
	}

	// Funcion que permite mostrar por pantalla cualquier vector de enteros dado.
	void print_vi(vi a){
		for (int k = 0; k < a.size(); k++) cout << a[k] << " ";
		cout << endl;
	}
};

// Escribir "init_code();" justo despues al comienzo del "int main() {" para lectura de datos.
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

	cin >> T;
	int aux, sz;
	FOR(t, T){
		cin >> N >> M;
		Graph G(1, N);
		aux = M;
		while(aux--){
			cin >> A >> B;
			G.add_arc(A, B);
			G.add_arc(B, A);
		}

		// Aplicacion de Tarjan para el calculo de puentes.
		G.father_tracker[1] = 1;
		G.Tarjan(1);
		sz = G.bridges.size();

		// Impresion de resultados.
		cout << "Caso #" << t << endl;
		if( !sz ){
			cout << "Sin bloqueos" << endl;
			continue;
		}
		cout << sz << endl;
		sort(G.bridges.begin(), G.bridges.end());
		for(const auto &it : G.bridges){
			cout << it.first << " " << it.second << endl;
		}
		
	}

	return EXIT_SUCCESS;
}