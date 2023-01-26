/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	Problema: Educational Codeforces Round 94 (Rated for Div. 2) C. Binary String Reconstruction

	Idea General: 
	
	

*/

#include <bits/stdc++.h>

using namespace std;

void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

typedef vector<int> vi;
const int Tmax = 1e3 + 5;
int T, X;
string S;
vector<pair<string, int>> Data(Tmax); 

int main() {
	// Mejora de velocidad para el cin y cout.
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	// Lectura de datos.
	init_code();

	cin >> T;

	for ( int k = 0; k < T; k++) {
		cin >> S; Data[k].first = S;
		cin >> X; Data[k].second = X;		
	}
	
	string auxS;
	int auxX, nz;

	for ( int k = 0; k < T; k++) {
		auxS = Data[k].first;
		auxX = Data[k].second;
		nz = auxS.size();
		vi newString(nz+5);
		bool anyChange = false;

		for( int i = nz; i > 0; i-- ) {
			if( auxS[i-1] == '1' ){
				if ( i > auxX ) {
					newString[i-auxX-1] = 1; 
				} else {
					newString[i+auxX-1] = 1; 
				}
			} else {
				if ( i > auxX ) {
					newString[i-auxX-1] = 0; 
				} else {
					newString[i+auxX-1] = 0; 
				} 
			}
			
		}

		for( int i = 0; i < nz; i++ ) {
			char ch = newString[i]+'0';
			if (ch != auxS[i]) {
				anyChange = true; break;
			}
		}

		if (anyChange) {
			for( int i = 0; i < nz; i++ ) cout << newString[i];
			cout << endl;
		} else {
			cout << "-1" << endl;
		}
	}

	return 0;
}