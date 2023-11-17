#include <iostream>
#include <math.h>

using namespace std;

int main(){
	double variacion_y;
	double x_distancia_tanque;
	double vel_inicial = 250;
	
	cout << "Ingrese distancia tanque: "; cin >> x_distancia_tanque;
	
	double tetha_min = 0;
	double tetha_max = 90;
	double x_min = 999999999, x_max = 0;
	double x_variable;
	double tiempo_vuelo;
	
	for(double tetha_variable = tetha_min; tetha_variable < 90; tetha_variable += 0.01){
		variacion_y = x_distancia_tanque*tan(tetha_variable*3.1415/180) - (0.5*9.81*pow(x_distancia_tanque/vel_inicial, 2)*(1/pow(cos(tetha_variable*3.1415/180),2)));
		tiempo_vuelo = vel_inicial*sin(tetha_variable*3.1415/180)/9.81;
		x_variable = (vel_inicial*cos(tetha_variable*3.1415/180) * tiempo_vuelo) - (x_distancia_tanque + 300);
		if(variacion_y > 1800 && x_variable > 0) {
			x_min = x_variable;
			tetha_min = tetha_variable;
		}
	}
	
	for(double tetha_variable = tetha_max; tetha_variable > 0; tetha_variable -= 0.01){
		variacion_y = x_distancia_tanque*tan(tetha_variable*3.1415/180) - (0.5*9.81*pow(x_distancia_tanque/vel_inicial, 2)*(1/pow(cos(tetha_variable*3.1415/180),2)));
		tiempo_vuelo = vel_inicial*sin(tetha_variable*3.1415/180)/9.81;
		x_variable = (vel_inicial*cos(tetha_variable*3.1415/180) * tiempo_vuelo) - (x_distancia_tanque + 300);
		if(variacion_y > 1800 && x_variable > 0) {
			x_max = x_variable;
			tetha_max = tetha_variable;
		}
	}
	
	cout << "El minimo angulo(rad) de disparo es: " << tetha_min << ", con distancia minima desde montaña: " << x_min << ".\n";
	cout << "El maximo angulo(rad) de disparo es: " << tetha_max << ", con distancia maxima desde montaña: " << x_max << ".\n";
	
	if( x_min < 10 || x_max < 10 ){
		cout << "Se ordena detener el camion, colision inminente.\n";
	}

	return 0;
}
