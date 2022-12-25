#include <iostream>
#include <vector>

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

void DSU :: make_set(int idx) {
        repr[idx] = idx;
}

int DSU :: find(int x) {

        // Operador ternario
        // return repr[x] = ((x == repr[x]) ? x : find(repr[x]));

        if(repr[x] != x) {
                return repr[x] = find(repr[x]);
        }

        return x;
}

// n1 y n2 no son necesariamente representantes
void DSU :: join(int n1, int n2) {

        n1 = find(n1);
        n2 = find(n2);

        repr[n1] = n2;
}

int main() {
	
	for(int i = 0; i < n; i++) {
		repr[i] = i;
	}
	
	return 0;
}
