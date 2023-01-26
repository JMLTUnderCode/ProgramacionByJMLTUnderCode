/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Mail.Ru Cup 2018 - Practice Round - A. Bmail Computer Network

	Idea General:

	Con el uso de la estructura/class de grafo creada, realizar una busqueda DFS por el
	arbol dado.
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int> > vii;
typedef vector<int> vi;

class Graph{
	int n_nodes;		// Numero de nodos en el grafo.
	int type_graph; 	// Tipo de grafo: 1 = Lista Adyacencia y 2 = Matriz de Adyacencia.
	vii lists;		// Estructura para la lista de adyacencia.
	vii Matriz;		// Estructura para la matriz de adyacencia.

public:
	// Constructor principal del grafo. Se espeficica el tamaÑo y el tipo de grafo,
	// 1 para el caso de usar listas de adyacencias, 2 para el caso de matrices.
	Graph(int type, int size) : type_graph(type), n_nodes(size) {
		assert(type > 0 && type < 3);
		if (type == 1) { // Listas de Adyacencias
			vii newLists(size+1);
			lists = newLists;

		} else if (type == 2) { // Matriz de Adyacencias
			vii newMatriz(size+1, vi (size+1, 0));
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
			lists.push_back(vi ());
		} else {
			vii aux(n_nodes+1, vi (n_nodes+1, 0));
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
		} else {
			Matriz[n1][n2] = 1;
		}
	}

	// Funcion que permite extraer para un nodo dado n como argumento su vector de elementos
	// adyacentes, en caso de listas se expresa por tipo de grafo 1, en caso de matrices entonces
	// por tip ode grafo 2 extraemos los elementos marcado con 1 en la fila respectiva de la matriz.
	vi get_ady(int n) {
		if (type_graph == 1) {
			return lists[n];
		} else {
			vi aux;
			for ( int k = 1; k-1 < n_nodes; k++) if (Matriz[n][k] == 1) aux.push_back(k);
			return aux;
		}
	}

	// Funcion que retorna el arbol DFS para una raiz de argumento. Este "arbol dfs" constra
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo DFS.
	vi DFS_tree(int root) {	
		// Inicializacion, push, marcado de variables y nodos.
		int visited[n_nodes+1];
		stack<int> S;

		visited[root] = 1;
		S.push(root);

		int cnt = 0;
		vi aux(n_nodes+1);

		// Calculo del arbol DFS mediante la estructura Pila(Stack).
		while ( !S.empty() ) {
			int node = S.top();
			S.pop();
			aux[cnt++] = node;

			if(type_graph == 1) {
				for ( auto it : lists[node]) {
					if ( visited[it]!= 1 ) {
						visited[it] = 1; S.push(it);
					}
				}
			} else {
				//Por implementar
			}
		}

		// Se procede a extrar el arbol DFS respectivo del vector aux, esto pautado
		// por la variable cnt.
		vi tree(cnt);
		for(int k = 0; k < cnt; k++) tree[k] = aux[k];

		return tree;
	}

	// Funcion que retorna el arbol BFS para una raiz de argumento. Este "arbol bfs" constra
	// de un vector de enteros cuyo orden expresa el orden en que fueron procesador en el 
	// algoritmo BFS.
	vi BFS_tree(int root) {
		// Inicializacion, push, marcado de variables y nodos.
		int visited[n_nodes+1];
		queue<int> Q;

		visited[root] = 1;
		Q.push(root);

		int cnt = 0;
		vi aux(n_nodes+1);

		// Calculo del arbol BFS mediante la estructura Cola(Queue).
		while ( !Q.empty() ) {
			int node = Q.front();
			Q.pop();
			aux[cnt++] = node;

			if(type_graph == 1) {
				for ( auto it : lists[node]) {
					if ( visited[it]!= 1 ) {
						visited[it] = 1; Q.push(it);
					}
				}
			} else {
				//Por implementar
			}
		}

		// Se procede a extrar el arbol BFS respectivo del vector aux, esto pautado
		// por la variable cnt.
		vi tree(cnt);
		for(int k = 0; k < cnt; k++) tree[k] = aux[k];

		return tree;
	}

	bool pb_recur(int n1, int n2, vi &visited, vi &path, int &cnt) {
		// Se marca como visitado el nodo n1 y agregamos el nodo al camino calculado.
		visited[n1] = 1;
		path[cnt++] = n1;
	 	
	 	// Si hemos encontrado a n2(la meta) retornamos en el proceso recursivo.
		if (n1 == n2) return true;
	 	
	 	// Llamada recursiva para la lista de elementos adyacentes al nodo actual.
		for ( auto it : lists[n1]) {
			if (visited[it] != 1) {
				// Si pb_recur retorna true es porque fue encontrado el valor n2
				// por tanto nos devolvemos de la misma forma en todas las llamadas.
				if (pb_recur(it, n2, visited, path, cnt)) return true;
			}
		}
	 	
	 	// Retroceder el contador el como estar eliminando elementos del vector.
		cnt--;

		return false;
	}

	// Funcion que permite calcular el camino entre dos nodos dados.
	// Como proceso interno realiza la llamada a una funcion recursiva,
	// esta se encarga de hacer DFS hasta encontrar el nodo meta(n2)
	vi path_between(int n1, int n2) {
		vi visited(n_nodes+1);
		vi aux(n_nodes+1);
		int cnt = 0;
		
		// En caso de pb_recur retorne true entonces n2 fue encontrado.
		// Se procede a extrar del vector aux la longitud del camino pautado por
		// la variable cnt.
		if ( pb_recur(n1, n2, visited, aux, cnt) ) {
			vi path(cnt);
			for(int k = 0; k < cnt; k++) path[k] = aux[k];
			return path;
		} else {
			printf("%s", "No existe camino entre los vertices.");
			return aux;
		}
	}

	// Funcion que permite mostrar por pantalla cualquier vector dado.
	void print_vi(vi a){
		for ( int k = 0; k < a.size(); k++) printf("%d ", a[k]);
		printf("%s","\n");
	}

};

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Inicializacion y estructuras de datos para el problema en cuestion.
const int Nmax = 2e5 + 5;
int N, node;

int main() {
	init_code();

	// Lectura e inicializacion de variables.
	scanf("%d", &N);
	
	Graph G(1, N);

	for (int k = 2; k-1 < N; k++ ) {
		scanf("%d", &node);
		G.add_arc(node, k);
	}
	// Fin de lectura.

	// Impresion de toda la lista de adyacencia.
	//for ( int k = 1; k-1 < N; k++) G.print_vi(G.get_ady(k));

	// Impresion del arbol DFS.
	//G.print_vi(G.DFS_tree(1));

	// Impresion del arbol BFS.
	//G.print_vi(G.BFS_tree(1));
	
	// Moscar el camino entre dos nodos.
	G.print_vi(G.path_between(1, N));

	return 0;
}