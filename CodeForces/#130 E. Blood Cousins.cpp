/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #130 (Div. 2) E. Blood Cousins

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

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef vector<int> vi;
int N, M;
const int max_n = (1e5)+5;
const int max_m = (1e5)+5;
int father;
int v, p;


// Estructuras de datos.
int fathers[max_n];
int levels[max_n];
vi Graph[max_n];

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

int find_p_ancestor(int v, int p) {
	int cousins = 0;

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

	// Lectura de datos.
	init_code();
	
	scanf("%d", &N);
	for(int node = 1; node-1 < N; node++ ){
		scanf("%d", &father);
		fathers[node] = father;
		if (father != 0) {
			Graph[father].push_back(node);
			levels[node] = levels[father]+1;
		} else {
			levels[father] = 0;
		}
	}
	
	scanf("%d", &M);
	for ( int query = 1; query-1 < M; query++) {
		scanf("%d%d", &v, &p);
		printf("%d ", find_p_ancestor(v, p));
	}
	
	return 0;
}