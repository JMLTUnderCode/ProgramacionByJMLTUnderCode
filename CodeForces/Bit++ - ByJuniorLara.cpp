#include<iostream>
#include<string>

using namespace std;

int main() {

    // Inicializamos variables y pedimos datos por pantalla.
    int num_sentences;

    cin >> num_sentences;

    string sentence;
    int x=0;

    /*
        Realizamos un bucle en funcion de la cantidad de
        sentencias determinadas anteriormente.
        Basta con verificar el caracter central se la sentencia
        para saber si aumentar o disminuir x en 1.
    */

    for (int i = 0; i < num_sentences; i++) {

        cin >> sentence;

        if ( sentence[1]=='+' ) {
            x++;
        } else {
            x--;
        }
    }

    cout << x;

    return 0;
}
