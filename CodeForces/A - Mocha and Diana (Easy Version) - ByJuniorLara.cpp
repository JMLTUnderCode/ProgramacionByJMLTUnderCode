/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	Con el uso de DSU, implementacion mostrada por Wilmer Bandres, creamos
	dos DSU's, uno para el bosque de Mocha y otro para Diana. Una vez leido 
	todos los datos por pantalla, tendremos en cada DSU los respectivos conjuntos
	ya unidos. En ese caso, debemos ir probrando los "pares posibles", dicho par de
	la forma (n1,n2) se debe comprobar para cada bosque, que los representantes
	son dintintos. Es decir, dentro del bosque de Mocha, n1 y n2 deben tener 
	representantes distintos, esto dice que pueden unirse. Similarmente, dentro 
	del bosque de Diana realizamos la comparacion para los representantes de n1 y 
	n2. Si en ambos bosques, encontramos diferentes representantes entonces 
	podemos unir dichos nodos en ambos bosques.
	
*/

#include <iostream>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

struct DSU {
	int len;
	vector<int> repr;
	
	DSU(int n) : len(n) {
		repr.resize(len+1);
	}
	
	int find(int);
	void join(int, int);
	void make_set(int);
};

void DSU::make_set(int idx) {
    repr[idx] = idx;
}

int DSU::find(int x) {
    return repr[x] = ((x == repr[x]) ? x : find(repr[x]) );
}

void DSU::join(int n1, int n2) {
	n1 = find(n1);
    n2 = find(n2);
    repr[n1] = n2;
}


void draw_set(set<pair<int,int>> N) {
	for ( pair<int,int> i : N ) {
		cout << i.first << " " << i.second << endl;;
	}
}


int main() {
	
	// Inicializacion de variables y definicion de Precondicion
	
			 // Precondicion:
	int n,   //   1 <= n  <= 1000 
		m1,  //   0 <= m1 < n
		m2;  //   0 <= m2 < n
	
	cin >> n >> m1 >> m2;
	
	// Creamos el DSU con cantidad de nodos + 1 para "Unoindexar"
	DSU Mocha(n+1);
	DSU Diana(n+1);
	
	// Armamos los conjuntos singleton de cada nodo.
	for ( int k = 1; k < n+1; k++) {
		Mocha.make_set(k);
		Diana.make_set(k);
	}
	
	// Leemos m1 + m2 pares de nodos. 
	int n1, n2;
	for ( int k = 0; k < m1+m2; k++ ) {
		
		cin >> n1 >> n2;
		// Los primeros m1 son del bosque de Mocha
		if ( k < m1 ) {
			Mocha.join(n1,n2);

		// Los m2 - m1 pares son del bosque de Diana
		} else {
			Diana.join(n1,n2);
		}
		
	}

	// Cnatidad maxima de pares a construir es de (nodos - 1) - el maximo
	// de arcos ya formados en uno de los bosques.
	int pair_nodes_p = (n-1) - max(m1,m2);
	set<pair<int,int>> pairs;
	
	if ( pair_nodes_p != 0 ) {
		int Mrp1, Mrp2;
		int Drp1, Drp2;
		int count = 0;
		
		// Iteramos con los nodos, pares, o arcos posibles a construir.
		for( int t = 1; t < n+1; t++ ) {
			
			for( int m = t+1; m < n+1; m++ ) {
				Mrp1 = Mocha.find(t);
				Mrp2 = Mocha.find(m);
				Drp1 = Diana.find(t);
				Drp2 = Diana.find(m);
				
				// En caso de diferentes representantes para ambos
				// nodos en cada bosque se unen.
				if ( Mrp1 != Mrp2 && Drp1 != Drp2 ) {
					pairs.insert({t, m});
					Mocha.join(t,m);
					Diana.join(t,m);
					count++;
					// Cuando ya alcanzamos la cantidad maxima de nodos
					// posibles por construir, entonces terminamos.
					if ( count == pair_nodes_p ) {
						cout << pair_nodes_p << endl;
						draw_set(pairs);
						return 0;
					}
				}
			}
		}
		
	} else {
		cout << pair_nodes_p << endl;
		return 0;	
	}
}
