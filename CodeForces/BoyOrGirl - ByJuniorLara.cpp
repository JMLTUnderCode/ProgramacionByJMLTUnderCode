#include<iostream>
#include<string>

using namespace std;

int main() {
    // Inicilizamos variables y pedimos informacion por pantalla.
    string name;
    cin >> name;

    int ssize = name.size();

    // Procedemos a eliminar los caracteres repetidos.
    // Aquellas primeras ocurrencias del caracter se
    // mantendran. Ej. htraarhh -> htraar -> htraa -> htra

    int i = 0;
    while ( i < ssize ) {

        int j = i+1;
        while ( j < ssize ) {

            while ( name[i]==name[j] ) {
                // Eliminamos el caracter repetido y
                // actualizamos el tamaño del string.
                name = name.erase(j,1);
                ssize--;
            }
            j++;
        }
        i++;
    }


    // En caso de conseguir una cantidad par de caracteres
    // nuestro Heroe debe chatear, de lo contrario ignorar.
    if ( name.size() % 2 == 0) {
        cout << "CHAT WITH HER!" << endl;
    } else {
        cout << "IGNORE HIM!" << endl;
    }

    return 0;
}
