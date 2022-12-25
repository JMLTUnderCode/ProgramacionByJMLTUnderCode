/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	A continuacion se encuentran
	
	
	
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int max_n = pow(10,5) + 5;
vector<int> padres(max_n, 0);
vector<int> altura(max_n, 0);
vector<int> hijos(max_n, 0);
vector<int> nodos_pisos[max_n];

int primosDe ( vector<int> nodos, int predecesor_v, int v, int p) {
	
	int primos = 0;
	
	for ( int predecesor_k : nodos ) {
		
		if ( predecesor_k != v ) {
			int pre_k_p = predecesor_k; 
			for( int j = 1; j <= p; j++) {
				pre_k_p = padres[pre_k_p];
			}
			
			if( pre_k_p == predecesor_v ) {
				primos++;
			}
		}
	}
	return primos;
}

int BuscarPrimos( int v, int p ) {
	
	// Garantizamos que el predecesor de "v" en altura "p" exista.
	if ( altura[v] < p) {
		return 0;
	}
	
	// Buscamos el predecesor del nodo "v" que se encuentra "p" niveles arriba.
	int predecesor_v = v;
	for( int k = 0; k < p; k++) {
		predecesor_v  = padres[predecesor_v];
	}
	
	// En caso de que el predecesor de "v" en altura "p" tenga 1 unico hijo, 
	// entonces es la misma "RAMA" por donde subimos
	// por tanto no tiene ramas(hijos) a los que verificar.
	/*if( hijos[predecesor_v] == 0 ) {
		return 0;
	}*/
	
	// Buscamos el vector de todos los nodos en la misma altura que "v"
	/*vector<int> nodos_p = nodos_pisos[altura[v]];
	cout << " Pre " << v << ": " << predecesor_v << endl;
	for ( int t : nodos_p ) cout << t << " ";
	cout << endl;*/
	return primosDe(nodos_pisos[altura[v]], predecesor_v, v, p);
}

int main() {
	
	int N, M;
	int padre;
	// 15
	// 0 1 1 3 3 1 6 0 6 2 8 10 8 13 5
	cin >> N;

	for(int nodo = 1; nodo-1 < N; nodo++ ){
		cin >> padre;
		
		if ( padre != 0 ) {
			padres[nodo] = padre;
			altura[nodo] = altura[padre] + 1;
			hijos[padre]++;
		}
		
		/*if ( valor == 0 ) {
			padres[nodo] = valor;
			altura[nodo] = valor;
		} else {
			padres[nodo] = valor;
			altura[nodo] = altura[valor]+1;
			hijos[valor]++;
		}*/
		// Guardamos los nodos por su altura
		nodos_pisos[altura[nodo]].push_back(nodo);
	}
	
	cin >> M;
	int v, p;
	vector<int> respuesta(M);
	for( int k = 0; k < M; k++ ) {
		cin >> v >> p;
		respuesta[k] = BuscarPrimos(v,p);
	}
	
	/*cout << "V-Padres: ";
	for( int k = 1; k-1 < N; k++ ) {
		cout << padres[k] << " ";
	}
	
	cout << "\nV-hijos: ";
	for( int k = 1; k-1 < N; k++ ) {
		cout << hijos[k] << " ";
	}
	
	cout << "\nV-altura: ";
	for( int k = 1; k-1 < N; k++ ) {
		cout << altura[k] << " ";
	}
	
	cout << "\nV-nodos_pisos: " << endl;
	for( int k = 0; k < N; k++ ) {
		cout << " - Piso " << k << ": ";
		for ( int t : nodos_pisos[k] ) cout << t << " ";
		cout << endl;
	}
	*/
	for( int k = 0; k < M; k++ ) {
		cout << respuesta[k] << " ";
	}
	
	return 0;
}
