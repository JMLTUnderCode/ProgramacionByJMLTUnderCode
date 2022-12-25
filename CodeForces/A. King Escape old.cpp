/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General: 
	
	Notemos que al posicionarse la reina en el tablero crea "4 cuadrantes" donde el rey 
	puede estar inicialmente, claramente estos cuadrantes pueden reducirse conforme la 
	posicion de la reina esta mas a un costado del tablero o mas al centro y estos
	cuadrantes basicamente son formados por zonas de jaque vectical y horizontal.
	Por tanto tener al rey en uno de estos cuadrantes y con las condiciones de movimiento 
	para la reina nos dice que el rey no puede pasar de cuadrante en cuadrante debido a 
	las zona de jaque de la reina. Dicho esto, solamente nos queda verificar que la posicion
	del rey y la posicion de victoria estan en el mismo cuadrante, pues en este cuadrante para 
	el rey es posible moverse dado que la zona de jaque viene dada por una diagonal y la diagonal
	puede ser cruzada por el rey.
		
*/
 
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
 
using namespace std;

int main(){
	
	/* Inicializacion de Variables */
	int n; // Precondicion: 3 <= n <= 1000
	vector<int> Queen_pos(2); // Precondicion: 1 <= ax, ay <= n
	vector<int> Bob_pos(2); // Precondicion: 1 <= bx, by <= n
	vector<int> pos_win(2); // Precondicion: 1 <= cx, cy <= n
	
	cin >> n;
	
	cin >> Queen_pos[0] >> Queen_pos[1];
	cin >> Bob_pos[0] >> Bob_pos[1];
	cin >> pos_win[0] >> pos_win[1];
	
	/* Bob y posicion de victoria a la izquierda de la Queen*/
	if ( (Queen_pos[0] > Bob_pos[0]) && (Queen_pos[0] > pos_win[0]) ) {
		
		/* Bob y posicion de victoria abajo de la Queen */
		if ( (Queen_pos[1] > Bob_pos[1]) && (Queen_pos[1] > pos_win[1]) ) {
			cout << "YES";
			return 0;
		}
		
		/* Bob y posicion de victoria arriba de la Queen */
		if ( (Queen_pos[1] < Bob_pos[1]) && (Queen_pos[1] < pos_win[1]) ) {
			cout << "YES";
			return 0;
		}
		
		cout << "NO";
		
	/* Bob y posicion de victoria a la derecha de la Queen */
	} else if ( (Queen_pos[0] < Bob_pos[0]) && (Queen_pos[0] < pos_win[0]) ) {
		
		/* Bob y posicion de victoria abajo de la Queen */
		if ( (Queen_pos[1] > Bob_pos[1]) && (Queen_pos[1] > pos_win[1]) ) {
			cout << "YES";
			return 0;
		}
		
		/* Bob y posicion de victoria arriba de la Queen */
		if ( (Queen_pos[1] < Bob_pos[1]) && (Queen_pos[1] < pos_win[1]) ) {
			cout << "YES";
			return 0;
		}
		
		cout << "NO";
		
	} else {
		cout << "NO";
	}
	return 0;
}
