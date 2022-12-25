/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode

	Idea principal para el programa:
	Como se debe contar la cantidad de piramides que se pueden hacer con todas
	las cartas en mano, primero determinamos una formula cerrada para las cartas
	necesarias para una piramide con k pisos
	
	    k
	  ____
	  \     (2*i + i - 1) = k*((3*k)+1)/2 
	  /___
       i=1
       
    Y como necesitamos saber cuantas piramides podemos formar con n cartas, entonces
	con un WHILE vamos restando la cantidad de cartas para hacer la piramide mas
	grande hasta que se nos acabe el mazo de cartas por asi decirlo.   
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;


// Funciones

int BinaryS( long long Cards ){ // Implementacion tradicional
	int L = 0;
	long long R = 1000*1000*1000;

	while ( L < R ) {
		
		long long mid = (L+R+1)/2;
		
		if ( ( mid*((3*mid)+1)/2 ) <= Cards ) {
			L = mid;
		} else {
			R = mid - 1;
		}
	}
	
	return L;
}


int main() {
	
	// Cantidad de lecturas por pantalla
	int t; cin >> t;
	
	// Precondicion: 1 <= t <= 1000
	assert( 0 < t <= 1000 );
	
	// Definimos variables
	long long inputs;
	long long pyramids, floor;
	
	for ( int k = 0; k < t; k++ ) {
		cin >> inputs;
		pyramids = 0;
		
		// Mientras que existan dos o mas cartas en mano contamos la cantidad
		// de piramides mas altas que se pueden realizar.
		while ( inputs > 1 ) {
			
			// Vemos la cantidad de pisos que podemos formar con las cartas 
			// actuales.
			floor = BinaryS(inputs);
			
			// Usando la formula cerrada con la cantidad de pisos nos da como
			// respuesta la cantidad de cartas justas y necesarias para dichos
			// pisos, pues esto lo restamos a la cantidad de cartas actuales.
			inputs = inputs - ( floor*((3*floor)+1)/2 );
			
			// Aumentamos la cantidad de piramides
			pyramids++;
		}
		
		cout << pyramids << endl;
	}
	
	return 0;
}
