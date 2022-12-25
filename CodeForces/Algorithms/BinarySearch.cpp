#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

// Funtions

int BinaryS_BF(vector<int> v, int num){ // Implementacion tradicional
	int L = 0;
	int R = v.size()-1;

	while ( L <= R ) {
		int mid = (L+R)/2;
		if ( v[mid] == num ) {
			return mid;
		} else if ( v[mid] > num ) {
			R = mid-1 ;
		} else {
			L = mid+1 ;
		}
	}
	
	// Si llegamos a este punto es porque no existe el elemento dentro
	// del arreglo.
	cout << "\n The number is not found." << endl;
	exit(1);	
	
}

int BinaryS_Recur(vector<int> v, int num, int l, int r) {
	int mid = (l+r)/2;
	if ( l > r ) {
		return -1;
	} else if ( v[mid] == num ) {
		return mid;
	} else if ( v[mid] < num ) {
		return BinaryS_Recur(v,num,mid+1, r);
	} else if ( v[mid] > num ) {
		return BinaryS_Recur(v,num,l, mid-1);
	}
}

int BinaryS_Bit(vector<int> v, int num){ // Implementacion por Bits
	int bit = 0;
	int test_n = 0;
	int temp;
	
	for(int i=30; i>=0; i--) {
		//test_n = pow(2,i);
		temp = test_n + pow(2,i);
		if ( temp < v.size() ) {
			
			if ( v[temp] == num ) {
				bit += pow(10,i) ;
				return bit;
				
			} else if ( v[temp] < num ) {
				test_n += pow(2,i);
				bit += pow(10,i) ; 
			}
		}	
	}
	
	// El caso para el elemento primer elemento del arreglo.
	if ( v[0] == num ) {
		return bit;
	}	
	
	// Si llegamos a este punto es porque no existe el elemento dentro
	// del arreglo.
	cout << "\n The number is not found." << endl;
	exit(1);
}


int main() {
	
	int n;
	// Precondicion: n > 0
	try{
		
		cout << "Size: "; cin >> n; cout << endl;
		if ( n < 1 ){
			throw "Precondition Error: n > 0";
		}
	} catch (const char* err) {
		cout << err << endl;
		exit(1);
	}

	vector<int> v;
	srand(time(NULL));
	for (int i = 0; i < n; i++){
		/*	Para generar un numero random en un rango [ L, R ] se debe incluir
			#include <ctime>. Luego se debe escribir:
			
			srand(time(NULL));
			numberRandom = rand() % ( R - L + 1 ) + L;
		*/
		v.push_back( rand() % (10*(i+1) - (10*i) + 1 ) + 10*i );
	}
	
	
	cout << "Elements: ";
	for (int i=0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	
	int num; cout << endl << "The number: "; cin >> num;
	
	cout << " In BF index: " << BinaryS_BF(v,num) << endl;
	cout << " In Recur index: " << BinaryS_Recur(v,num,0,v.size()) << endl;
	cout << " In Bit index: " << BinaryS_Bit(v,num) << endl;
	return 0;
}
