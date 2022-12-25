/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Nota: Hace poco me cambie de IDE, usaba Dev C++, ahora es Sumplime Text con configuracion 
	de competitivo en CodeForces.

	Idea General: 
	
	


*/

#include <bits/stdc++.h>
#include <stack>

using namespace std;

void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

/* Inicializacion de Variables */
int f, c; // Precondicion: 1 <= f, c <= 1000

vector<vector<int> > M_path(f, vector<int> (c, 0));
vector<int> salida(2);
vector<int> comienzo(2);
string input;

// Moves Breeders: Arriba, Izquier, Abajo,   Derecha
int m_b[4][2] = { {-1, 0}, { 0,-1}, { 1, 0}, { 0, 1} };
vector<int> aux;
vector<int> a_pos;
int variacionLen, lenPila;

void p_m(vector<vector<int> > M) {

  int n = M.size();
  int m = M[0].size();

  for ( int k = 0; k < n; k++) {
    for ( int j = 0; j < m; j++) {
      cout << M[k][j] << " ";
    }
    cout << endl;
  }

}

void p_s(stack<vector<int>> S) {
	while ( !S.empty() ) {
		cout << "(" << S.top()[0] << ", " << S.top()[1] << "), " << " ";
		S.pop();
	}
	cout << endl;
}

// Funcion que valida las coordenadas dadas. Basicamente que no se salga del rango.
bool valid_move(int a, int b) {
	return (a >= 0 && b >= 0 && a < f && b < c );
}

// Funcion que valida el moviendo de los breeders dentro del tablero.
bool valid_move_breeder( vector<vector<int>> &M_data, int a, int b ) {
	return (valid_move(a, b) && (M_data[a][b] >= 0 || M_data[a][b] == -2));
}

vector<vector<int>> empty_stack(stack<vector<int> > &P_A, stack<vector<int> > &P, vector<vector<int> > &vis ) {
	
	stack<vector<int> > p_aux;
	int z = P_A.size();
	int l = z-2;
	vector<vector<int> > path(z-1, vector<int> (2, 0)); 

	if ( !P.empty()) {
		while ( P.top() != P_A.top() ) {

			aux = P_A.top();
			if (aux != salida) {
				vis[aux[0]][aux[1]] = 2;
			}
					
			P_A.pop();
			path[l] = aux;
			l--;
		}
	}
	

	aux = P_A.top();
	vis[aux[0]][aux[1]] = 2;
	P_A.pop();
	if ( !P.empty()) {
		P.pop();
	}
	path[l] = aux;
	l--;

	p_aux = P_A;
	while (l > -1) {
		aux = p_aux.top();
		p_aux.pop();
		path[l] = aux;
		l--;
	}
	
	return path;
}

list<vector<vector<int>>> calculate_paths(vector<vector<int> > M_D, vector<int> mi_p, vector<int> sal, stack<vector<int> > &P_A, stack<vector<int> > &P) {

	list<vector<vector<int> > > p;
	vector<vector<int> > vis(f, vector<int> (c, 0));
	variacionLen = 0;
	lenPila = 0;
	
	vis[mi_p[0]][mi_p[1]] = 1;

	P.push(mi_p);

	while (!P.empty()) {
		
		variacionLen = P.size() - lenPila;
		
		a_pos = P.top();
		if ( variacionLen < 2 ) {
			P.pop();
		}

		lenPila = P.size();

		P_A.push(a_pos);

		if (a_pos == sal) {
			vector<vector<int> > c_path = empty_stack(P_A, P, vis);
			
			p.push_back(c_path);

			list<vector<vector<int> > >::iterator it = p.begin();

			while ( it != p.end() ) {
				cout << "\ncamino válido:" << endl;
				p_m(*it);
				cout << "Fin camino." << endl;
				it++;
			}

			if ( !P.empty()) {
				a_pos = P.top();
				P.pop();

				P_A.push(a_pos);
				aux = a_pos;
			} else {
				return p;
			}
			cout << "check" << endl;
			p_s(P);
			p_s(P_A);
		} else {
			aux = a_pos;
		}

		for (int k = 0; k < 4; k++) {
			if ( valid_move_breeder(M_D, a_pos[0] + m_b[k][0], a_pos[1] + m_b[k][1]) ) {
				if (vis[a_pos[0] + m_b[k][0]][a_pos[1] + m_b[k][1]] == 0) {
					if ( M_D[a_pos[0] + m_b[k][0]][a_pos[1] + m_b[k][1]] != -2 ){
						vis[a_pos[0] + m_b[k][0]][a_pos[1] + m_b[k][1]] = 1;
					} 
					aux[0] = a_pos[0] + m_b[k][0];
					aux[1] = a_pos[1] + m_b[k][1];
					P.push(aux);
				}
			}
		}

		if ( aux == a_pos ) {
			cout << "no check" << endl;
			vector<vector<int> > no_path = empty_stack(P_A, P, vis);
		}
	}
	
	return p;
}

