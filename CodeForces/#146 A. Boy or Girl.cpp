/*
    Nombre: Junior Miguel Lara Torres
    Carnet: 1710303
    Nick: JMLTUnderCode
    Problema: Codeforces Round #146 (Div. 2) A. Boy or Girl

    Idea General: 
    Procedemos a eliminar los caracteres repetidos. Aquellas primeras ocurrencias del 
    caracter se mantendran. Ej. htraarhh -> htraar -> htraa -> htra. Este proceso lo realizamos
    con los bucles while anidados se irá recorriendo el string dado y eliminando las repeticiones
    de chars. Finalmente, cuando se tenga el caracter sin chars repetidos procedemos a verificar
    la paridad de este string resultante y mostrar la respuesta segun sea el caso pedido por el 
    problema.
    
*/

#include <bits/stdc++.h>

using namespace std;

// Inicializacion y definicion de variables/estructuras de datos/formatos.
string user_name;
int i, j, s_string;

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
    
    // Lectura de datos.
    init_code();

    cin >> user_name;
    // Fin lectura de datos.

    // Procedemos a eliminar los caracteres repetidos.
    s_string = user_name.size();
    i = 0;
    while ( i < s_string ) {
        j = i+1;
        while ( j < s_string ) {
            // Eliminamos el caracter repetido y actualizamos el tamaño del string.
            while ( user_name[i] == user_name[j] ) {
                user_name = user_name.erase(j, 1);
                s_string--;
            }
            j++;
        }
        i++;
    }

    // En caso de conseguir una cantidad par de caracteres
    // nuestro Heroe debe chatear, de lo contrario ignorar.
    ( user_name.size()%2 == 0) ? printf("%s\n","CHAT WITH HER!") : printf("%s\n","IGNORE HIM!");

    return 0;
}
