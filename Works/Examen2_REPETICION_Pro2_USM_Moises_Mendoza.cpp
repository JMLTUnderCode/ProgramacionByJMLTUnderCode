#include <iostream>
#include <stdlib.h>
#include <unistd.h> 
#include <cmath>

using namespace std;

int main(){
	int iter1 = 0, iter2 = 0;
	while(iter1 < 3){
		iter2 = 0;
		while(iter2 < 4){
			system("cls");
			cout << "**************************************************************\n";
			cout << "****************** System Report - USM Navy ******************\n";
			cout << "**************************************************************\n";
			switch (iter2){
				case 0:
					cout << "  Calculando";
					break;
				case 1:
					cout << "  Calculando.";
					break;
				case 2:
					cout << "  Calculando..";
					break;
				case 3:
					cout << "  Calculando...";
					break;
				default:
					break;
			}
			usleep(100000);
			iter2++;
		}
		iter1++;
	}

	system("cls");
	cout << "**************************************************************\n";
	cout << "****************** System Report - USM Navy ******************\n";
	cout << "**************************************************************\n";
	
	// Constantes del problema.
	float pi = 3.141592653589793;
	float g = -9.81;
	float nudo = 0.514444;
	
	// Datos del navio USM Navy.
	float velocidad_inicial_arma_navy = 390;
	float angulo_arma_navy = 45*pi/180; // En radianes.
	float velocidad_inicial_y_arma_navy = velocidad_inicial_arma_navy*sin(angulo_arma_navy);
	float velocidad_inicial_x_arma_navy = velocidad_inicial_arma_navy*cos(angulo_arma_navy);
	
	// Datos del enemigo.
	float velocidad_inicial_arma_enemiga = 400;
	float angulo_arma_enemiga = 45*pi/180; // En readianes.
	float velocidad_inicial_y_arma_enemiga = velocidad_inicial_arma_enemiga*sin(angulo_arma_enemiga);
	float velocidad_inicial_x_arma_enemiga = velocidad_inicial_arma_enemiga*cos(angulo_arma_enemiga);
	float altura_arma_enemiga = 100;
	
	// Variables a usar en todo el problema.
	float velocidad_viento;
	float velocidad_viento_recomendada;
	float velocidad_inicial_maxima;
	float tiempo_subida, tiempo_vuelo, tiempo_transcurrido;
	float alcance_arma_navy, alcance_arma_enemiga, alcance_maximo_arma_enemiga;
	float distancia_segura;
	float altura_impacto;
	float velocidad_x_aux, altura_impacto_aux;
	
	// Solicitamos datos del viento, transformamos en caso de ser correcto el dato y calculamos alcances e impacto.
	
	cout << "  Indique la velocidad del viento(nudos): "; cin >> velocidad_viento;
	
	if(velocidad_viento >= 0 and velocidad_viento <= 115){
		velocidad_viento *= nudo; // Transformamos la velocidad del viento a m/sg.
		
		// **** Determinamos las velocidades definitivas de los misiles en el eje horizontal. ****
		// Para arma navy.
		velocidad_inicial_x_arma_navy += velocidad_viento/4;
		
		// Para arma enemiga.
		velocidad_inicial_x_arma_enemiga -= velocidad_viento/4;
		
		// **** Calculamos alcance del arma enemiga. ***
		tiempo_transcurrido = (-velocidad_inicial_y_arma_enemiga - sqrt(pow(velocidad_inicial_y_arma_enemiga, 2) - 200*g))/g;
		alcance_arma_enemiga = tiempo_transcurrido*velocidad_inicial_x_arma_enemiga;
		
		// **** Calculamos alcance del arma del navio. ***
		tiempo_subida = (0 - velocidad_inicial_y_arma_navy)/g;
		tiempo_vuelo = 2*tiempo_subida;
		alcance_arma_navy = tiempo_vuelo*velocidad_inicial_x_arma_navy;
		
		// **** Calculamos la velocidad inicial maxima. ****
		velocidad_inicial_maxima = sqrt(pow(velocidad_inicial_x_arma_navy, 2) + pow(velocidad_inicial_y_arma_navy, 2));
		
		cout << "\n  >>> DETECTANDO <<<\n";
		cout << "\n   - El alcance del arma enemiga es: " << alcance_arma_enemiga << " mts.\n";
		cout << "\n   - El alcance del arma navy es:    " << alcance_arma_navy << " mts.\n";
		cout << "\n   - La velocidad inicial maxima del proyectil: " << velocidad_inicial_maxima << " mts.\n";
		
		// **** Determinamos la distancia segura. ****
		distancia_segura = alcance_arma_enemiga + 200;
		
		// **** Determinamos altura de impacto y velocidad maxima inicial ****
		tiempo_transcurrido = distancia_segura/velocidad_inicial_x_arma_navy;
		altura_impacto = velocidad_inicial_y_arma_navy*tiempo_transcurrido + (g/2)*pow(tiempo_transcurrido, 2);
		
		// **** Realizamos la comprobacion de impacto sobre la torre enemiga. ****
		// En caso de la altura sea menor a cero, eso pasa cuando el proyectil impacta en el mar.
		if(altura_impacto < 0) {
			cout << "\n   ¡FALLO DE COLISION!\n   El proyectil impacto en el mar.\n";
			cout << "    Se recomienda que espere un aumento de la velocidad del viento.\n";
			
			// Buscamos para que velocidad del viento podemos impactar,  esto es aumentando la velocidad actual.
			for(float vv = velocidad_viento/nudo; vv <= 115; vv += 0.01){
				velocidad_x_aux = velocidad_inicial_x_arma_navy - velocidad_viento/4 + vv*nudo/4;
				tiempo_transcurrido = distancia_segura/velocidad_x_aux;
				altura_impacto_aux = velocidad_inicial_y_arma_navy*tiempo_transcurrido + (g/2)*pow(tiempo_transcurrido, 2);

				// Cuando consigamos una altura mayor o igual a 0, significa entonces que dejamos
				// impactar en el mar.
				if(altura_impacto_aux >= 0){
					cout << "   Velocidad recomendada a partir de: " << vv << " nudos.\n";
					break;
				}
			}
			
		// En caso de tener una altura mayor a 100 metros, eso pasa cuando el proyectil sobrepasa la estructura enemiga.
		} else if (altura_impacto > 100){
			cout << "\n   ¡FALLO DE COLISION!\n   El proyectil sobrepaso la estructura enemiga.\n";
			cout << "    Se recomienda que espere una reduccion de la velocidad del viento.\n";
			
			// Buscamos para que velocidad del viento podemos impactar, esto es reduciendo la velocidad actual.
			for(float vv = velocidad_viento/nudo; vv >= 0; vv -= 0.01){
				velocidad_x_aux = velocidad_inicial_x_arma_navy - velocidad_viento/4 + vv*nudo/4;
				tiempo_transcurrido = distancia_segura/velocidad_x_aux;
				altura_impacto_aux = velocidad_inicial_y_arma_navy*tiempo_transcurrido + (g/2)*pow(tiempo_transcurrido, 2);
				
				// Cuando sonsigamos una altura menor a o igual a 100 , significa entonces que dejamos
				// de sobrepasar la estructura enemiga.
				if(altura_impacto_aux <= 100){
					cout << "   Velocidad recomendada a partir de: " << vv << " nudos.\n";
					break;
				}
			}
			
		// Si no es menor a 0 o mayor a 100, entonces hemos impactado con la estructura enemiga.
		} else {
			cout << "\n  ¡COLISION DETECTADA!\n";
			cout << "    - Altura de impacto: " << altura_impacto << " mts.\n";
		}
		
	} else {
		cout << "\n WARNING: \n   La velocidad del viendo(nudos) es incorrecta.\n   Solo valores en intervalo [0, 115].\n";
	}
	cout << "\n**************************************************************\n";
	
	return 0;
}
