/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	// Primera idea: *Codigo sin comentar* Consigo TLE
	
	Consta de usar la teoria de LCA para subir y encontrar el ancestro de un nodo en altura "p" dentro de la
	matriz de ancestros "seteada" con la funcion "build_ancestors". Dentro del propio input se almancean en una
	matriz, donde las filas representan los "PISOS" del arbol, los nodos que existen en dicho piso. Una vez dado
	el "queris" para un valor "v" en altura "p", buscamos todos los nodos que se encuenten a la misma altura que "v",
	sobre ese vector de nodos para cada uno de ellos verificamos que esos nodos tienen el mismo precedesor en pasos "p"
	que el de "v", en caso afirmativo es un primo.
	
	**********************************************************************************************************************************************
	// Segunda Idea: *Codigo Comentado al final* Consigo MLE
	Consta de ir seteando o almacenando por input los ancestros del nodo. por ejemplo para el peor caso
	
	n = 5
	vec 0 1 2 3 4     (La linea recta)   
	
	Se tendria que la matriz de ancestros conforme avanza el input del "vec" se veria de esta forma
	           p 
	     1  2  3  4  5       1  2  3  4  5       1  2  3  4  5       1  2  3  4  5       1  2  3  4  5
	  1  0                1  0                1  0                1  0                1  0
	  2                   2  1  0             2  1  0             2  1  0             2  1  0
	n 3                   3                   3  2  1  0          3  2  1  0          3  2  1  0 
	  4                   4                   4                   4  3  2  1  0       4  3  2  1  0
	  5                   5                   5                   5                   5  4  3  2  1  0
	  
	Notese que vamos "uniendo" para cada nodo dado por input le agregamos su padre y luego vamos al vector
	del padre en la misma matriz, dicho vector contiene los predecesores del padre y eso lo agregamos el nodo
	actual. Note que al final de tener el input completo tendremos todos los saltos posibles para cada nodo.
	Lo que sigue es verificar para el "queris" dado los nodos en el mismo piso que "v" si en la matriz
	tienen el mismo ancestro. 
	
	Nota: El problema creo que yace en realizar el metodo "insert" de vectores en c++, la reacreacion continua
	en cada input de nuevos vectores. De forma similar pasa si realizo unicamente push_backs.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Definicion de matrices, variables y constantes.
const int max_n = pow(10,5) + 5;
const int max_jumps = 19;
int ancestors[max_n][max_jumps];
vector<int> height(max_n, 0);
vector<int> nodes_by_height[max_n];
int N, M;

// Construye la matriz de ancestro para la cantidad de saltos logaritmicos.
void build_ancestors( ) {
	
	for(int jump = 1; jump < max_jumps; jump++){
		
		for(int node = 1; node-1 < N; node++) {
			
			int ancestor_jump_1 = ancestors[node][jump];
	
			if(ancestor_jump_1 != 0 && ancestors[ancestor_jump_1][jump] != 0) {
				ancestors[node][jump+1] = ancestors[ancestor_jump_1][jump];
			}
			
		}
	}
}

// Se encarga de subir "p" pisos arriba de manera logaritmica.
int find_ancestor(int n, int h) {
    for(int i = max_jumps - 1; i >= 0; i--) {
    	
        if(h & (1 << i)) n = ancestors[n][i+1];
    }
    return n;
}

// Esta funcion se encarga de para el vector de todos los nodos en la misma altura del valor "v" verificar
// que el ancestro en pasos "p" de cada uno de ellos tiene el mismo ancestro a pasos "p" del valor "v".
int find_cousins( int v, int p ) {
	
	// Garantizamos que el predecesor de "v" en altura "p" exista.
	if ( height[v] < p) {
		return 0;
	}
	
	int cousins = 0;
	int predecessor_v = find_ancestor(v, p);
	vector<int> nodes_height_v = nodes_by_height[height[v]];
	
	for ( int node : nodes_height_v ) {
		// Si el "node" tiene el mismo predecesor que "v" son primos.
		if ( node != v && (find_ancestor(node, p) == predecessor_v) ) {
			cousins++;
		}
	}
	
	return cousins;
}

