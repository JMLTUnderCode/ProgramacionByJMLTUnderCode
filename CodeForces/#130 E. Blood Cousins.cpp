/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #130 (Div. 2) E. Blood Cousins

	Idea General: 
	


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
int ancestor, cousins;

// Estructuras de datos.
int fathers[max_n];
int levels[max_n];
int nodes_levels[max_n];
vi Graph[max_n];


// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

int find_p_ancestor(int v, int p) {
	int a = v;
	for ( int k = 0; k < p; k++ ) a = fathers[a];
	return a;
}

int DFS( int a, int v ) {
	stack<int> Pila;
	int c = 0;

	Pila.push(a);

	while( !Pila.empty() ) {
		int node = Pila.top();
		Pila.pop();

		for (auto it : Graph[node]) {
			if ( levels[it] == levels[v] && it != v) c++;
			if ( levels[it] > levels[v] ) return c;
			Pila.push(it);
		}
	}
	return c;
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
			levels[node] = levels[father] + 1;
		} else {
			levels[father] = 0;
		}

		nodes_levels[levels[node]]++;
	}
	
	scanf("%d", &M);
	for ( int query = 1; query-1 < M; query++) {
		scanf("%d%d", &v, &p);
		cousins = 0;
		if (levels[v] - p > -1 && nodes_levels[levels[v]] > 1 ) {
			ancestor = find_p_ancestor(v, p);
			cousins = DFS(ancestor, v);
		}
		
		printf("%d ", cousins);
	}
	
	return 0;
}