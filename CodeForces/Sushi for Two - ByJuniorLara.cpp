/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode

	Idea principal para el programa:
	
	Tenemos tres pilas/stacks, la MAIN con los elementos base, una para almacenar
	los unos y otra pila para los dos. Se iran agregando los elementos del MAIN
	a sus pilas respectivas y siempre que en la pila opuesta hayan elementos
	se eliminaran tambien.
	Ej. Top de main = 1, se agrega a la pila de unos dicho elemento, si en la
	pila de dos (opuesta) hay elementos se hace un pop y viceversa.
	
	Se llevara un conteo de pops hechos tanto a la pila de unos y de dos.
	Esto es, si la cantidad de pops = 1, es el caso base
	de longitud 2 no es de interés, en caso de que pops = 2, entonces indica
	que se agregaron 2 elementos a la pila opuesta y se eliminaron dos de la
	pila actual, por lo que longitud = 4, y asi sucesivamente.
	
	Cabe destacar que el punto clave de esta implementacion es que cuando 
	se hace un pop el contador de pops actuales para la pila opuesta se 
	resetea y en caso de que dicho pop vacíe la pila respectiva entonces la pila
	opuesta debe resetearse antes de agregar un valor a ella.
*/


#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

int main() {
	
	// Inicializacion de variables
	stack<int> mainV, oneV, twoV;
	int len=2;
	
	/* Precondicion: Una entrada n tal que 2 <= n <= 100000 y 1 <= t <= 2
	/                ambos numeros enteros.
	*/
	
	long n; cin >> n;
	int t;
	
	for (int k = 0; k < n; k++) {
		cin >> t;
		mainV.push(t);
	}
	
	// Contadores de pops actualces y previos que se le hacen tanto
	// al stack de One's y de Two's
	int pops1 = 0, pops2 = 0;
	int privPops1 = 0, privPops2 = 0 ;
	
	while( !mainV.empty() ) {
		
		if ( mainV.top() == 1 ) {
			
			if ( !twoV.empty() ) {
				//	En caso de que la pila opuesta quede vacia, entonces a futuras
				//	la informacion guardada en la pila actual debemos resetearla.
				if ( pops1 > 0 ) {
					stack<int> newoneV; 
					oneV = newoneV;
				}
				
				//  Se eliminan elementos de la pila opuesta  y
				//	reseteamos el contador de pops de la pila actual.
				pops1 = 0;
				twoV.pop();
				pops2++;
				
				if ( pops2 > 1 && (pops2 > privPops1 && pops2 > privPops2)  ) {
					// La longitud respuesta sera aumentada siempre que pase
					// la cantidad de pops de la pila contraria sea mayor 1
					// y que dicha cantidad sea mayor a los previos pops de la pila
					// anterior.
					privPops2 = pops2;
					len += 2;
				}

			}
			oneV.push(mainV.top());	
				
		} else {
			// Los comentarios anteriores aplican para las siguientes lineas
			// de codigo ya que es el caso analogo.
			
			if ( !oneV.empty() ) {
				
				if ( pops2 > 0 ) {
					stack<int> newtwoV; 
					twoV = newtwoV;
				}
				
				pops2 = 0;
				oneV.pop();
				pops1++;
				
				
				if ( pops1 > 1 && (pops1 > privPops1 && pops1 > privPops2) ) {
					privPops1 = pops1;
					len += 2;
				}
				
			}
			twoV.push(mainV.top());	
		}
		mainV.pop();
	}
	
	cout << len;
	
	return 0;
}
