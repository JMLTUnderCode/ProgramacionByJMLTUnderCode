/*
	República Bolivariana de Venezuela
	Ministerio de el Poder Popular para la Educación
	Universidad Santa María

	Título

	Profesor.          Estudiante

	Caracas, fecha y año
	
	- Decisiones de implementacion.
	
	1)  El tiempo se maneja tal que 10 sg descritos equivalen a 1 sg dentro del programa.
		Es decir, si se describe 30 sg como tiempo de rotacion esto se SIMULA a 3 sg dentro del
		programa. Si se describe 45 sg entonces pasa a ser simulado como 4.5 sg, sin embargo las bombas
		trabajaran 5 sg y luego haran el switch respectivo de cumplir las condiciones necesarias.
		
	2)  Se hace dentro del programa un congelamiento de pantalla cada 1 sg que equivalen a 10 sg "reales",
	    y de esta forma en la informacion mostrada por consola lleva un tiempo total del funcionamiento
	    general del sistema, esto quiere decir que si una linea de transmision de etileno inicia con
	    las condiciones completas para transmitir etileno al objetivo, notara que por cada 1 minuto activo
		se habran transmitido 40 Gal de etileno, pero debe recordar que ese 1 minuto realmente se simulo como
		60 sg / 10 = 6 sg.

	3)  Se toma como referencia a las valvulas V101, V102 y V103 como las de tipo "Succion" y las valvulas
		V201, V202 y V203 como las de tipo "Descarga".
		
	4)  Se asume que maximo pueden estar trabajando 2 bombas a la vez. Esto quiere decir que no existe el caso
		en que 3 bombas estan trabajando. Ya luego si existe la opcion de encender 3 bombas, entonces se prenden
		2 para luego realizar la rotacion de trabajo. Pero siempre estaran prendidas 2 de poder encender 2.
		
	5)	Las condiciones de encendido es que una vez llegado a los 50 psi se apaga la bomba por seguridad, luego
		se debe esperar a que la presion llegue a 20 psi para poder encenderse, siempre y cuando el switch de 
		floju indique que hay etileno.
*/

#include <iostream> 	// Mostrar datos en pantalla
#include <fstream> 		// leer y escribir en un archivo de texto
#include <windows.h> 	// Control de ejecución (tiempo de refrescamiento de pantalla)
#include <string>
#include <cctype>

using namespace std;

// Funcion para pasar a mayusculas una cadena de caracteres.
string to_uppercase(string str) {
	for (int i = 0; i < str.size(); i++) str[i] = toupper(str[i]);
	return str;
}

