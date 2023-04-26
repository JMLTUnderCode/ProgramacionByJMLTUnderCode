#include<iostream>

using namespace std;

const int n = 10000;
int repr[n];


/* 
 *
struct DSU {
        int tam;
        vector<int> repr;

        DSU(int n) : tam(n) {}

        int find();
        void join();
        void make_set;
}
*/
// No se necesita la implementacion del size
int size[n];


void make_set(int idx) {
        repr[idx] = idx;
        // size[idx] = 1;
}

int find(int);
// n1 y n2 no son necesariamente representantes
void join(int n1, int n2) {

        n1 = find(n1);
        n2 = find(n2);

        /*
         * if(size[n1] > size[n2]) {
         *      repr[n2] = n1;
         * } else {
         *      if(size[n1] == size[n2]) {
         *          size[n2] += size[n1];
         *      }
         *      repr[n1] = n2;
         * }
         * */
        repr[n1] = n2;
}


int find(int x) {

        // Operador ternario
        // return repr[x] = ((x == repr[x]) ? x : find(repr[x]);

        if(repr[x] != x) {
                return repr[x] = find(repr[x]);
        }

        return x;
}

int main() {

        for(int i = 0 ; i < n; i++) {
                make_set(i);
                // size[i] = 1;
        }

        return 0;
}
