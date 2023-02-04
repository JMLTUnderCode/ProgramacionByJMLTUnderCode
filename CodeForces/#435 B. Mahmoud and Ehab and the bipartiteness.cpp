/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #435 (Div. 2) B. Mahmoud and Ehab and the bipartiteness

	** Idea General para el problema: **
	Se usa la nocion de biparticion para contar cuantos nodos son de 1 color y cuantos del
	otro color, con esto simulamos el conteo de elementos en cada conjunto disjunto. 
	Luego, procedemos un chequeo por todos los nodos verificando aquellos que sean de un
	conjunto determinado, digamos CONJUNTO1, y proceder a restar la cardinalidad del 
	CONJUNTO2 con la cantidad de elementos adyacentes del nodo que viene del CONJUNTO 1,
	la respuesta es la suma de estas restas. 

	Ejemplo.  1 --- 2 --- 3  (Grafo 1 conecta con 2, 2 con 3)
	Se tiene, conjunto 1 = {1,3} y conjunto 2 = {2}. 
	Realizamos la busqueda por todos los nodos tal que si son del conjunto 1 se realiza:
	Para nodo 1: |Conjunto 2| - n_ady(1) = 1 - 1 = 0 
	Para nodo 2: 2 no pertenece al conjunto 1. 
	Para nodo 3: |Conjunto 2| - n_ady(2) = 1 - 1 = 0
	
	Por tanto, hemos contado el total de arcos posibles entre ambos conjuntos tal que 
	no quebrante la regla de biparticion, para el caso actual 0.
	
	** Actualizacion de Libreria/Class: **
	1. Se agrega nueva variables dato para clase NODE, "n_ady" numero entero que permite
	contar el numero de nodos adyacentes a n. Y leves arreglos a los constructores.

	2. La funcion "isBipartito" es modifica en esta oportunidad con el fin de solventar el
	problema/ejercicio. En versiones anteriores se retornaba bool, ahora un int.

*/

#include <bits/stdc++.h>

using namespace std;
/*************************************************************************************************/
// Class/Struct NODE para informacion de un nodo en grafos. Implementada por Junior Lara.
class NODE{
public:
	int n;		// Numero del nodo.
	int n_ady;	// Numero de nodos adyacentes a n.
	int visited;	// Identificador de visitado.
	int min_cost;	// Costo del nodo.
	string color;	// Color del nodo.
	int range;	// Rango para busqueda BFS/DFS.
	int soldier;	// Variable del problema particular.

	// Constructor DEFAULT.
	NODE() : n(0), n_ady(0), visited(0), min_cost(0), color(""), range(0) {
	}
	// Constructor basico.
	NODE(int _id, int _vis) : n(_id), visited(_vis) {
		n_ady = 0; min_cost = 0; color = ""; range = 0;
	}
	// En caso de necesitar Num nodo, isVisitado y color del nodo.
	NODE(int _id, int _vis, string _color) : n(_id), visited(_vis), color(_color) {
		n_ady = 0; min_cost = 0; range = 0;
	}
	// En caso de necesitar Num nodo, isVisitado y costo del nodo.
	NODE(int _id, int _vis, int _cost) : n(_id), visited(_vis), min_cost(_cost) {
		n_ady = 0; color = ""; range = 0;
	}
	

};

typedef vector<vector<NODE>> vvn;
typedef vector<NODE> vn;
typedef vector<vector<int> > vvi;
typedef vector<int> vi;

// Fin de la Class//Struct NODE.
/*************************************************************************************************/

// Inicializacion de variables y estructuras de datos.
const int MaxN= 1e5+5;	// Numero maximo de nodos en un grafo.
int N;			// Numero de nodos en el grafo.
int A, B;		// Nodos auxiliares qui similan el arco (n1 - n2).

/*************************************************************************************************/
// Libreria Graph implementada por Junior Lara.

class Graph{
	int n_nodes;		// Numero de nodos en el grafo.
	int type_graph; 	// Tipo de grafo: 1 = Lista Adyacencia y 2 = Matriz de Adyacencia.
	vvi lists;		// Estructura para la lista de adyacencia.
	vvi Matriz;		// Estructura para la matriz de adyacencia.

public:
	vn Nodes;		// Vector para guardar cada nodo de class NODE.
	int NoNvis = 0;		// Valor default de No Visitado.

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
	void add_arc(int n1, int n2) {
		if ( type_graph == 1 ) {
			lists[n1].push_back(n2);
			if(Nodes[n1].n == 0) Nodes[n1] = NODE (n1, 0);
			if(Nodes[n2].n == 0) Nodes[n2] = NODE (n2, 0);
		} else {
			Matriz[n1][n2] = 1;
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

	// Funcion que realiza un BFS para una seria de raices "LIMITADO A" un cierto rango de amplitud 
	// de busqueda, es decir se tiene un nodo ROOT con rango x por tanto todo nodo a distancia
	// <= x del ROOT sera procesado en el BFS. Retorna true en caso de recorrer todos los nodos y
	// que en cada nodo fue visitado al menos 1 vez.
	bool BFS_lim_to() {
		queue<NODE> C;
		int cnt_vis = 0;
		C.push(Nodes[1]);

		while(!C.empty()){
			NODE v = C.front();
			C.pop();

			if( v.visited != NoNvis && v.visited != v.soldier ) return false;

			if( v.range > 0 ){
				for(auto it : lists[v.n]){
					// Si no hay soldados entonces actualizamos.
					if ( Nodes[it].visited == NoNvis ) {
						cnt_vis++;
						Nodes[it].visited = v.soldier;
						Nodes[it].range = v.range - 1;
						Nodes[it].soldier = v.soldier;
						C.push(Nodes[it]);
					} else {
						// Si encontramos un soldado distinto, retorn false.
						if( Nodes[it].visited != v.soldier ) return false;
					}
				}
			}
		}
		
		// Sino se visitaron todos los nodos, entonces no cumple la condicion.
		if(cnt_vis < n_nodes) return false;

		return true;
	}

	// Funcion para determinar si un grafo es bipartito o no. Esto se realiza mediante la
	// coloracion del grafo con 2 colores. Si es posible colorear el grafo tal que dos nodos
	// adyacentes tengan dos colores distintos, en caso afirmativo es bipartito.
	// Modificacion particular del problema: Se realizan cambiar para determinar los arcos
	// posibles que pueden agregarse talque sea un grafo bipartito.
	long long isBipartito(int n){
		queue<NODE> C;

		Nodes[n].visited = 1;
		Nodes[n].color = "Blanco";
		int cnt_n = 0;
		C.push(Nodes[n]);

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

		long long adds_arcs = 0;
		for(int cnt = 1; cnt-1 < N; cnt++){
			if( Nodes[cnt].color == "Blanco") {
				adds_arcs += (long long)(cnt_n - Nodes[cnt].n_ady);
			}
		}

		return adds_arcs;
	}


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

	scanf("%d", &N);
	Graph G(1, N);

	bool takeRoot = false;
	int root;
	for(int cnt = 1; cnt < N; cnt++){
		scanf("%d %d", &A, &B);
		G.add_arc(A, B); G.add_arc(B, A);
		G.Nodes[A].n_ady++, G.Nodes[B].n_ady++; 
		if(!takeRoot) root = A; takeRoot = true;
	}

	printf("%lld\n", G.isBipartito(root));

	return EXIT_SUCCESS;
}