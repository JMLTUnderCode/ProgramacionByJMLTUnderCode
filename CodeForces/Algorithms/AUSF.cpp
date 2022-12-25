#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

struct DSU {
	int len;
	vector<int> repr;
	
	DSU(int n) : len(n) {
		repr.resize(len+1);
	}
	
	int find(int);
	void join(int, int);
	void make_set(int);
};

void DSU::make_set(int idx) {
        repr[idx] = idx;
}

int DSU::find(int x) {

        // Operador ternario
        //return repr[x] = ((x == repr[x]) ? x : find(repr[x]) );

        if(repr[x] != x) {
                return repr[x] = find(repr[x]);
        }

        return x;
}

// n1 y n2 no son necesariamente representantes
void DSU::join(int n1, int n2) {
        n1 = find(n1);
        n2 = find(n2);

        repr[n1] = n2;
}

map<string, int> indices;
int main() {

        int Q;
        cin >> Q;
		
		DSU R(100001);
        string s1, s2;
        int unicos = 0;
        
        for(int i = 0 ; i < Q; i++) {
                // scanf("%d", &var)
                // scanf("%c", &var)
                // scanf("%s", arreglo_de_chars)
                cin >> s1 >> s2 ;
                if(indices.count(s1) == 0) {
                        // inserta en el mapa "indices" el par (s1, unicos)
                        indices[s1] = unicos;
                        R.make_set(unicos);
                        unicos++;
                }
                if(indices.count(s2) == 0) {
                        indices[s2] = unicos;
                        R.make_set(unicos);
                        unicos++;
                }

                int repr1 = R.find(indices[s1]);
                int repr2 = R.find(indices[s2]);

                if(repr1 == repr2) {
                        cout << "Found in friend list" << endl;
                } else {
                        cout << "Found by random" << endl;
                }

                R.join(repr1, repr2);
        }

        return 0;
}
