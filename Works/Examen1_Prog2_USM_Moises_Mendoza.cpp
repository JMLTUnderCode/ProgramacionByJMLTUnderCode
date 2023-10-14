#include <iostream>
#include <math.h>

using namespace std;

int main(){
	// Inicializacion de variables
	double Xmts = 0, Ymts = 0; 	// Anchos de pasillos
	double radians, tetha; 		// Algulos tanto en grados como radianes.
	double PI = 3.141592;		// Constante universal PI
	double S1, S2, L_max;		// Segmentos de la cabilla.
	
	// Lectura de datos
	cout << "Ingrese ancho X para pasillo 1: ";
	cin >> Xmts;
	while(Xmts < 6 || Xmts > 12) {
		cout << "Error - Rango Permitido 6mts a 12 mts.\n Intente de nuevo: ";
		cin >> Xmts;
	}
		
	cout << "Ingrese ancho Y para pasillo 2: ";
	cin >> Ymts;
	while(Ymts < 6 || Ymts > 12) {
		cout << "Error - Rango Permitido 6mts a 12 mts.\n Intente de nuevo: ";
		cin >> Ymts;
	}
	
	radians = atan(pow(Xmts, 1.0/3.0) / pow(Ymts, 1.0/3.0)); //Angulo de inclinacion en radianes.
	tetha = radians * 180 / PI; // Angulo de inclinacion en grados.
	
	S1 = Xmts / sin(radians); 	// Segmento 1
	S2 = Ymts / cos(radians);	// Segmento 2
	L_max = S1 + S2; 			// Segmento total/Longitud total de la cabilla
	
	// Mostrando calculos finales y respuesta
	cout << "El segmento maximo de cabilla: " << L_max << " mts." << endl;
	cout << "Angulo tetha optimo: " << tetha << " grados." << endl;

	return 0;
}
