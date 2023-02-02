/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: jmlt_undercode
	Problema: SPOJ 2. AKBAR - Akbar, The great

	** Idea General para el problema: **
	Se plantea una busqueda BFS para cada punto inicial de la ciudades donde recide un guardia
	inicialmente. La busqueda BFS se limita al rango/fuerza X que posee el guardia en la ciudad 
	base, por tanto el BFS tendra como condicion que todas las ciudades a distancia <= X serán
	marcadas como visitada por el guardia. En caso de que el BFS encuentre una ciudad ya visitada
	y este tenga un guardia diferente al actual entonces fallo la distrubucion de guardias, de lo 
	contrario se debe verificar que cada ciudad esta custodiada, para esto se lleva un contador
	de elementos visitados, si al final de proceso este contador es menor al numero total de ciudades
	se retorna "No" indicando mala distrubucion de guardia. Si todo lo anterior es correcto,
	mostramos un "Yes".

	** Actualizacion de Libreria: **
	1. Se agrego una nueva funcion BFS_limit_to (BFS limitado a..) un rango de busqueda para una
	lista de nodos root. Como bien dice el comentario superior de la funcion se realiza un BFS
	para tal que todo nodo a x distancia del nodo root será procesado.

	2. Para la entrega de SEMANA 1 no se tenia la estructura de dato NODE para los nodos del
	grafo(Graph), por tanto se actualizó a todas las funciones entregadas en problemas de semana 1
	se modificaron a este nueva estructura NODE, incluso la nueva funcion mencionada en (1).
	
*/

#include <bits/stdc++.h>

using namespace std;
/*************************************************************************************************/
// Class/Struct NODE para informacion de un nodo en grafos. Implementada por Junior Lara.
class NODE{
public:
	int n;		// Numero del nodo.
	int visited;	// Identificador de visitado.
	int min_cost;	// Costo del nodo.
	string color;	// Color del nodo.
	int range;	// Rango para busqueda BFS/DFS.
	int soldier;	// Variable del problema particular.

	// Constructor DEFAULT.
	NODE() : n(0), visited(0), min_cost(0), color(""), range(0) {
	}
	// Constructor basico.
	NODE(int _i, int _v) : n(_i), visited(_v) {
	}
	// En caso de necesitar Num nodo, isVisitado y color del nodo.
	NODE(int _id, int _vis, string _color) : n(_id), visited(_vis), color(_color) {
	}
	// En caso de necesitar Num nodo, isVisitado y costo del nodo.
	NODE(int _id, int _vis, int _cost) : n(_id), visited(_vis), min_cost(_cost) {
		n = _id; visited = _vis; min_cost = _cost;
	}
	// Constructor especifico del problema.
	NODE(int _i, int _v, int _s, int _f) : n(_v), visited(_v), soldier(_s), range(_f) {
	}

};

typedef vector<vector<NODE>> vvn;
typedef vector<NODE> vn;
typedef vector<vector<int> > vvi;
typedef vector<int> vi;

// Fin de la Class//Struct NODE.
/*************************************************************************************************/

// Inicializacion de variables y estructuras de datos.
const int MaxN = 1e6 + 5; 
int T;				// Numero de casos.
int N, R, M;			// Num. de nodos, Num. de "roads" arcos, Num. de guardias.
int K, S;			// Posicion del guardia, Fuerza del guardia.
int A, B;			// Nodos que conforman el arco AB.
int str_soldier[MaxN]; 		// Arrays de fuerza para cada soldado.
vn pos_soldier(MaxN);		// Arrays para almacenar la posicion(nodo) donde esta el guardia.

/*************************************************************************************************/
// Libreria Graph implementada por Junior Lara.

class Graph{
	int n_nodes;		// Numero de nodos en el grafo.
	int type_graph; 	// Tipo de grafo: 1 = Lista Adyacencia y 2 = Matriz de Adyacencia.
	vvi lists;		// Estructura para la lista de adyacencia.
	vvi Matriz;		// Estructura para la matriz de adyacencia.

public:
	vn Nodes;		// Vector para guardar cada nodo de class NODE.
	// Constructor principal del grafo. Se espeficica el tamaÑo y el tipo de grafo,
	// 1 para el caso de usar listas de adyacencias, 2 para el caso de matrices.
	Graph(int type, int size) : type_graph(type), n_nodes(size) {
		assert(type > 0 && type < 3);
		if (type == 1) { // Listas de Adyacencias
			vvi newLists(size+1); vn newNodes(size+1);
			lists = newLists; Nodes = newNodes;

		} else if (type == 2) { // Matriz de Adyacencias
			vvi newMatriz(size+1, vi (size+1));
			Matriz = newMatriz;

		} else {
			printf("%s", "Error: Tipo de grafo especificado (Argument).");
		}
	}

	// Funcion que realiza un BFS para una seria de raices "LIMITADO A" un cierto rango de amplitud 
	// de busqueda, es decir se tiene un nodo ROOT con rango x por tanto todo nodo a distancia
	// <= x del ROOT sera procesado en el BFS.
	bool BFS_lim_to() {
		queue<NODE> C;
		int cnt_vis = 0;
		for(int s = 1; s-1 < M; s++) {
			if( Nodes[pos_soldier[s].n].visited != -1) return false;
			Nodes[pos_soldier[s].n].visited = s;
			Nodes[pos_soldier[s].n].range = str_soldier[s];
			Nodes[pos_soldier[s].n].soldier = s;
			cnt_vis++;
			C.push(Nodes[pos_soldier[s].n]);
		}

		while(!C.empty()){
			NODE v = C.front();
			C.pop();

			if( v.visited != -1 && v.visited != v.soldier ) return false;

			if( v.range > 0 ){
				for(auto it : lists[v.n]){
					if ( Nodes[it].visited == -1 ) {
						cnt_vis++;
						Nodes[it].visited = v.soldier;
						Nodes[it].range = v.range - 1;
						Nodes[it].soldier = v.soldier;
						C.push(Nodes[it]);
					} else {
						if( Nodes[it].visited != v.soldier ) return false;
					}
				}
			}
		}
		
		if(cnt_vis < n_nodes) return false;

		return true;
	}

