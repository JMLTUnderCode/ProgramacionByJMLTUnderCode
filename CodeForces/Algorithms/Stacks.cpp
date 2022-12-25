#include<iostream>
#include<string>
#include<vector>
#include<cmath>

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

// Classes

class Stack {
    // Variables de la Clase
    vector<int> arrayElements;
    int lastPointer;

public:
    // Constructor
    Stack(int n) {
        arrayElements = vector<int>(n);
        lastPointer = -1;
    }

    // Funciones de la clase
    int top();
    void push(int value);
    void pop();
    bool aEmpty();

};

// Funtions

int Stack :: top() {
    if ( lastPointer == -1 ) {
        cerr << "Array is empty." << endl;
        exit(1);
    } else {
        return arrayElements[lastPointer];
    }
}

void Stack :: push(int value) {

    if ( lastPointer == arrayElements.size() - 1 ) {

        vector<int> newArrayElements( 2 * arrayElements.size());
        for ( int k = 0; k < arrayElements.size(); k++ ) {
            newArrayElements[k] = arrayElements[k];
        }

        cout << " Expensive call with: " << value << endl;
        cout << " OldArray size = " << arrayElements.size() << ", NewArray size = " << newArrayElements.size() << "\n" << endl;

        arrayElements = newArrayElements;
    }

    arrayElements[lastPointer+1] = value;
    lastPointer++;
}

void Stack :: pop() {
    if ( lastPointer == -1 ) {
        cout << "Array is empty." << endl;
        exit(1);
    } else {
        lastPointer--;
    }
}

bool Stack :: aEmpty() {
    return lastPointer == -1;
}

// Main Funtion
int main () {

    int n; cin >> n;
    Stack S(n);

    // Agregamos elementos a la pila.
    for (int i = 1; i < n; i++){
        S.push(i);
    }

    // Eliminamos elementos de la pila y los imprimimos por pantalla.
    while ( !S.aEmpty() ) {
        int x = S.top();
        S.pop();
        cout << x << endl;
    }

    return 0;
}
