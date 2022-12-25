#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

const int max_n = 1010;
const int max_saltos = 20;

vector<int> succesores[max_n];
int altura[max_n];
int ancestros[max_n][max_saltos];
int N;
int M;

void setear_ancestro(int nodo, int salto) {
        int ancestro_salto_1 = ancestros[nodo][salto-1];

        if(ancestro_salto_1 != -1 && ancestros[ancestro_salto_1][salto-1] != -1) {
                ancestros[nodo][salto] = ancestros[ancestro_salto_1][salto-1]; 
        }
}

void construir() {
        for(int i = 1; i< max_saltos; i++) {
                for(int j =0 ; j < N; j++ ) {
                        setear_ancestro(j, i);
                }
        }
}

void setear_altura(int nodo, int h) {
        altura[nodo] = h;

        for(int i = 0 ; i < succesores[nodo].size(); i++) {
                setear_altura(succesores[nodo][i], h + 1);
        }
}

void subir(int &n, int x) {
       for(int i = max_saltos - 1; i >= 0; i--) {
                if(x & (1 << i)) { // x = 1011 <- ... i = 0 ... 000000001 << 2 = 00000100
                                        //                                       001011
                                        //                                        000000
                                        //                                        5 = 101
                                        //                                        3 = 011
                                        //                                    5 & 3 = 001
                        n = ancestros[n][i];
                }
       } 
}

void nivelar(int &n1, int &n2) {
        if(altura[n1] < altura[n2]) {
                swap(n1,n2);
        }

        int diff = altura[n1] - altura[n2];
        subir(n1, diff);
}

int LCA(int n1, int n2) {
       nivelar(n1, n2);
       if(n1 == n2) {
               return n1 + 1;
       }

       for(int i = max_saltos - 1; i >= 0; i--) {
                if(ancestros[n1][i] != ancestros[n2][i]) {
                        n1 = ancestros[n1][i];      
                        n2 = ancestros[n2][i];      
                }
       }

        return ancestros[n1][0] + 1;
}

int main() {

        int T;
        cin >> T;
        for(int t =0 ; t< T; t++) {

                cin >> N;
                for(int i =0 ; i < N; i++) {
                        for(int j = 0 ; j < max_saltos; j++) {
                                ancestros[i][j] = -1;
                        }
                }
                

                for(int i = 0; i < N ; i++) {
                        cin >> M;
                        int hijo;
                        succesores[i] = vector<int>(M);
                        for(int j = 0; j < M ; j++) {
                                cin >> hijo;
                                hijo--;
                                succesores[i][j] = hijo;
                                ancestros[hijo][0] = i;
                        }
                }
                int raiz = -1;
                for(int i =0 ;i < N ; i++) {
                        if(ancestros[i][0] == -1) {
                                raiz = i;
                                break;
                        }
                }
                setear_altura(raiz, 0);
                construir();

                int Q;
                cin >> Q;
        
                cout << "Case " << t + 1 << ": ";
                for(int i =0 ; i < Q; i++) {
                        int v,w;
                        cin >> v >> w;
                        v--;
                        w--;
                        cout << LCA(v,w) << endl;
                }
        }

        return 0;
}
