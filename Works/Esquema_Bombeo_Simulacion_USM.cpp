#include<iostream> // Mostrar datos en pantalla
#include<fstream> // Leer y escribir en un archivo de texto
#include<windows.h> // Control de ejecución (tiempo de refrescamiento de pantalla)

using namespace std;

int main() {
	string bomba="APAGADA";
	double presion=0;
	string pantalla="ON",texto_aux;
	int aux=1;

	// Leemos los datos del archivo de texto prueba a través de la función
	// Casabe (Puede ser cualquier nombre coloque Casabe porque me gusto la palabra)
	
	inicio:
	
	ifstream casabe("d:\\prueba.txt"); 
	
	string sw_bajo_nivel;
	string valvula;
	string modobomba; 

	casabe >> sw_bajo_nivel >> valvula >> modobomba;
	
	//Verifico que los datos sean escritos correctamente
	if( modobomba=="Remoto" or modobomba=="remoto" or modobomba=="REMOTO") {
		modobomba=="REMOTO";
	} else {
		modobomba=="LOCAL";
	}
	
	if(sw_bajo_nivel=="ON" or sw_bajo_nivel=="on" or sw_bajo_nivel=="On") sw_bajo_nivel="ON";
	
	if(sw_bajo_nivel=="OFF" or sw_bajo_nivel=="off" or sw_bajo_nivel=="Off") sw_bajo_nivel="OFF";
	
	if(sw_bajo_nivel != "ON" and sw_bajo_nivel!="On" and sw_bajo_nivel!="on" and sw_bajo_nivel!="OFF" and sw_bajo_nivel!="Off" and sw_bajo_nivel!="off") modobomba="LOCAL";	
	
	if(valvula=="ABIERTA" or valvula=="abierta" or valvula=="Abierta") valvula="ABIERTA";
	
	if(valvula=="CERRADA" or valvula=="cerrada" or valvula=="Cerrada") valvula="CERRADA";
	
	if(valvula!="ABIERTA" and valvula!="Abierta" and valvula!="abierta" and valvula!="CERRADA" and valvula!="Cerrada" and valvula!="cerrada") modobomba="LOCAL";	
	
	//CHEQUEO EL MODO DE OPERACIÓN DE LA BOMBA
	
	if (modobomba=="REMOTO") {
		aux=0;
		pantalla="ON";
	}	
	
	if (modobomba=="LOCAL") {
		aux=1;
		pantalla="ON";
	}
	
	// HACEMOS TODOS LOS CÁLCULOS PARA EL MODO REMOTO AUTOMÁTICO
	
	if (aux==0) {
		// imprimimos los valores en pantalla para el modo Remoto
		
		if(pantalla=="ON") {
			system("cls");
			cout << "La Presion= "<< presion;
			cout << " - Tu bomba esta= "<< bomba; 
			 =
			if(sw_bajo_nivel=="OFF") {
				texto_aux="ALARMA";	
			} else {
				texto_aux="NORMAL";	
			}
			cout <<" - El Switch de nivel= "<<texto_aux;
			cout <<" - La valvula esta= "<<valvula<<endl<<endl;  
			cout <<"                               **** MODO AUTOMATICO REMOTO *****";
			pantalla ="OFF"; 
		}
		
		//  Establecemos un tiempo de 1/2 de segundo para ver los cambios en la presión
		
		Sleep (500);
		
		// Simulamos la Presión    
		
		if (valvula=="CERRADA" and bomba=="ENCENDIDA") {
			presion=presion+3;
			pantalla ="ON";
		}
		
		if (valvula=="ABIERTA" and bomba=="APAGADA") {
			presion=presion-3;
			pantalla ="ON";
		}
		
		if (valvula=="ABIERTA" and bomba=="ENCENDIDA" and presion<32) {
			presion=presion+1;
			pantalla ="ON";
		}
		
		if (valvula=="ABIERTA" and bomba=="ENCENDIDA" and presion>32) {
			presion=presion-1;
			pantalla ="ON";
		}
		
		//impedimos que la presión de negativo
		
		if (presion<0){
			presion=0;
			pantalla ="ON";
		}
		
		// Controlamos el encendido y apagado de la bomba
		
		if (sw_bajo_nivel=="OFF" and bomba=="ENCENDIDA") {
			bomba="APAGADA";
			pantalla ="ON";
		} 
		
		if (sw_bajo_nivel=="ON" and presion<20 and bomba=="APAGADA") {
			bomba="ENCENDIDA";
			pantalla ="ON";
		}  
		
		if (sw_bajo_nivel=="ON" and presion>40 and bomba=="ENCENDIDA") {
			bomba="APAGADA";
			pantalla ="ON";
		} 
	}
	
	// PRESENTAMOS LOS DATOS DEL MODO LOCAL
	// imprimimos los valores en pantalla para el modo Local
	if (aux==1 && pantalla=="ON") {
		system("cls");
		cout <<" **** MODO LOCAL - EL PROGRAMA NO CONTROLA LA BOMBA "; 
		cout <<"o LOS DATOS ESCRITOS EN EL ARCHIVO .TXT ESTAN INCORRECTOS *****";
		pantalla ="OFF"; 	 
	}
	
	goto inicio;

}
