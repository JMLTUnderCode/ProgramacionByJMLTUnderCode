#include <iostream>
#include <math.h>

using namespace std;

int main(){
	// Solicitamos los metros para el pasillo 1.
	double x;
	cout << "Ancho X metros para pasillo 1, rango [6, 12]: ";
	cin >> x;
	while(x > 12 || x < 6) {
		cout << "Intente de nuevo, con valores entre [6, 12]: ";
		cin >> x;
	}
		
	// Solicitamos los metros para el pasillo 2.		
	double y;
	cout << "Ancho Y metros para pasillo 2, rango [6, 12]: ";
	cin >> y;
	while(y > 12 || y < 6 ) {
		cout << "Intente de nuevo, con valores entre : ";
		cin >> y;
	}
	
	// Angulos en radianes y luego se pasan a grados.
	double r = atan(pow(x, 1.0/3.0) / pow(y, 1.0/3.0));
	double pi = 3.141592; // Valor pi constante.
	double angulo = r * 180 / pi;
	
	// Calculamos los segmentos, y los totales.
	double parte1 = x / sin(r);
	double parte2 = y / cos(r);
	double cabilla_completa = parte1 + parte2;
	
	// Resultados
	cout << "Longitud de cabilla maximo es: " << cabilla_completa << " metros." << endl;
	cout << "Angulo de inclinacion es: " << angulo << " grados." << endl;

	system("pause");
}
