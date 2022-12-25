/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	Trabajando con una estructura para tener la informacion del arbol, tanto hijos
	como padres, vamos recibiendo inputs, guardamos la cantidad de hijos para el nodo
	y almecenamos los inputs tal que la posicion del array/vector es el nodo que se
	agrega, es decir si el TERCER input es un 1, quiere decir que el NODO 3 se agrego
	como hijo del NODO 1.
	
	Luego, en la lista de hijos para indexado en los padres buscamos los nodos cuyos
	hijos son padres y disminuirmos la cantidad de hijos del nodo en cuestion. Esto
	permite determinar al final del loop la cantidad de HOJAS por nodo padre.
	
	Luego, se verifica que para para cada padre se cumple la condicion de ser 
	Spruce Tree.
	
*/

#include <iostream>
#include <vector>

using namespace std;

// Estructura para tener tanto los hijos como los padres por nodo del arbol.
struct InfoTree {
	public:
	vector<int> children, fathers;
	
	// Constructor
	InfoTree (int n) {
		children = vector<int>(n);
		fathers = vector<int>(n);
	}
};

int main(){
	
	/* Inicializacion de Variables */
	int n; // Precondicion: 3 <= n <= 1000
	int p;
	bool is_Spruce = true;
	
	cin >> n;
	InfoTree T(n);
	for( int i = 1; i < n; i++) {
		cin >> p; 
		
		// El "nodo I" tiene padre "p"
		T.fathers[i]=p;
		
		// El "nodo p" aumenta la cantidad de hijos en 1. Se hace
		// p-1 para "cero indexar" dentro del vector.
		T.children[p-1]++;
	}
	
	
	for ( int k = 1; k < n; k++){
		
		// Verificamos que para todo NODO K, cuyos hijos sea distinto de cero, de 
		// lo contrario se habla de un nodo HOJA.
		if ( T.children[k] != 0) {
			
			// Determinamos el padre de NODO K, a nivel de posicion cero-indexado,
			// se habla del NODO K+1. 
			int father = T.fathers[k]-1;
			
			// Reducimos el numero de hijos para dicho padre. 
			T.children[father]--;
			
			// Si la reduccion llega a 0 entonces quiere decir que todos los hijos
			// del nodo padre son padres. Esto irrumpe la propiedad de Spruce Tree.
			if ( T.children[father] == 0 ) {
				is_Spruce = false;
				break;
			}
		}
	}
	
	// Ya en este punto el vector/array tiene unica y exclusivamente los HIJOS HOJA
	// de todo nodo padre.
	int k = 0;
	
	// Mientras que sea un Spruce Tree verificamos que dichas hojas son mayor o igual
	// a 3.
	while ( is_Spruce && (k < n) ) {
		
		if ( T.children[k] < 3 && T.children[k] != 0 ) 
			is_Spruce = false;
		k++;
	}

	if (is_Spruce) {
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
