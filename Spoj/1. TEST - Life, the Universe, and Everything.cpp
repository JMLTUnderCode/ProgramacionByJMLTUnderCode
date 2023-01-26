/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: jmlt_undercode
	Problema: SPOJ 1. TEST - Life, the Universe, and Everything

	Idea General: 
	
	Mediante el uso del bucle while y variables boleanas, adicional al uso del contidional ternario
	se resuelve el problema.
*/

#include <bits/stdc++.h>

using namespace std;

void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
}

int main() {
	init_code();

	int n;
	bool status = true;
	while (scanf("%d", &n) && status) {
		n != 42 ? printf("%d\n", n) : status = false;
	}

	return 0;
}