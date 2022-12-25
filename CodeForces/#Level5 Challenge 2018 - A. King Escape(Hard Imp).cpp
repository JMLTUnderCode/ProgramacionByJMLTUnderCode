/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Lyft Level 5 Challenge 2018 - Elimination Round - A. King Escape (Hard Implementation)

	Idea General: 
	
	Se arma una matriz de visitados NxN, vamos analizando y moviendonos en el tablero
	siempre y cuando sea posible. Estas posiciones válidas se almacenan en una cola
	tal como en BFS, si alguna de estas posiciones concuerdan con la de llegada entonces
	decimos YES (El rey puede moverse hasta el objetivo). Cuando hayamos recorrido todas las
	posiciones posibles del rey y no hemos dado con la de llegada decimos que NO.
	
	Una vez posicionado en un punto del tablero marcado por el Rey, almacenamos precisamente
	de los 8 posibles movimientos del rey los que sean válidos.

*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef vector<int> vi;
typedef vector<vi> vii;
int N;						// Variables basicas del problema.
int maximo = 1005;			// Cota maxima para N.
vi a_pos;					// Posicion actual del rey Bob.
vi aux(2);					// Posicion auxiliar del rey para luego ser verificada.

// Estructuras de datos.
vi Queen_pos(2); 			// Vector que almacena la posicion de la reina. Precondicion: 1 <= ax, ay <= n
vi Bob_pos(2); 				// Vector que almacena la posicion del rey. Precondicion: 1 <= bx, by <= n
vi pos_win(2); 				// Vector que almacena la posicion objetivo. Precondicion: 1 <= cx, cy <= n
vii vis(maximo, vi (maximo, 0));	// Matriz de visitados para cada posicion del tablero. 
queue<vi> path_Bob;			// Estructura Queue que permite llevar control de la ruta del rey Bob.

// Moves King:    Arriba, Sup.Izq, Izquier,  Inf.Izq, Abajo,   Inf.Der, Derecha, Sub.Dere.
int m_k[8][2] = {{-1, 0}, {-1,-1}, { 0,-1},  { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}};

// Funcion para lectura de documentos/casos de prueba.
void init_code() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Funcion que permite ajustar la entrada de datos a la 0-indexacion de matrices en C++.
void adjust_pos(vi &A){
	int aux;
	// Restamos en eje x.
	A[0]--;
	// Ajustamos la vectical 0 indexada.
	A[1] = N - A[1];
	// Intercambiamos posiciones para obtener x = filas e y = columnas.
	aux = A[0];
	A[0] = A[1];
	A[1] = aux;
}

// Funcion que valida las coordenadas dadas. Basicamente que no se salga del rango.
bool valid_move( int f, int c) {
	return (f >= 0 && c >= 0 && f < N && c < N);
}

// Funcion que valida el moviendo del rey dentro del tablero. Entre las condiciones
// que sea válida y que no entre en una celda alcanzable por la Reina.
bool valid_move_king( int f, int c ) {
	return (valid_move(f, c) && (abs(Queen_pos[0]-f) != abs(Queen_pos[1]-c)) && (Queen_pos[0] != f) && (Queen_pos[1] != c));
}

// Funcion modificada usando ideas de BFS para obtener la posicion de llegada/Win del rey Bob.
void king_path() {
	// Agregamos y marcamos el primer elemento/posicion.
	path_Bob.push(Bob_pos);
	vis[Bob_pos[0]][Bob_pos[1]] = 1;

	while (!path_Bob.empty()) {
		a_pos = path_Bob.front();
		path_Bob.pop();
		aux = a_pos;

		// Recorremos todos los posibles movimientos del rey y lo agregamos a la path_Bob.
		for (int k = 0; k < 8; k++) {
			if (valid_move_king(a_pos[0] + m_k[k][0] , a_pos[1] + m_k[k][1]) ) {
				if (vis[a_pos[0] + m_k[k][0]][a_pos[1] + m_k[k][1]] == 0) {
					vis[a_pos[0] + m_k[k][0]][a_pos[1] + m_k[k][1]] = 1;
					aux[0] = a_pos[0] + m_k[k][0];
					aux[1] = a_pos[1] + m_k[k][1];
					path_Bob.push(aux);

					// Si encontramos una posicion auxiliar igual a la objetivo, entonces hemos
					// concluido con la búsqueda del path.
					if (aux == pos_win) {
						printf("%s\n", "Yes"); return;
					} 
				}
			}
			
		}
		// En caso de que no haya modificacion en la posicion (cambiado de celda) y
		// la path_Bob este vacia entonces no hemos encontrado la posicion objetivo.
		if ( (aux == a_pos) && path_Bob.empty()) {
			printf("%s\n", "No"); return;
		}
	}
}

int main() {
	
	// Lectura de datos.
	init_code();
	
	// Solicitamos datos por pantalla y ajustamos las coordenadas dadas.	
	scanf("%d", &N);

	scanf("%d%d", &Queen_pos[0], &Queen_pos[1]);
	adjust_pos(Queen_pos);

	scanf("%d%d", &Bob_pos[0], &Bob_pos[1]);
	adjust_pos(Bob_pos);

	scanf("%d%d", &pos_win[0], &pos_win[1]);
	adjust_pos(pos_win);
	// Fin lectura de datos.

	// Buscamos la posicion objetivo.
	king_path();

	return 0;
}