/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Nota: Hace poco me cambie de IDE, usaba Dev C++, ahora es Sumplime Text con configuracion 
	de competitivo en CodeForces.

	Idea General: 
	
	Dado el arreglo TREE que debe verificar si es un BFS correcto o no, debemos analizar que cumple
	con la caracteritica de un tree_bfs, es decir que se cumpla el orden de visitados y almacenado
	en la cola. Entonces, consideramos dos apuntadores/señaladores "l_aux" y "aux" importante dentro 
	del array TREE dado por pantalla a verificar. Supongamos el siguiente input de CF:
	4
	1 2
	1 3
	2 4
	1 2 3 4
	
	La lista de adyacencia respectiva seria: 
	Nodo
	 1 -> 2, 3
	 2 -> 4
	 3 -> 
	 4 -> 

	 El TREE dado a verificar es 1 2 3 4, no posicionamos en el primer elemento del tree, veamos 
	 a su lista de adyacencia y su length es 2, por tanto debemos verificar en el subbloque
	 l_aux = 1 y aux = 2, es decir en el intervalo [l_aux, aux] = [1 , 2] del TREE dado con los 
	 elementos en la lista de adyacencia. Notemos que efectivamente en la posicion 1 y 2 del arreglo 
	 TREE estan los dos elementos de la lista de adyacencia del nodo 1.

	 Proseguimos con el segundo elemento del TREE, en este caso nodo 2, vemos su lista de adyacencia
	 y su length es 1, por tanto verificamos en el bloque l_aux = aux + 1 = 2 + 1 = 3. y aux = length + 1
	 = 3, por tanto es el bloque [3 , 3], es decir verificar que la posicion 3 del TREE es igual a los
	 elementos de la lista de adyacencia del 2, lo cual es cierto. 

	 En este punto, tenemos aux = 4 y como aux < n-1 == False salimos del algoritmo principal de verificacion
	 lo que nos permite decir que el BFS_TREE dado es correcto. En caso de que no esté un elemento
	 respectivo de la lista en el array TREE, se retorna No. 		
*/

#include <bits/stdc++.h>

using namespace std;

void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

void is_BFS(vector<list<int>> G, vector<int> tree){

	int n = tree.size();		// Cantidad de nodos.
	vector<int> visitados(n);	// Vector de visitados para los nodos.
	int aux = 0;				// Aux permite posicionarte en el arreglo TREE he ir verificando los elementos de los adyacentes.
	int pos = 0;				// Iterador sobre cada nodo del arreglo TREE.
	int eliminados;				// Contador de nodos que hayan sido visitados y esten en la lista de ady.
	
	// Vamos verificando por bloques (aux) del arreglo TREE en la lista de adyacencia de 
	// cada nodo.
	while ( aux < n-1) {
		
		list<int> ady = G[tree[pos]-1];	// Extraemos la lista de adyacencia
		int lenAdy = ady.size();		// Cantidad de nodos en la lista de adyacencia
		visitados[tree[pos]-1] = 1;		// Marcar como visitado en nodo actual.
		eliminados = 0;
		
		// El primer elemento del TREE es el vectex 1, este nunca tendra en los adyacentes 
		// nodos visitados
		if (pos != 0) {
			list<int>::iterator it = ady.begin();
			while ( it != ady.end() && (lenAdy != eliminados) ) {
				if ( visitados[*it - 1] == 1 ) {
					eliminados++;
				} 
				it++;
			}
		}

		// En caso de un nodo x tenga como length la lista de adyadencia igual n-1 quiere decir que todo
		// los nodos estan conectado al nodo x.
		if ( lenAdy >= (n-1) ) {
			cout << "Yes";
			return;
		}
		
		// Si la cantidad de adyacentes al nodo actual es igual a los eliminados quiere decir que
		// la lista tiene solo elementos que ya fueron visitados, por tanto no aportan nada al
		// analisis.
		if (lenAdy != eliminados) {
			
			// Actualizamos variables y posicionamos un l_aux para verificar los adyacentes en el TREE.
			int l_aux = aux + 1;
			aux += (lenAdy-eliminados);
			
			// Marcamos como visitados y marcamos como eliminado a todo nodos en la lista de adyacencia
			// que se encuentra en el tree respectivo. Esto enfatizado en el subbloque del array tree 
			// dictado por l_aux hasta aux, [l_aux, aux].
			for ( int k = l_aux; k <= aux; k++ ) {
				
				list<int>::iterator it = ady.begin();
				while ( it != ady.end() ) {
					if ( *it == tree[k] ) {
						visitados[tree[k]-1] = 1;
						eliminados++;
						break;
					} 
					it++;
				}
			}
			
			// Si se da el caso de tener una lista de adyacencias con elementos sobrantes quiere decir
			// que estos elementos no estaban en el bloque correspondiente [l_aux, aux] por tanto nos 
			// afirma que no estan los elementos respectivo en el TREE.
			if (eliminados != lenAdy) {
				cout << "No";
				return;
			}
		}

		// Aumentamos posicion en el arreglo TREE
		pos++;
		
	}

	// 
	cout << "Yes";
	return;	
}

int main(){
	
	init_code();

	/* Inicializacion de Variables */
	int n;	// Precondicion: 3 <= n <= 2*10^5
	vector<int> arc(2);
	
	cin >> n;
	vector<int> tree_bfs(n);
	vector<list<int>> grafo(n);
	
	/*Solicitamos datos por pantalla*/
	for( int k = 0; k < n-1; k++ ) {
		cin >> arc[0] >> arc[1];
		grafo[arc[0]-1].push_back(arc[1]);
		grafo[arc[1]-1].push_back(arc[0]);
	}
	
	for( int k = 0; k < n; k++ ) {
		cin >> tree_bfs[k];
	}
	
	/*En caso de el TREE_BFS tenga como inicio un nodo distinto al vertex 1, retornar No*/
	if ( tree_bfs[0] == 1) {
		is_BFS(grafo, tree_bfs);
	} else {
		cout << "No";
	}
		
	return 0;
}