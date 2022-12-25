/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #738 (Div. 2) D1. Mocha and Diana(Easy Version)
	
	Idea General:
	
	Con el uso de DSU, implementacion mostrada por Wilmer Bandres, creamos
	dos DSU's, uno para el bosque de Mocha y otro para Diana. Una vez leido 
	todos los datos por pantalla, tendremos en cada DSU los respectivos conjuntos
	ya unidos. Se debe ir probrando los "pares posibles", dicho par es de
	la forma (n1,n2), se debe comprobar para cada bosque que los representantes
	son dintintos, es decir, dentro del bosque de Mocha, n1 y n2 deben tener 
	representantes distintos esto dice que pueden unirse. Similarmente, dentro 
	del bosque de Diana realizamos la comparacion para los representantes de n1 y 
	n2, si en ambos bosques, encontramos diferentes representantes entonces 
	podemos unir dichos nodos en cada bosques.
	
*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef pair<int,int> pii;
int N, M1, M2; 				// Variables basicas del problema.
int Mocha_rp1, Mocha_rp2;	// Auxiliares para los representados del bosque de Mocha.
int Diana_rp1, Diana_rp2;	// Auxiliares para los representados del bosque de Diana.
int n1, n2;					// Auxiliares para los arcos dados de cada bosque en input.
int count_bridges = 0;		// Contador de puentes/arcos agregados en los bosques.

// Estructuras de datos.
set<pii> added_bridges;		// Permite almacenar los pares(Arco) que agregamos en el bosque.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Estructura para el algoritmo DSU = Disjoin Set Union.
struct DSU {
	int len;
	vector<int> repr;
	
	DSU(int n) : len(n) {
		repr.resize(len+1);
	}
	
	// Funciones de la Estructura DSU.
	int find(int);
	void join(int, int);
	void make_set(int);
};

// Funcion que permite crear un conjunto para un representante dado.
void DSU::make_set(int idx) {
    repr[idx] = idx;
}

// Funcion que permite buscar un representante para un elemento dado.
int DSU::find(int x) {
    return repr[x] = ((x == repr[x]) ? x : find(repr[x]) );
}

// Funcion que permite unir dos elementos dados mediante sus representantes.
void DSU::join(int n1, int n2) {
	n1 = find(n1);
    n2 = find(n2);
    repr[n1] = n2;
}

// Funcion que permite mostrar los elementos de un Set de pares por pantalla.
void draw_set(set<pii> forest) {
	for ( auto it : forest ) printf("%d %d\n", it.first, it.second );
}

int main() {
	
	// Lectura de datos.
	init_code();
	
	scanf("%d%d%d", &N, &M1, &M2);
	
	// Creamos el DSU con cantidad de nodos N+1 para "Unoindexar".
	DSU Mocha(N+1); DSU Diana(N+1);
	
	// Armamos los conjuntos singleton de cada nodo.
	for ( int k = 1; k-1 < N; k++) {
		Mocha.make_set(k); Diana.make_set(k);
	}
	
	// Leemos M1 + M2 pares de nodos. Los primeros M1 es para el bosque de Mocha, 
	// los M2-M1 siguientes para Diana.
	for ( int k = 0; k < M1+M2; k++ ) {
		scanf("%d%d", &n1, &n2);
		(k < M1) ? Mocha.join(n1, n2) : Diana.join(n1, n2);
	}
	// Fin lectura de datos.

	// Cantidad maxima de pares a construir es de (N - 1) menos el maximo entre M1 y M2.
	int arcs_possible = (N-1) - max(M1,M2);
	
	// En caso de no tener arcos posibles para armar, entonces se ha terminado la busqueda.
	if ( arcs_possible > 0 ) {
		
		// Iteramos con los nodos, pares, o arcos posibles a construir.
		for( int t = 1; t-1 < N; t++ ) {
			for( int m = t+1; m-1 < N; m++ ) {
				Mocha_rp1 = Mocha.find(t); Diana_rp1 = Diana.find(t);
				Mocha_rp2 = Mocha.find(m); Diana_rp2 = Diana.find(m);
				
				// En caso de diferentes representantes para ambos nodos en cada bosque
				// unen, ya que es posible formarlo en ambos bosques.
				if ( Mocha_rp1 != Mocha_rp2 && Diana_rp1 != Diana_rp2 ) {
					added_bridges.insert({t, m});
					Mocha.join(t, m);		// Agregamos al bosque de Mocha.
					Diana.join(t, m);		// Agregamos al bosque de Diana.
					count_bridges++;		// Aumentamos contador de arcos agregados.

					// Alcanzado la cantidad maxima de nodos posibles por construir, 
					// entonces se ha terminado.
					if ( count_bridges == arcs_possible ) {
						printf("%d\n", arcs_possible);
						draw_set(added_bridges);
						return 0;
					}
				}
			}
		}

	} else {
		printf("%d\n", arcs_possible);
		return 0;	
	}
}