bool valid_move_BFS( vector<vector<int>> &M_data, vector<vector<int>> &vis, int a, int b ) {
	return (valid_move(a, b) && (M_data[a][b] >= 0) && vis[a][b] == -1);
}

bool BFS(vector<vector<int> > &M_D, vector<vector<int> > p, vector<int> p_b) {

	queue<vector<int>> Cola;
	vector<int> ac_pos(2);
	vector<int> helper(2);

	vector<vector<int>> visitados(M_D.size(), vector<int> (M_D[0].size(), -1));
	int d = -2;

	for (int k = 0; k < p.size(); k++) {
		visitados[p[k][0]][p[k][1]] = d;
		d--;
	}

	if ( visitados[p_b[0]][p_b[1]] < -1 ) {
		return true;
	}

	Cola.push(p_b);
	visitados[p_b[0]][p_b[1]] = 0;

	while (!Cola.empty()) {
		ac_pos = Cola.front();
		Cola.pop();

		for (int k = 0; k < 4; k++) {
			
			if ( valid_move(ac_pos[0] + m_b[k][0], ac_pos[1] + m_b[k][1]) ) {
				
				if (visitados[ac_pos[0] + m_b[k][0]][ac_pos[1] + m_b[k][1]] < -1) {
					
					int y = abs(visitados[ac_pos[0] + m_b[k][0]][ac_pos[1] + m_b[k][1]]) - 1;
					int t = visitados[ac_pos[0]][ac_pos[1]] + 1;

					if ( (t - y) <= 0 ) {
						return true;
					}
				}
			}
			
			if ( valid_move_BFS(M_D, visitados, ac_pos[0] + m_b[k][0], ac_pos[1] + m_b[k][1]) ) {
				
				helper[0] = ac_pos[0] + m_b[k][0];
				helper[1] = ac_pos[1] + m_b[k][1];
				
				visitados[helper[0]][helper[1]] = visitados[ac_pos[0]][ac_pos[1]] + 1;
				Cola.push(helper);

			} 

		}
	}

	return false;
}

void count_battle(vector<vector<int> > &M_D, list<vector<vector<int> > > p, vector<vector<int>> pos_breeders) {

	int c_batlle = pow(10,7);
	int aux_batlle;
	
	list<vector<vector<int> > >::iterator it = p.begin();

	while ( it != p.end() ) {
		aux_batlle = 0;
		for ( int k = 0; k < pos_breeders.size(); k++) {
			if ( BFS(M_D, *it, pos_breeders[k])	) {
				aux_batlle += M_D[pos_breeders[k][0]][pos_breeders[k][1]];
			}
			
		} 
		

		if ( c_batlle > aux_batlle) {
			c_batlle = aux_batlle;
			if (c_batlle == 0) {
				cout << c_batlle;
				return;
			}
		}
		it++;
	}
	cout << c_batlle;
	return;
}

int main() {
	
	init_code();

	cin >> f >> c;
	vector<vector<int> > M_data(f, vector<int> (c, 0));
	stack<vector<int> > Pila;
	stack<vector<int> > PilaAux;
	vector<vector<int> > pos_breeders; 

	for (int k = 0; k < f; k++) {
		cin >> input;
		for (int i = 0; i < c; i++) {
			// Exit = -2
			if ( input[i] == 'E' ) {
				M_data[k][i] = -2;
				salida[0] = k;
				salida[1] = i;

			// Tree = -1
			} else if ( input[i] == 'T' ) {
				M_data[k][i] = -1;

			// MiPosicion = -3
			} else if ( input[i] == 'S' ) {
				M_data[k][i] = -3;
				comienzo[0] = k;
				comienzo[1] = i;

			// Cualguier otro numero representa la cantidad de breeders en al celda.
			} else if ( input[i] != '0') {
				// Pasar de un char a entero manejando la tabla ASCII, es restar 48 en decimal.
				int num = input[i] - 48;
				M_data[k][i] = num;
				pos_breeders.push_back({k,i});
			}
		}
	}

	if ( pos_breeders.size() == 0 ) {
		cout << 0;
		return 0;
	}

	//p_m(M_data);
	
	list<vector<vector<int> > > paths = calculate_paths(M_data, comienzo, salida, PilaAux, Pila);
	
	/*cout << "\nchick 2" << endl;
	list<vector<vector<int> > >::iterator it = paths.begin();

	while ( it != paths.end() ) {
		cout << "\ncamino válido:" << endl;
		p_m(*it);
		cout << "\nFin camino." << endl;
		it++;
	}*/

	count_battle(M_data, paths, pos_breeders);

	return 0;
}
