/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode

	Idea General: 
	
	


*/

#include <bits/stdc++.h>
#include <stack>

using namespace std;

void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

void DFS(vector<list<int>> G, int raiz, int t){
	stack<int> Pila;
	int v;
	list<int> ady;
	list<int>::iterator it;
	
	int n = G.size();
	vector<int> visitados(n+1, 0);
	
	Pila.push(raiz);
	visitados[raiz] = 1;

	while (!Pila.empty()) {
		v = Pila.top();
		Pila.pop();
		
		ady = G[v];
		it = ady.begin();
		
		while ( it != ady.end() ) {
			if (visitados[*it] == 0) {
				visitados[*it] = 1;
				Pila.push(*it);			
			}
			if (*it == t) {
				cout << "YES";
				return;
			}
			it++;
		}
	}
	cout << "NO";
	return;
}

int main() {
	
	init_code();

	int n, t, aux;
	cin >> n >> t;

	vector<int> transportation(n, 0);
	vector<list<int> > grafo(n+1);

	for (int k = 1; k < n; k++) {
		cin >> transportation[k];
	}

	aux = 1;
	while (aux < n) {
		grafo[aux].push_back(aux+transportation[aux]);
		aux += transportation[aux];
	}
	
	DFS(grafo, 1, t);

	return 0;
}