int main(){
	// Inicializacion de variables.
	
	// Para simular el encendido y apagado de las bombas.
	string bomba_P101 = "APAGADA";
	string bomba_P102 = "APAGADA";
	string bomba_P103 = "APAGADA";
	
	// Para simular el estado de alarma o normalidad de un switch.
	string switch_FS201 = "ALARMA";
	string switch_FS202 = "ALARMA";
	string switch_FS203 = "ALARMA";
	
	// Para simular las valvulas de succion de etileno.
	string valvula_101;
	string valvula_102;
	string valvula_103;
	
	// Para simular las valvulas de descargar del etileno.
	string valvula_201;
	string valvula_202;
	string valvula_203;
	
	// Para simular la presion en cada linea.
	float presion_PT201 = 0.0;
	float presion_PT202 = 0.0;
	float presion_PT203 = 0.0;
	
	// Para simular el tiempo total del sistema y la de retacion de bombas.
	float tiempo_rotacion = 30.0;
	float tiempo_total = 0.0;
	
	// Bombeo maximo de cada bomba.
	float bombeo_maximo = 40.0;

	// Para simular la cantidad total de etileno y circulacion actual del mismo.
	float total_etileno_plastilagos = 0.0;
	float etileno_circulando = 0.0;
	
	// Para simular las bombas encendidas actualmente y las que se pueden encender.
	float bombas_encendidas = 0.0;
	float cuantas_bombas_pueden_encender = 0.0;
	
	// Para simular el tiempo que se ha mantenido funcionando cada bomba.
	float tiempo_bomba_P101 = 0.0;
	float tiempo_bomba_P102 = 0.0;
	float tiempo_bomba_P103 = 0.0;
	
	// Condicion de encendido de bomba para presion maxima.
	bool no_falla_bomba_P101 = true;
	bool no_falla_bomba_P102 = true;
	bool no_falla_bomba_P103 = true;
	
	inicio:
	
	// Lectura de valvulas del archivo "prueba.txt" que debe estar en el mismo directorio que este programa.
	ifstream lectura("prueba.txt");
	lectura >> valvula_101 >> valvula_102 >> valvula_103 >> valvula_201 >> valvula_202 >> valvula_203 >> tiempo_rotacion;
	
	// Control de STRINGS, se pasan a mayusculas cada valvula para evitar problemas.
	valvula_101 = to_uppercase(valvula_101);
	valvula_102 = to_uppercase(valvula_102);
	valvula_103 = to_uppercase(valvula_103);
	valvula_201 = to_uppercase(valvula_201);
	valvula_202 = to_uppercase(valvula_202);
	valvula_203 = to_uppercase(valvula_203);
	
	// Mostramos el estado del sistema para las 3 lineas.
	system("cls");
	cout <<"*******************************************************\n";
	cout <<"**************** PLASTILAGOS - CONTROL ****************\n";
	cout <<"**                                                   **\n";
	cout <<"**  Tiempo Total:       " << tiempo_total*10/60 << " mins\n";
	cout <<"**  Total Etileno:      " << total_etileno_plastilagos << " Gal\n";
	cout <<"**  Etileno circulando: " << etileno_circulando << " Gal\n";
	cout <<"**\n";
	cout <<"**    Estados Linea 1\n";
	cout <<"**      Bomba P101:     " << bomba_P101 << endl;
	cout <<"**      Valvula V101:   " << valvula_101 << endl;
	cout <<"**      switch FS201:   " << switch_FS201 << endl;
	cout <<"**      Valvula V201:   " << valvula_201 << endl;
	cout <<"**      Presion PT201:  " << presion_PT201 << endl;
	cout <<"**\n";
	cout <<"**    Estados Linea 2\n";	
	cout <<"**      Bomba P102:     " << bomba_P102 << endl; 
	cout <<"**      Valvula V102:   " << valvula_102 << endl;
	cout <<"**      switch FS202:   " << switch_FS202 << endl;
	cout <<"**      Valvula V202:   " << valvula_202 << endl;
	cout <<"**      Presion PT202:  " << presion_PT202 << endl;
	cout <<"**\n";
	cout <<"**    Estados Linea 3\n";	
	cout <<"**      Bomba P103:     " << bomba_P103 << endl; 
	cout <<"**      Valvula V103:   " << valvula_103 << endl;
	cout <<"**      switch FS203:   " << switch_FS203 << endl;
	cout <<"**      Valvula V203:   " << valvula_203 << endl;
	cout <<"**      Presion PT203:  " << presion_PT203 << endl;
	cout <<"**\n";
	cout <<"**      T. Rotacion:    " << tiempo_rotacion << " sgs\n";
	cout <<"**\n";
	cout <<"**                                                   **\n";
	cout <<"*******************************************************\n";	
		
	// Control de cambio de trabajo en bombas.
	// Bomba 1
	if (tiempo_bomba_P101 >= tiempo_rotacion/10.0 && bombas_encendidas < 3 && cuantas_bombas_pueden_encender > 0){
		// Verificamos si la bomba 2 esta disponible.
		if (switch_FS202 == "NORMAL" && bomba_P102 == "APAGADA" && no_falla_bomba_P102){
			bomba_P101 = "APAGADA";
			bomba_P102 = "ENCENDIDA";
			tiempo_bomba_P101 = 0;
			tiempo_bomba_P102 = 0;
			
		// Sino, verificamos si la bomba 3 esta disponible.
		} else if (switch_FS203 == "NORMAL" && bomba_P103 == "APAGADA" && no_falla_bomba_P103){
			bomba_P101 = "APAGADA";
			bomba_P103 = "ENCENDIDA";
			tiempo_bomba_P101 = 0;
			tiempo_bomba_P103 = 0;
		}
	// Bomba 2
	} else if (tiempo_bomba_P102 >= tiempo_rotacion/10.0 && bombas_encendidas < 3 && cuantas_bombas_pueden_encender > 0){
		// Verficamos si la bomba 1 esta disponible.
		if (switch_FS201 == "NORMAL" && bomba_P101 == "APAGADA" && no_falla_bomba_P101){
			bomba_P102 = "APAGADA";
			bomba_P101 = "ENCENDIDA";
			tiempo_bomba_P102 = 0;
			tiempo_bomba_P101 = 0;
			
		// Sino verificamos si la bomba 3 esta disponible.
		} else if (switch_FS203 == "NORMAL" && bomba_P103 == "APAGADA" && no_falla_bomba_P103){
			bomba_P102 = "APAGADA";
			bomba_P103 = "ENCENDIDA";
			tiempo_bomba_P102 = 0;
			tiempo_bomba_P103 = 0;
		}
	// Bomba 3
	} else if (tiempo_bomba_P103 >= tiempo_rotacion/10.0 && bombas_encendidas < 3 && cuantas_bombas_pueden_encender > 0){
		// Verificamos si la bomba 1 esta disponible.
		if (switch_FS201 == "NORMAL" && bomba_P101 == "APAGADA" && no_falla_bomba_P101){
			bomba_P103 = "APAGADA";
			bomba_P101 = "ENCENDIDA";
			tiempo_bomba_P103 = 0;
			tiempo_bomba_P101 = 0;
			
		// Sino, verificamos si la bomba 2 esta disponible.
		} else if (switch_FS202 == "NORMAL" && bomba_P102 == "APAGADA" && no_falla_bomba_P102){
			bomba_P103 = "APAGADA";
			bomba_P102 = "ENCENDIDA";
			tiempo_bomba_P103 = 0;
			tiempo_bomba_P102 = 0;
		}
	}	
	
	
	// Control del Switch de flujo segun la valvula de succion.
	// Para Switch 1 contamos si la bomba se puede encender o en su defecto se debe apagar.
	if (switch_FS201 == "ALARMA" && valvula_101 == "ABIERTA"){
		cuantas_bombas_pueden_encender++;
		switch_FS201 = "NORMAL";
	} else if (switch_FS201 == "NORMAL" && valvula_101 == "CERRADA") {
		cuantas_bombas_pueden_encender--;
		switch_FS201 = "ALARMA";	
	}
	// Para Switch 2 contamos si la bomba se puede encender o en su defecto se debe apagar.
	if (switch_FS202 == "ALARMA" && valvula_102 == "ABIERTA"){
		cuantas_bombas_pueden_encender++;
		switch_FS202 = "NORMAL";
	} else if (switch_FS202 == "NORMAL" && valvula_102 == "CERRADA") {
		cuantas_bombas_pueden_encender--;
		switch_FS202 = "ALARMA";	
	}
	// Para Switch 3 contamos si la bomba se puede encender o en su defecto se debe apagar.
	if (switch_FS203 == "ALARMA" && valvula_103 == "ABIERTA"){
		cuantas_bombas_pueden_encender++;
		switch_FS203 = "NORMAL";
	} else if (switch_FS203 == "NORMAL" && valvula_103 == "CERRADA") {
		cuantas_bombas_pueden_encender--;
		switch_FS203 = "ALARMA";	
	}
	
	
	// Control de la bomba segun el switch de flujo.
	// Encendemos Bomba 1 si cumple las condiciones de encendido, o en su defecto apagarga.
	if (bomba_P101 == "APAGADA" && switch_FS201 == "NORMAL" && bombas_encendidas < 2 && no_falla_bomba_P101) {
		bombas_encendidas++;
		cuantas_bombas_pueden_encender--;
		tiempo_bomba_P101 = 0;
		bomba_P101 = "ENCENDIDA";
	} else if (bomba_P101 == "ENCENDIDA" && switch_FS201 == "ALARMA"){
		bombas_encendidas--;
		cuantas_bombas_pueden_encender++;
		tiempo_bomba_P101 = 0;
		bomba_P101 = "APAGADA";
	}
	// Encendemos Bomba 2 si cumple las condiciones de encendido, o en su defecto apagarga.
	if (bomba_P102 == "APAGADA" && switch_FS202 == "NORMAL" && bombas_encendidas < 2 && no_falla_bomba_P102) {
		bombas_encendidas++;
		cuantas_bombas_pueden_encender--;
		tiempo_bomba_P102 = 0;
		bomba_P102 = "ENCENDIDA";
		cout << "check\n";
	} else if (bomba_P102 == "ENCENDIDA" && switch_FS202 == "ALARMA"){
		bombas_encendidas--;
		cuantas_bombas_pueden_encender++;
		tiempo_bomba_P102 = 0;
		bomba_P102 = "APAGADA";
	}
	// Encendemos Bomba 3 si cumple las condiciones de encendido, o en su defecto apagarga.
	if (bomba_P103 == "APAGADA" && switch_FS203 == "NORMAL" && bombas_encendidas < 2 && no_falla_bomba_P103) {
		bombas_encendidas++;
		cuantas_bombas_pueden_encender--;
		tiempo_bomba_P103 = 0;
		bomba_P103 = "ENCENDIDA";
	} else if (bomba_P103 == "ENCENDIDA" && switch_FS203 == "ALARMA"){
		bombas_encendidas--;
		cuantas_bombas_pueden_encender++;
		bomba_P103 = "APAGADA";
		tiempo_bomba_P103 = 0;
	}
	
	
	// Control de presion segun la bomba y valvula de descarga
	// Verificamos si la valvula de descarga esta abierta o cerrada para 
	// disminuir o aumentar la presion respectivamente.
	// Para bomba 1
	if (bomba_P101 == "APAGADA" && valvula_201 == "ABIERTA") presion_PT201 -= 2.0;
	if (bomba_P101 == "ENCENDIDA" && valvula_201 == "CERRADA") presion_PT201 += 2.0;
	
	// Para bomba 2
	if (bomba_P102 == "APAGADA" && valvula_202 == "ABIERTA") presion_PT202 -= 2.0;
	if (bomba_P102 == "ENCENDIDA" && valvula_202 == "CERRADA") presion_PT202 += 2.0;
	
	// Para bomba 3
	if (bomba_P103 == "APAGADA" && valvula_203 == "ABIERTA") presion_PT203 -= 2.0;
	if (bomba_P103 == "ENCENDIDA" && valvula_203 == "CERRADA") presion_PT203 += 2.0;
	
	
	// Correccion de presiones.
	if (presion_PT201 > 50) presion_PT201 = 50.0;
	if (presion_PT201 < 0 ) presion_PT201 = 0.0;
	
	if (presion_PT202 > 50) presion_PT202 = 50.0;
	if (presion_PT202 < 0 ) presion_PT202 = 0.0;
	
	if (presion_PT203 > 50) presion_PT203 = 50.0;
	if (presion_PT203 < 0 ) presion_PT203 = 0.0;
	
	
	// Control de la bomba segun la presion.
	// Se debe verificar el estado actual de la presion para asi realizar el encendido de la misma.
	// Para bomba 1
	if (bomba_P101 == "APAGADA" && switch_FS201 == "NORMAL" && presion_PT201 < 20 && bombas_encendidas < 2 && cuantas_bombas_pueden_encender > 0){
		no_falla_bomba_P101 = true;
		bombas_encendidas++;
		cuantas_bombas_pueden_encender--;
		tiempo_bomba_P101 = 0;
		bomba_P101 = "ENCENDIDA";
	} else if (bomba_P101 == "ENCENDIDA" && presion_PT201 >= 50) {
		no_falla_bomba_P101 = false;
		bombas_encendidas--;
		cuantas_bombas_pueden_encender++;
		tiempo_bomba_P101 = 0;
		bomba_P101 = "APAGADA";
	}
	// Para bomba 2
	if (bomba_P102 == "APAGADA" && switch_FS202 == "NORMAL" && presion_PT202 < 20 && bombas_encendidas < 2 && cuantas_bombas_pueden_encender > 0){
		no_falla_bomba_P102 = true;
		bombas_encendidas++;
		cuantas_bombas_pueden_encender--;
		tiempo_bomba_P102 = 0;
		bomba_P102 = "ENCENDIDA";
	} else if (bomba_P102 == "ENCENDIDA" && presion_PT202 >= 50) {
		no_falla_bomba_P102 = false;
		bombas_encendidas--;
		cuantas_bombas_pueden_encender++;
		tiempo_bomba_P102 = 0;
		bomba_P102 = "APAGADA";
	}
	// Para bomba 3
	if (bomba_P103 == "APAGADA" && switch_FS203 == "NORMAL" && presion_PT203 < 20 && bombas_encendidas < 2 && cuantas_bombas_pueden_encender > 0){
		no_falla_bomba_P103 = true;
		bombas_encendidas++;
		cuantas_bombas_pueden_encender--;
		tiempo_bomba_P103 = 0;
		bomba_P103 = "ENCENDIDA";
	} else if (bomba_P103 == "ENCENDIDA" && presion_PT203 >= 50) {
		no_falla_bomba_P103 = false;
		bombas_encendidas--;
		cuantas_bombas_pueden_encender++;
		tiempo_bomba_P103 = 0;
		bomba_P103 = "APAGADA";
	}
	
	
	// Revision adicional si una bomba deja de estar en modo fallo.
	if (!no_falla_bomba_P101 && presion_PT201 < 20) no_falla_bomba_P101 = true;
	if (!no_falla_bomba_P102 && presion_PT202 < 20) no_falla_bomba_P102 = true;
	if (!no_falla_bomba_P103 && presion_PT203 < 20) no_falla_bomba_P103 = true;
	
	// Control de Etileno y estabilizacion de presion.
	etileno_circulando = 0;
	if (bomba_P101 == "ENCENDIDA" && valvula_201 == "ABIERTA"){
		etileno_circulando += bombeo_maximo/6.0;
		presion_PT201 > 32 ? presion_PT201 -= 2.0 : presion_PT201 += 2.0;
	}
	
	if (bomba_P102 == "ENCENDIDA" && valvula_202 == "ABIERTA"){
		etileno_circulando += bombeo_maximo/6.0;
		presion_PT202 > 32 ? presion_PT202 -= 2.0 : presion_PT202 += 2.0;
	}
	
	if (bomba_P103 == "ENCENDIDA" && valvula_203 == "ABIERTA"){
		etileno_circulando += bombeo_maximo/6.0;
		presion_PT203 > 32 ? presion_PT203 -= 2.0 : presion_PT203 += 2.0;
	}
	
	// Sumamos la circulacion actual al total de etileno transmitido a Plastilagos.
	total_etileno_plastilagos += etileno_circulando;
	
	// Control de tiempos de encendido de cada bomba.
	if (bomba_P101 == "ENCENDIDA") tiempo_bomba_P101++;
	if (bomba_P102 == "ENCENDIDA") tiempo_bomba_P102++;
	if (bomba_P103 == "ENCENDIDA") tiempo_bomba_P103++;
	
	// Control del tiempo total del sistema en funcionamiento general.
	tiempo_total++;
	
	//  Establecemos un tiempo de 1 de segundo para ver los cambios de la pantalla
    Sleep (1000);
	
	goto inicio;
}