	// Funcion que permite agregar un nodo al grafo, en caso de grafo tipo 1 entonces un pushback
	// de una vector vacio simulando una nueva posicion disponible en la estructura del grafo.
	// Para el caso grafo tipo 2 entonces es recrear una nueva matriz con 1 unidad fila/columna mas
	// y con el contenido de la antigua matriz.
	void add_node() {
		n_nodes++;
		if (type_graph == 1) {
			lists.push_back(vector<int> ());
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
	void add_arc(NODE n1, NODE n2) {
		if ( type_graph == 1 ) {
			lists[n1.n].push_back(n2.n);
		} else {
			Matriz[n1.n][n2.n] = 1;
		}
	}

	// Funcion que permite extraer para un nodo dado n como argumento su vector de elementos
	// adyacentes, en caso de listas se expresa por tipo de grafo 1, en caso de matrices entonces
	// por tipo de grafo 2 extraemos los elementos marcado con 1 en la fila respectiva de la matriz.
	vi get_ady(NODE x) {
		if (type_graph == 1) {
			return lists[x.n];
		} else {
			// Por implementar
			/*vi aux;
			for ( int k = 1; k-1 < n_nodes; k++) if (Matriz[x.n][k] == 1) aux.push_back(k);
			return aux;*/
		}
	}

	// Funcion que retorna el arbol DFS para una raiz de argumento. Este "arbol dfs" consta
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo DFS.
	vn DFS_tree(NODE root) {	
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
	}

	// Funcion que retorna el arbol BFS para una raiz de argumento. Este "arbol bfs" consta
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo BFS.
	vn BFS_tree(NODE root) {
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
	}

	bool pb_recur(NODE n1, NODE n2, vn &path, int &cnt) {
		// Se marca como visitado el nodo n1 y agregamos el nodo al camino calculado.
		n1.visited = 1;
		path[cnt++] = n1;
	 	
	 	// Si hemos encontrado a n2(la meta) retornamos en el proceso recursivo.
		if (n1.n == n2.n) return true;
	 	
	 	// Llamada recursiva para la lista de elementos adyacentes al nodo actual.
		for ( auto it : lists[n1.n]) {
			if (Nodes[it].visited != 1) {
				// Si pb_recur retorna true es porque fue encontrado el valor n2
				// por tanto nos devolvemos de la misma forma en todas las llamadas.
				if (pb_recur(Nodes[it], n2, path, cnt)) return true;
			}
		}
	 	
	 	// Retroceder el contador el como estar eliminando elementos del vector.
		cnt--;

		return false;
	}

	// Funcion que permite calcular el camino entre dos nodos dados.
	// Como proceso interno realiza la llamada a una funcion recursiva,
	// esta se encarga de hacer DFS hasta encontrar el nodo meta(n2)
	vn path_between(int initial, int final) {
		//vi visited(n_nodes+1);
		vn aux(n_nodes+1);
		int cnt = 0;
		
		// En caso de pb_recur retorne true entonces n2 fue encontrado.
		// Se procede a extrar del vector aux la longitud del camino pautado por
		// la variable cnt.
		NODE i(initial, -1), f(final, -1);
		if ( pb_recur(i, f, aux, cnt) ) {
			vn path(cnt);
			for(int k = 0; k < cnt; k++) path[k] = aux[k];
			return path;
		} else {
			printf("%s", "No existe camino entre los vertices.");
			return aux;
		}
	}

	// Funcion
	//bool isBipartito(  ){}


	// Funcion que permite mostrar por pantalla cualquier vector de class NODE dado.
	void print_vn(vn a){
		for ( int k = 0; k < a.size(); k++) printf("%d ", a[k].n);
		printf("%s","\n");
	}

	// Funcion que permite mostrar por pantalla cualquier vector de enteros dado.
	void print_vi(vi a){
		for ( int k = 0; k < a.size(); k++) printf("%d ", a[k]);
		printf("%s","\n");
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
	init_code();

	scanf("%d", &T);
	while(T--){
		scanf("%d %d %d", &N, &R, &M);
		Graph G(1, N);
		
		for(int cnt = 1; cnt-1 < R; cnt++){
			scanf("%d %d", &A, &B);
			// Generamos los nodos class NODE, insertamos en la lista y 
			// agregamos al grafo.
			NODE a(A, -1), b(B, -1);
			if(G.Nodes[A].n == 0) G.Nodes[A] = a;
			if(G.Nodes[B].n == 0) G.Nodes[B] = b;
			G.add_arc(a, b); G.add_arc(b, a);
		}
		
		for(int cnt = 1; cnt-1 < M; cnt++){
			scanf("%d %d", &pos_soldier[cnt].n, &str_soldier[cnt]);
			pos_soldier[cnt].visited = -1;
		}
		
		printf("%s\n", G.BFS_lim_to() ? "Yes" : "No" );

	}

	return EXIT_SUCCESS; 	// Lo recien aprendo de Sistemas Operativos 1. SUCCESS y FAILURE
				// Modos de terminacion de un programa en C.
}