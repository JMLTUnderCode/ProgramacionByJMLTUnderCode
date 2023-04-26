#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

/*
    Implementacion de una Cola:
    - Operaciones:
        head() -> Ver el elemento del principio de la cola.
        tail() -> Ver el elemento del final de la cola.
        enqueve(x) -> Agregar el elemento x al final de la cola.
        dequeve() -> Eliminar el ultimo elemento de la cola.

    - Funciones adicionales:
        aEmpty() -> Determina si la cola esta vacia o no.
        reveal() -> Muestra todos los elementos de la cola.

*/

// Classes

class Queves {
    // Variables de la Clase
    vector<int> qElements;
    int firstElement, lastPointer;

public:
    // Constructor
    Queves ( int len ) {
        qElements = vector<int>(len);
        firstElement = -1;
        lastPointer = -1;
    }

    // Funciones de la clase
    int head();
    int tail();
    void enqueve(int number);
    void dequeve();
    bool aEmpty();
    void reveal();
};

// Funtions

int Queves :: head() {
    if ( lastPointer == -1 ) {
        cerr << " Error: Array is empty" << endl;
        exit(1);
    } else {
        return qElements[firstElement];
    }
}

int Queves :: tail() {
    if ( lastPointer == -1 ) {
        cerr << " Error: Array is empty" << endl;
        exit(1);
    } else {
        return qElements[ lastPointer ];
        //return qElements[ qElements.size()-1 ];
    }
}

void Queves :: enqueve( int number) {
    if ( lastPointer < -1 ) {
        cerr << " Error: Out of Range" << endl;
        exit(1);
    }

    if ( lastPointer == -1 ) {
        firstElement++;
    }

    if ( lastPointer == qElements.size() - 1 + firstElement ) {
        cout << " check point 1: " << endl;

        vector<int> newArrayElements = vector<int>( 2 * qElements.size() );
        for ( int k = 0; k < qElements.size() + firstElement; k++ ) {
            newArrayElements[k] = qElements[k];
        }
        cout << " \n Expensive call with: " << number << endl;
        cout << " OldArray size = " << qElements.size() << ", NewArray size = " << newArrayElements.size() << "\n" << endl;
        
		cout << " check point 2: " << endl;
        qElements = newArrayElements;

    }

    qElements[ lastPointer + 1 ] = number;
    lastPointer++;
}

void Queves :: dequeve() {
    if ( lastPointer >= firstElement ) {
        firstElement++;

    } else {
        cerr << " Error: Array is empty " << endl;
        exit(1);
    }
}

bool Queves :: aEmpty() {
    return firstElement > lastPointer;
}

void Queves :: reveal() {
    cout << "\n" << " Queve: ";
    for ( int j = firstElement; j <= lastPointer; j++ ) {
        cout << qElements[j] << " ";
    }
    cout << "\n" << endl;
}

// Main Funtion
int main () {

    int n; cin >> n;
    Queves Q(n);

    cout << " Queve: ";
    for ( int i = 1; i <= n ; i++ ) {
        Q.enqueve(i);
        cout << i << " ";
    }
    cout << "\n" << endl;

    for ( int j = 0; j < 4; j++ ) {
        cout << " Head queve: " << Q.head() << ", Tail queve: " << Q.tail() << endl;
        cout << " Deleted element: " << Q.head() << endl;
        Q.dequeve();
    }

    Q.reveal();

    for ( int i = 1; i <= 10. ; i++ ) {
        Q.enqueve(i*i);
        Q.reveal();
    }

    while ( !Q.aEmpty() ) {
        cout << " Head queve: " << Q.head() << ", Tail queve: " << Q.tail();
        Q.reveal();
        Q.dequeve();
    }

    return 0;
}
