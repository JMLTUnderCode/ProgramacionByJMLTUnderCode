/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode

	Idea principal para el programa:
	
	Hacer uso de la biblioteca stack propia para almacenar los caracteres
	del string uno a uno, como tambien un stack auxiliar que ira almacenando
	los caracteres de categoria "CERRADO" conforme se vayan leyendo del stack 
	principal, en caso de que al tomar un elemento de la stack principal
	este sea de categoria "ABIERTO" entonces checamos que hayan caracteres 
	disponibles en el stack auxiliar de tipo cerrado, en caso de que el top
	del stack auxiliar sea del mismo tipo (Parentesis, corchete, llaves, ...)
	este no sumara a la variables "replaces" nada, en caso contrario si porque
	da a entender que es de un tipo distinto.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

/*
    Implementacion de una Pila/Stacks:
    - Operaciones:
        top() -> Ver el elemento tope.
        push(x) -> Agregar x en el tope de la pila.
        pop() -> Eliminar el elemento en el tope de la pila.
    - Funciones adicionales:
        aEmpty() -> Determina si esta vacio o no la pila.
*/

// Clase Stack

class Stack {
    // Variables de la Clase
    vector<char> arrayElements;
    int lastPointer;

public:
    // Constructor
    Stack(int n) {
        arrayElements = vector<char>(n);
        lastPointer = -1;
    }

    // Funciones de la clase
    int top();
    void push(char value);
    void pop();
    bool aEmpty();

};

// Implementacion de las funciones de la clase

int Stack :: top() {
    if ( lastPointer == -1 ) {
        //cerr << "Array is empty." << endl;
        //exit(0);
    } else {
        return arrayElements[lastPointer];
    }
}

void Stack :: push(char value) {

    if ( lastPointer == arrayElements.size() - 1 ) {

        vector<char> newArrayElements( 2 * arrayElements.size());
        for ( int k = 0; k < arrayElements.size(); k++ ) {
            newArrayElements[k] = arrayElements[k];
        }
        
        arrayElements = newArrayElements;
    }

    arrayElements[lastPointer+1] = value;
    lastPointer++;
}

void Stack :: pop() {
    if ( lastPointer == -1 ) {
        //cout << "Array is empty." << endl;
        //exit(0);
    } else {
        lastPointer--;
    }
}

bool Stack :: aEmpty() {
    return lastPointer == -1;
}

// Funcionces
bool checkTypeChar(char c, char RBS[]) {
	
	for( int i = 0; i < 4; i++ ) {
		if ( RBS[i] == c ) {
			return true;
		}
	}
	return false;
}

int main() {
	
	// Inicializacion de variables
	char openRBS[] = {'<','{','[','('};
	char closeRBS[] = {'>','}',']',')'};
	string s;
	int openChars = 0, closeChars = 0;
	
	// Precondicion: Cadena de carecteres con solo combinaciones de <>, {}, [], ().
	// 				 y con una longitud de cadena no maxima a 10^6.
	/*
	try {
		cin >> s;
		for ( int i=0; i < s.size(); i++ ) {
			if ( (!checkTypeChar(s[i], closeRBS) && !checkTypeChar(s[i], openRBS)) || s.size() >= pow(10,6) ) 
				throw "\n Precondition Error: Character chain of <>, {}, [], ()";
				
			if ( checkTypeChar(s[i], closeRBS) ) {
				closeChars++;
			} else {
				openChars++;
			}
		}	

	} catch (const char* err) {
		cout << err << endl;
		exit(0);
	}
	*/
	
	// *** Programa ***
	
	/*  En caso de obtener una cantidad igualada de caracteres tanto de apertura
		como de clausura entonces procedemos. De lo contrario sera imposible
		conseguir un string RBS y agregamos los caracteres a la pila.
	*/
	
	cin >> s;
	Stack v(s.size());
	for ( int i=0; i < s.size(); i++ ) {
		if ( checkTypeChar(s[i], closeRBS) ) {
			closeChars++;
		} else {
			openChars++;
		}
		v.push(s[i]);
	}
	
	if ( openChars == closeChars ) {
		
		// Inicializacion de variables
		int open = 0, close = 0;
		int replaces = 0;
		Stack vAux(s.size());
		
	    	
		// Comprobamos que el primer(top) elemento de la pila sea un corchete de
		// tipo cerrado. Esto hace referencia al ultimo caracter del string.
		if ( !checkTypeChar(v.top(), closeRBS) ) {
			cout << "Impossible";
			exit(0);
		}
		
		while ( !v.aEmpty() ) {

			// Comprobamos que el ultimo elemento de la pila sea un corchete de
			// tipo abierto.

			// Agregamos a la pila auxiliar todo caracter que sea de tipo cerrado.
			if ( checkTypeChar(v.top(), closeRBS ) ) {
				close++;
				vAux.push(v.top());
				
			/*  En caso contrario, sera un caracter de tipo abierto por lo que 
				comparamos los los top de cada pila y determinamos si necesita
				un reemplazo o no.
			*/		
			} else { 
				open++;
				if ( !vAux.aEmpty() &&
					((v.top() == '<' && vAux.top() != '>') || 
					(v.top() == '{' && vAux.top() != '}') ||
					(v.top() == '[' && vAux.top() != ']') ||
					(v.top() == '(' && vAux.top() != ')') ) )
				{
					replaces++;	
				} 
				
				// Eliminamos elementos de la pila auxiliar siempre y cuando tenga.
				if ( !vAux.aEmpty() ) {
					vAux.pop();
				}
				
			}
			
			/* Conforme vamos quitando elementos de la pila principal comprobamos
				que la cantidad de caracteres abiertos y cerrados llevados hasta
				el momento se cumpla que ABIERTOS <= CERRADOS, de lo contrario
				tendremos caracteres de tipo abierto que nunca podran cerrarse.
			*/
			if (open > close) {
				cout << "Impossible";
				exit(0);
			}
			
			v.pop();
		}
		
		cout << replaces;
		
	} else {
		cout << "Impossible";
	}
	
	return 0;
}
