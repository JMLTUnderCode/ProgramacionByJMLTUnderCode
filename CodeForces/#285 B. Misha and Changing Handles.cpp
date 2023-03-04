/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Codeforces Round #285 (Div. 2) B. Misha and Changing Handles
	
	Idea General:
	
	Mediante el uso de "mapas" almacenamos para cada nuevo nick su respectiva
	llave y value(entero que representa la posicion dentro del vector de clientes)
	una vez asi verificamos que para nuevos pedidos de cambio de nicks en caso de
	estar reflejado en el mapa entonces debemos buscar su value y dicho numero indica
	la posicion del vector que debemos cambiar por el nuevo nick.
	
*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef vector<string> vs;
int q;				// Variables basicas del problema.
int numerator = 0;		// Numerador de los nicks finales.
vs o_nick;			// Permite almanecar los nicks(clientes) primarios.
vs f_nick;			// Permite almacenar los nicks finales de cada cliente.
string s1, s2;			// Variables de uso auxiliar.

// Estructuras de datos.
map<string, int> final_requests;// Se mapea por key = string y value = entero para el final nick.

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

int main() {
	// Mejora de velocidad para el cin y cout.
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	// Lectura de datos.
	init_code();

	cin >> q;
	
	for ( int k = 0; k < q; k++) {
		
		cin >> s1 >> s2;
	
		// En caso de no estar S1 representado en el mapa, se agrega como
		// cliente nuevo. Se le asigna incluso una posicion (numerator) dentro del
		// vector de nicks originales y de finales.
		if(!final_requests.count(s1)) {
	        	final_requests[s2] = numerator;
	        	o_nick.push_back(s1);
			f_nick.push_back(s2);
			numerator++;
	            
	        // En caso de S1 estar representado en el mapa, tomamos la posicion
	        // segunda (value) la key de S1 y reasignamos dentro de f_nick el
	        // nick pedido por el cliente ya existente.
	        } else {
	        	int pos = final_requests[s1];
	        	final_requests[s2] = pos;
	        	f_nick[pos] = s2;
		}
	}
	
	// Mostramos por pantalla los valores iniciales y finales para cada cliente.
	cout << o_nick.size() << endl;
	for( int k = 0; k < o_nick.size(); k++) cout << o_nick[k] << " " << f_nick[k] << endl;

	return 0;
}
