/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Nota: Hace poco me cambie de IDE, usaba Dev C++, ahora es Sumplime Text con configuracion 
	de competitivo en CodeForces.

	Idea General: 
	
	Se arma una matriz de visitados nxn, vamos analizando y moviendonos en el tablero
	siempre y cuando sea posible. Estas posiciones válidas se almacenan en una cola
	tal como en BFS, si alguna de estas posiciones concuerdan con la de llegada entonces
	decimos YES (El rey puede moverse hasta el objetivo). Cuando hayamos recorrido todas las
	posiciones posibles del rey y no hemos dado con la de llegada decimos que NO.
	
	Una vez posicionado en un punto del tablero marcado por el Rey, almacenamos precisamente
	de los 8 posibles movimientos del rey los que sean válidos.

*/

#include <bits/stdc++.h>

using namespace std;

void init_code() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

// Funcion que permite ajustar la entrada de datos a la 0-indexacion de matrices en C.
vector<int> adjust_pos(vector<int> A, int n){
	int aux;
	// Restamos en eje x.
	A[0]--;
	// Ajustamos la vectical 0 indexada.
	A[1] = n - A[1];
	// Intercambiamos posiciones para obtener x = filas e y = columnas.
	aux = A[0];
	A[0] = A[1];
	A[1] = aux;

	return A;
}

// Funcion que valida las coordenadas dadas. Basicamente que no se salga del rango.
bool valid_move(int n, int f, int c) {
	return (f >= 0 && c >= 0 && f < n && c < n);
}

// Funcion que valida el moviendo del rey dentro del tablero. Entre las condiciones
// que sea válida y que no entre en una celda alcanzable por la Reina.
bool valid_move_king( int n, vector<int> Q_p, int f, int c ) {
	return (valid_move(n, f, c) && (abs(Q_p[0]-f) != abs(Q_p[1]-c)) && (Q_p[0] != f) && (Q_p[1] != c));
}

// Funcion modificada usando ideas de BFS para obtener la posicion de llegada/Win del
// rey Bob.
void king_path(int n, vector<int> Q_p, vector<int> B_p, vector<int> p_w) {
	// Moves King:    Arriba, Sup.Izq, Izquier,  Inf.Izq, Abajo,   Inf.Der, Derecha, Sub.Dere.
	int m_k[8][2] = {{-1, 0}, {-1,-1}, { 0,-1},  { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}};

	// Inicializacion de variables y matriz de visitados.
	queue<vector<int> > Cola;
	vector<int> a_pos;
	vector<int> aux(2);
	vector<vector<int> > vis(n, vector<int> (n, 0));

	// Agregamos y marcamos el primer elemento/posicion.
	Cola.push(B_p);
	vis[B_p[0]][B_p[1]] = 1;

	while (!Cola.empty()) {
		a_pos = Cola.front();
		Cola.pop();
		aux = a_pos;

		// Recorremos todos los posibles movimientos del rey y lo agregamos a la cola.
		for (int k = 0; k < 8; k++) {
			if (valid_move_king(n, Q_p, a_pos[0] + m_k[k][0] , a_pos[1] + m_k[k][1]) ) {
				if (vis[a_pos[0] + m_k[k][0]][a_pos[1] + m_k[k][1]] == 0) {
					vis[a_pos[0] + m_k[k][0]][a_pos[1] + m_k[k][1]] = 1;
					aux[0] = a_pos[0] + m_k[k][0];
					aux[1] = a_pos[1] + m_k[k][1];
					Cola.push(aux);

					if (aux == p_w){
						cout << "Yes";
						return;
					}
				}
			}
			
		}
		// En caso de que no haya modificacion en la posicion (cambiado de celda) y
		// la cola este vacia entonces no hemos encontrado la posicion objetivo.
		if ( (aux == a_pos) && Cola.empty()) {
			cout << "No";
			return;
		}
	}
}


int main() {
	
	init_code();

	/* Inicializacion de Variables */
	int n; // Precondicion: 3 <= n <= 1000
	vector<int> Queen_pos(2); // Precondicion: 1 <= ax, ay <= n
	vector<int> Bob_pos(2); // Precondicion: 1 <= bx, by <= n
	vector<int> pos_win(2); // Precondicion: 1 <= cx, cy <= n
	
	// Solicitamos datos por pantalla y ajustamos las coordenadas dadas.	
	cin >> n;

	cin >> Queen_pos[0] >> Queen_pos[1];
	Queen_pos = adjust_pos(Queen_pos, n);

	cin >> Bob_pos[0] >> Bob_pos[1];
	Bob_pos = adjust_pos(Bob_pos, n);

	cin >> pos_win[0] >> pos_win[1];
	pos_win = adjust_pos(pos_win, n);
	
	// Buscamos la posicion objetivo.
	king_path(n, Queen_pos, Bob_pos, pos_win);

	return 0;
}