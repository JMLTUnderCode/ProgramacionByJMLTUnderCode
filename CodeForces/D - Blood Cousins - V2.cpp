/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	
	
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

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
