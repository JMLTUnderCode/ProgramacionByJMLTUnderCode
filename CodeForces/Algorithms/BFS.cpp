/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General: 
	Se ingresan la cantidad de arcos. He imprire el Arbol BFS respectivo.
		
*/

#include <bits/stdc++.h>

using namespace std;

void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

void print_vector(vector<int> &A) {
	for (int i=0 ; i<A.size() ; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

vector<int> BFS(vector<list<int>> G, int raiz){
	
	queue<int> Cola;
	int v;
	list<int> ady;
	list<int>::iterator it;
	
	int n = G.size();
	vector<int> visitados(n, 0);
	vector<int> bfs_tree(n, 0);
	int aux = 0;
	
	Cola.push(raiz);
	visitados[raiz-1] = 1;

	while (!Cola.empty()) {

		v = Cola.front();
		bfs_tree[aux] = v;
		aux++;
		Cola.pop();
		
		ady = G[v-1];
		it = ady.begin();
		
		while ( it != ady.end() ) {
			
			if (visitados[*it-1] == 0) {
				visitados[*it-1] = 1;
				Cola.push(*it);
			}
			it++;
		}
	}

	return bfs_tree;
}


int main() {

	init_code();

	int n; 
	vector<int> arc(2);
	
	cin >> n;
	vector<list<int> > grafo(n);

	for( int k = 0; k < n-1; k++ ) {
		cin >> arc[0] >> arc[1];
		grafo[arc[0]-1].push_back(arc[1]);
	}

	vector<int> bfs_tree = BFS(grafo, 1);
	
	print_vector(bfs_tree);
	
	return 0;
}
