#include <iostream>
#include <math.h>

using namespace std;

int main(){
	double x_distancia_tanque;
	cout << "Ingrese distancia tanque: "; cin >> x_distancia_tanque;
	
	double zona_minada = 1400;
	if (x_distancia_tanque >= zona_minada){
		// Datos
		double pi = 3.141592;
		double g = 9.81;
		double vel_inicial = 250;
		double altura_montania = 1800;
		double centro_a_extremo_montania = 300;
		// Variables a calcular y auxiliares.
		double variacion_y;
		double tetha_min = 0;
		double tetha_max = 90;
		double angulo;
		double x_min = 999999999, x_max = 0;
		double x_variable;
		double tiempo, tiempo_alt_max;
		double x_total;
		
		// Iteramos desde 0 hasta 90 grados buscando el menor angulo y el menor x sobrante luego de la montania.
		for(double tetha_variable = tetha_min; tetha_variable <= 90; tetha_variable += 0.01){
			// Convirtiendo a radianes.
			angulo = tetha_variable*pi/180; 
			
			// Calculamos el tiempo para el angulo actual respecto a la distancia del tanque.
			tiempo = x_distancia_tanque/(vel_inicial*cos(angulo));
			
			// Calculando la altura 
			variacion_y = vel_inicial*sin(angulo)*tiempo - g*pow(tiempo, 2)/2;
			
			// Calculamos la distancia sobrante menos la distancia total del tanque mas los 300 metros a la derecha de la montania.
			tiempo_alt_max = (0 - vel_inicial*sin(angulo))/(-g);
			x_total = 0 + vel_inicial*cos(angulo)*(2*tiempo_alt_max);
			x_variable = x_total - (x_distancia_tanque + 300);
			
			// Verificamos que la altura sea mayor que la montaña y que la distancia sobrante sea mayor a 0.
			if(variacion_y > altura_montania && x_variable >= 0) {
				x_min = x_variable;			// Guardamos el x minimo.
				tetha_min = tetha_variable; // Guardamos el algulo minimo.
			}
		} 
		
		// Iteramos desde 90 a 0 grados buscando el mayor angulo y el mayor x sobrante luego de la montania.
		for(double tetha_variable = tetha_max; tetha_variable >= 0; tetha_variable -= 0.01){
			// Convirtiendo a radianes.
			angulo = tetha_variable*pi/180; 
			
			// Calculamos el tiempo para el angulo actual respecto a la distancia del tanque.
			tiempo = x_distancia_tanque/(vel_inicial*cos(angulo));
			
			// Calculando la altura 
			variacion_y = vel_inicial*sin(angulo)*tiempo - g*pow(tiempo, 2)/2;
			
			// Calculamos la distancia sobrante menos la distancia total del tanque mas los 300 metros a la derecha de la montania.
			tiempo_alt_max = (0 - vel_inicial*sin(angulo))/(-g);
			x_total = 0 + vel_inicial*cos(angulo)*(2*tiempo_alt_max);
			x_variable = x_total - (x_distancia_tanque + 300);
			
			// Verificamos que la altura sea mayor que la montaña y que la distancia sobrante sea mayor a 0.
			if(variacion_y > altura_montania && x_variable >= 0) {
				x_max = x_variable;			// Guardamos el x maximo.
				tetha_max = tetha_variable; // Guardamos el algulo maximo.
			}
		}
		
		// Convirtiendo de radianes a grados para ser mostrados en pantalla.
		cout << "El minimo angulo(rad) de disparo es: " << tetha_min << ", con distancia minima desde montaña: " << x_min << ".\n";
		cout << "El maximo angulo(rad) de disparo es: " << tetha_max << ", con distancia maxima desde montaña: " << x_max << ".\n";
		
		if( x_min < 10 || x_max < 10 ){
			cout << "Se ordena detener el camion, colision inminente.\n";
		}
	} else {
		cout << "El tanque se encuentra en la zona minada de la montaña.\n";
	}
	
	return 0;
}