int main() {
	// Ejercicio de prueba
	//n=  15
	//    0 1 1 3 3 1 6 0 6 2 8 10 8 13 5
	//m=  3       |   3       |   3       |   3      
	//    10 1    |   12 3    |   4 1     |   11 1
	//    2 1     |   15 3    |   5 1     |   13 1
	//    7 2     |   14 1    |   7 1     |   8 1
	//            |           |           |
	//R=  0 2 4   |   1 1 0   |   1 1 1   |   1 1 0

	int father;
	cin >> N;
	
	for(int node = 1; node-1 < N; node++ ){
		cin >> father;
		
		// Mientra que el padre sea distinto de 0 actualizamos los datos del nodo,
		// como lo es el ancestro directo (padre) y la altura que es el funcion de la
		// altura del padre + .
		if ( father != 0 ) {
			ancestors[node][1] = father;
			height[node] = height[father] + 1;
		}
		
		// Guardamos por "pisos" los nodos que se encuentran el mismo.
		nodes_by_height[height[node]].push_back(node);
	}
	
	// Armamos la matriz de ancestros para los n nodos.
	build_ancestors();
	
	cin >> M;
	int v, p;
	vector<int> response(M);
	
	// Pedimos los "queris" y almanecamos en un vector de repuestas
	for( int k = 0; k < M; k++ ) {
		cin >> v >> p;
		response[k] = find_cousins(v,p);
	}
	
	// Imprimimos por pantalla el vector de respuestas como se pide en CF.
	for( int k = 0; k < M; k++ ) {
		cout << response[k] << " ";
	}
	
	return 0;
}

/*
	SEGUNDA IDEA
*/

/*
const int max_n = pow(10,5) + 5;
vector<int> ancestros[max_n];
vector<int> altura(max_n, 0);
vector<int> nodos_pisos[max_n];
int N, M;

void setear_ancestros(int nodo, int padre){
	// Agregamos el padre del nodo como su primer ancestro.
	ancestros[nodo].push_back(padre);
	
	// Unimos los ancestros del nodo actual con los ancestros del padre del nodo actual.
	ancestros[nodo].insert( ancestros[nodo].end(), ancestros[padre].begin(), ancestros[padre].end() );
}

int buscar_primos(int v, int p) {
	
	// Garantizamos que el predecesor de "v" en altura "p" exista.
	if ( altura[v] < p ) {
		return 0;
	}
	
	// Para los nodos en el mismo piso que el nodo "v" verificamos ancestros.
	vector<int> nodos_p = nodos_pisos[altura[v]];
	int primos = 0;
	for ( int k : nodos_p ) {
		if( k != v && (ancestros[v][p-1] == ancestros[k][p-1]) ) primos++;
	}
	return primos;
}

int main() {
	
	cin >> N;
	int padre;
	
	for(int nodo = 1; nodo-1 < N; nodo++ ){
		cin >> padre;

		// Mientra que el padre sea distinto de 0 determinamos la altura 
		// del nodo en cuestion
		if ( padre != 0 ) altura[nodo] = altura[padre] + 1;
		
		// La matriz de ancestros la actualizamos o "seteamos"
		setear_ancestros(nodo,padre);
		
		// Guardamos los nodos por su altura
		nodos_pisos[altura[nodo]].push_back(nodo);
	}
	
	// Pedimos los "queris" y verificamos la cantidad de primos.
	cin >> M;
	int v, p;
	vector<int> respuesta(M);
	for( int k = 0; k < M; k++ ) {
		cin >> v >> p;
		respuesta[k] = buscar_primos(v,p);
	}

	for( int k = 0; k < M; k++ ) {
		cout << respuesta[k] << " ";
	}
	
	return 0;
}
*/
