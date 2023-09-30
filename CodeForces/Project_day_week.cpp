#include <iostream>
	
using namespace std;

int main() {
	// Declaramos las variables
	int dia, mes, anio;
	bool bisiesto = false;
	
	// Pedimos los datos al usuario
	cout << "Introduce el dia: ";
	cin >> dia;
	cout << "Introduce el mes: ";
	cin >> mes;
	cout << "Introduce el anio: ";
	cin >> anio;
	
	// Verificamos rangos para la de fecha.
	if(dia < 1 || dia > 31) { // Verificamos dia.
		cout << "Error en dia, rango permitido [1, 31]" << endl;
		return 1;
	} else if (mes < 1 || mes > 12){ // Verificamos mes.
		cout << "Error en mes, rango permitido [1, 12]" << endl;
		return 1;
	} else if (anio < 2021 || anio > 2050) { // Verificamos anio.
		cout << "Error en anio, rango permitido [2021, 2050]" << endl;
		return 1;
	}
	
	// Verificamos anio Bisiesto
	if(anio % 4 == 0) {// Divisible por 4
		if(anio % 100 == 0) { // Divisible por 100
			if(anio % 400 == 0) { // Divisible por 400
				bisiesto = true;
			}
		} else {
			bisiesto = true;
		}
	}
	
	// Verificamos que el dia este en rango correcto dependiente del mes/anio.
	if( mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
		// 1 = Enero tiene 31 dias, es el rango maximo.
		// 3 = Marzo tiene 31 dias, es el rango maximo.
		// 5 = Mayo tiene 31 dias, es el rango maximo.
		// 7 = Julio tiene 31 dias, es el rango maximo.
		// 8 = Agosto tiene 31 dias, es el rango maximo.
		// 10 = Octubre tiene 31 dias, es el rango maximo.
		// 12 = Diciembre tiene 31 dias, es el rango maximo.
	} else {
		switch(mes) {
			case 2: { // 2 = Febrero
				if(dia > 29) {
					cout << "Febrero solo tiene maximo 29 dias en anios bisiestos y 28 en anios no bisiestos." << endl;
					return 1;
				}else if(bisiesto && dia > 29){
					cout << "Error de fechas, el anio dado por input es bisiesto, por tanto febrero tiene maximo 29 dias." << endl;
					return 1;
				} else if(bisiesto == false && dia > 28) {
					cout << "Error de fechas, el anio dado por input NO es bisiesto, por tanto febrero tiene maximo 28 dias." << endl;
					return 1;
				}
				break;
			}
			case 4: { // 4 = Abril
				if(dia > 30) {cout << "Abril solo tiene maximo 30 dias." << endl; return 1;}
				break;
			}
			case 6: { // 6 = Junio
				if(dia > 30) {cout << "Junior solo tiene maximo 30 dias." << endl; return 1;}
				break;
			}
			case 9:{ // 9 = Septiembre
				if(dia > 30) {cout << "Septiembre solo tiene maximo 30 dias." << endl; return 1;}
				break;
			}
			case 11:{ // 11 = Noviembre
				if(dia > 30) {cout << "Noviembre solo tiene maximo 30 dias." << endl; return 1;}
				break;
			}
		}
	}
	
	/****** Calculamos el dia de la semana *****/
	
	int anio_inicial = 2021;
	int contador_dias = 0;
	// Cantidad de dias por meses.
	int dias_por_mes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	/* Contamos los dias */
	// Sumamos 365 dias si el anio NO es bisiesto, de lo contrario 366.
	for(int a = anio_inicial; a < anio; a++){
		bool bisiesto_actual = false;
		if(a % 4 == 0) {// Divisible por 4
			if(a % 100 == 0) { // Divisible por 100
				if(a % 400 == 0) { // Divisible por 400
					bisiesto_actual = true;
				}
			} else {
				bisiesto_actual = true;
			}
		}
		if(bisiesto_actual){
			contador_dias += 366;
		} else {
			contador_dias += 365;
		}
	}
	
	// Estando en la fecha actual dada
	// Los meses del anio actual(input)
	for(int m = 1; m < mes; m++){
		if( m == 2 && bisiesto){
			contador_dias += (dias_por_mes[m-1] + 1);
		} else {
			contador_dias += dias_por_mes[m-1];
		}
	}
	// Los dias restantes, se resta 1 dia porque el dia inicial es el 1 de enero de 2021.
	contador_dias += (dia-1);
	
	// Imprimimos el resultado
	cout << "El dia de la semana es: ";
	
	// Como dicho valor "contador_dias" esta condicionado al 01/01/2021 dia VIERNES debemos sumar 4 por la tabla:
	/*  0 = Lunes
		1 = Martes
		2 = Miercoles
		3 = Jueves
		4 = Viernes
		5 = Sabado
		6 = Domingo
	Para asi obtener el modulo 7 correcto.
	*/
	int d = (contador_dias + 4) % 7; // Sacamos modulo 7 de la cantidad de dias.

	switch(d) {
		case 0: cout << "Lunes" << endl; break;
		case 1: cout << "Martes" << endl; break;
		case 2: cout << "Miercoles" << endl; break;
		case 3: cout << "Jueves" << endl; break;
		case 4: cout << "Viernes" << endl; break;
		case 5: cout << "Sabado" << endl; break;
		case 6: cout << "Domingo" << endl; 
	}
	cout << "Cantidad de dias: " << contador_dias << endl;
	
	return 0;
}
