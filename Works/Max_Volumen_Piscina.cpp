#include <iostream>
#include <cmath>

using namespace std;

int main(){
	
	// Inicializacion de variables fundamentales
	double materiales; // Cantidad de materiales disponibles para la obra.
	
	cout << "Ingrese cantidad de materiales disponibles: ";
	cin >> materiales;
	
	// Se debe resolver x^2 + 8x - materiales = 0
	
	// Con formula ya previamente determinada
	double x = -4 + sqrt(16 + materiales);
	double y = (materiales-4*x)/(x+4);
	
	// Impresion de datos finales
	cout << "Valores apropiados para un volumen maximo optimo:" << endl;
	cout << "Largo X = " << x << endl;
	cout << "Ancho Y = " << y << endl;

	return 0;
}
