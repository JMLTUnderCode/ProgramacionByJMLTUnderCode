/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	NOTA: El codigo escrito a continuacion es un parafraseo de una solucion dado
	en internet. Explicare cada parte lo mejor posible para lograr en medida posible
	mi entiendimiento sobre el codigo.
	
	Sea n1 y n2 los numeros a concatenar. Si formamos n1n2, es decir
	C = n1 * pow(10, len(n2) ) + n2, si dicho numero C es divisible por k, entonces
	C % k. 
	
	Matematicamente se tiene que C es divisible por k, entonces 
	C % k = 0
	( n1 * pow(10, len(n2) ) + n2 ) % k = 0
	
	Sabemos que k % k = 0, y por propiedades de % se tiene que
	( n1 * pow(10, len(n2)) % k + n2 % k ) % k = k % k
	
	Despejando por propiedades de %
	n1 * pow(10, len(n2)) % k = ( k - n2%k ) % k (FORMULA)
	
	Entonces precalculamos durante el input la parte izquierda de la formula y almacenamos en un mapa, esto porque la parte
	izquierda requiere de "len(n2)" entonces como el maximo a_i dado es de 10^9 entonces para un for de 10 iteraciones,
	calculamos todos los posibles len's. Luego iteramos por los elementos del vector dado, calculamos la cantidad de digitos
	y buscamos dentro del mapa para ese nodo el valor que cumpla con el lado derecho de la formula. Luego como estamos iterando
	sobre todos los valores dados, debemos eliminar los pares n1n1 que son divisibles por k.
	
	PD: Al final tienes la version O(n^2) comentada que no sirve pa nah.
	
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int a[200005];
map<int, long long> l_equation[20];

int main() {
	
			// Precondicion
	int n,  // 1 <= n <= 2*10^5
		k;  // 2 <= k <= 10^9
	
	cin >> n >> k;
	
	// 

	for ( int t = 1; t < n+1; t++ ) {
		scanf("%d", &a[t]);
		
		// Calculamos el lado izquierdo de la formula n1 * pow(10, len(n2)) % k 
		long long aux = a[t];
		
		// iteramos el maximo de veces para el len posible de un numero es 10^9
		for ( int m = 1; m <= 10; m++ ) {
			aux = aux * 10 % k;
			
			// Almacenamos en el mapa
			l_equation[m][aux]++;
		}
	}
	
	long long count = 0;
	
	for ( int i=1; i < n+1; i++ ) {
		// iteramos sobre todos los elementos del vector y calculamos su cantidad de digitos
		int digits = log10(a[i]) + 1;
		
		//Buscamos dentro del mapa los elementos que tengan la misma cantidad de digitos que cumplan
		// con la parte derecha de la ecuacion ( k - n2%k ) % k
		count = count + l_equation[digits][ (k - a[i]%k)%k ];
		
		// Para la cantidad de digitos calculamos definimos un auxiliar y calculamos el lado izquierdo de la formula
		// dicho elemento al final del bucle permitira determina eliminar los elementos que "count" tiene de la forma
		// n1n1 divisibles por k.
		long long aux1 = 1;
		for ( int t = 1; t <= digits; t++ ) {
			aux1 = aux1 * 10 % k;
		}
		
		if( ( a[i] * aux1 % k + a[i] % k ) % k == 0 ) {
			count--;
		}
	}
	cout << count << endl;
	
	// *******************************************************************************************************************
	// Lo comentado a continuacion es hecho por mi, pensado por mi, sudado 
	// por mi. Pero no sirve pa CF e.e (Time limit exceeded on test 8)... Es O(n^2) T.T
	/*
			// Precondicion
	int n,  // 1 <= n <= 2*10^5
		k;  // 2 <= k <= 10^9
			  
	cin >> n >> k;
	long long a[n+1];
	for ( int t = 0; t < n; t++ ) {
		scanf("%longlong", &a[t]);
	}
	

	
	int count = 0;
	unsigned long long int num1, num2;
	
	for ( int indx1 = 0; indx1 < n-1; indx1++ ) {
		
		for ( int indx2 = indx1 + 1; indx2 < n; indx2++ ) {
			// num1 es la concatenacion de (indx1)(indx2)
			int digits2 = log10(a[indx2]) + 1;
			num1 = a[indx1]*pow(10, digits2) + a[indx2];
			if ( !(num1 % k != 0) ) count++;
			
			// num2 es la concatenacion de (indx2)(indx1)
			int digits1 = log10(a[indx1]) + 1;
			num2 = a[indx2]*pow(10, digits1) + a[indx1];
			if ( !(num2 % k != 0) ) count++;
	}
	
	cout << count << endl;
	*/
	
	return 0;
}
