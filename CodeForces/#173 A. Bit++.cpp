/*
    Nombre: Junior Miguel Lara Torres
    Carnet: 1710303
    Nick: JMLTUnderCode
    Problema: Codeforces Round #173 (Div. 2) A. Bit++

    Idea General: 
    
    Realizamos un bucle en funcion de la cantidad de sentencias determinadas anteriormente.
    Basta con verificar el caracter central se la sentencia para saber si aumentar o disminuir 
    x en 1.

*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos
int num_sentences, x = 0;
string sentence;

// Funcion para lectura de documentos/casos de prueba.
void init_code(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

int main() {

    // Mejora de velocidad para el cin y cout.
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Lectura de datos
    init_code();

    cin >> num_sentences;

    for (int i = 0; i < num_sentences; i++) {
        cin >> sentence;
        ( sentence[1]=='+' ) ? x++ : x--;
    }

    cout << x;

    return 0;
}
