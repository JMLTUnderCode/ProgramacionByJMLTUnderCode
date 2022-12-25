/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Lyft Level 5 Challenge 2018 - Elimination Round - A. King Escape (Easy Implementation)

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
 
#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
typedef vector<int> vi;
int N;						// Variables basicas del problema.

// Estructuras de datos.
vi Queen_pos(2); 			// Vector que almacena la posicion de la reina. Precondicion: 1 <= ax, ay <= n
vi Bob_pos(2); 				// Vector que almacena la posicion del rey. Precondicion: 1 <= bx, by <= n
vi pos_win(2); 				// Vector que almacena la posicion objetivo. Precondicion: 1 <= cx, cy <= n

// Funcion para lectura de documentos/casos de prueba.
void init_code() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

int main(){
	
	// Lectura de datos.
	init_code();
		
	scanf("%d", &N);
	
	scanf("%d%d", &Queen_pos[0], &Queen_pos[1]);

	scanf("%d%d", &Bob_pos[0], &Bob_pos[1]);

	scanf("%d%d", &pos_win[0], &pos_win[1]);

	// Fin lectura de datos.

	// Bob y posicion de victoria a la izquierda de la Queen
	if ( (Queen_pos[0] > Bob_pos[0]) && (Queen_pos[0] > pos_win[0]) ) {
		
		/* Bob y posicion de victoria abajo de la Queen */
		if ( (Queen_pos[1] > Bob_pos[1]) && (Queen_pos[1] > pos_win[1]) ) {
			printf("%s\n", "Yes"); return 0;
		}
		
		/* Bob y posicion de victoria arriba de la Queen */
		if ( (Queen_pos[1] < Bob_pos[1]) && (Queen_pos[1] < pos_win[1]) ) {
			printf("%s\n", "Yes"); return 0;
		}
		
		printf("%s\n", "No");
		
	// Bob y posicion de victoria a la derecha de la Queen
	} else if ( (Queen_pos[0] < Bob_pos[0]) && (Queen_pos[0] < pos_win[0]) ) {
		
		/* Bob y posicion de victoria abajo de la Queen */
		if ( (Queen_pos[1] > Bob_pos[1]) && (Queen_pos[1] > pos_win[1]) ) {
			printf("%s\n", "Yes"); return 0;
		}
		
		/* Bob y posicion de victoria arriba de la Queen */
		if ( (Queen_pos[1] < Bob_pos[1]) && (Queen_pos[1] < pos_win[1]) ) {
			printf("%s\n", "Yes"); return 0;
		}
		
		printf("%s\n", "No");
		
	} else {
		printf("%s\n", "No"); 
	}
	return 0;
}
