/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	Mediante el uso de "mapas" almacenamos para cada nuevo nick su respectiva
	llave y value(entero que representa la posicion dentro del vector de clientes)
	una vez asi verificamos que para nuevos pedidos de cambio de nicks en caso de
	estar reflejado en el mapa entonces debemos buscar su value y dicho numero indica
	la posicion del vector que debemos cambiar por el nuevo nick.
	
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	
			// Precondicion:
	int q;	// 1 <= q <= 1000
	
	cin >> q;
	
	// Inicializacion de variables: Un mapa para almacenar por key = string y
	// value = entero que representa el indice dentro del vector f_nick.
	// o_nick sirve para almanecar los nicks(clientes) primarios.
	map<string, int> final_requests;
	vector<string> o_nick, f_nick;
	string s1, s2;
	
	int iter = 0;
	
	for ( int k = 0; k < q; k++) {
		
		cin >> s1 >> s2;
	
		// En caso de no tener S1 representado en el mapa, se agrega como
		// cliente nuevo. Se le asigna incluso una posicion (iter) dentro del
		// vector de nicks originales y de finales.
		if(!final_requests.count(s1)) {
            final_requests[s2] = iter;
            o_nick.push_back(s1);
            f_nick.push_back(s2);
            iter++;
            
        // En caso de S1 estar represetnado en el mapa, tomamos la posicion
        // (value) segunda la key de S1 y reasignamos dentro de f_nick el
        // nick pedido por el cliente ya existente.
        } else {
        	int pos = final_requests[s1];
        	final_requests[s2] = pos;
        	f_nick[pos] = s2;
		}
	}
	
	// Mostramos por pantalla los valores iniciales y finales para cada cliente.
	cout << o_nick.size() << endl;
	for( int k = 0; k < o_nick.size(); k++) {
		cout << o_nick[k] << " " << f_nick[k] << endl;
	}

	return 0;
}
