#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

void print_vector(vector<int> &A) {
	for (int i=0 ; i<A.size() ; i++)
		cout << A[i] << " ";
	cout << endl;
}

vector<int> bubble_sort(vector<int> A) {
	
	int swaps, n = A.size(), aux;
	
	do {
		swaps = 0;
		for ( int k = 0; k < n-1; k++ ) {
			if ( A[k] > A[k+1] ) {
				aux = A[k+1];
				A[k+1] = A[k];
				A[k] = aux; 
				swaps++;
			}
		}
	} while( swaps != 0 );
	
	return A;
}

vector<int> insertion_sort(vector<int> A) {
	
	int n = A.size(), pos, aux;
	vector<int> R = A;
	
	for ( int k = 1; k < n; k++) {
		for ( int t = 0; t < k; t++ ) {
			if ( A[t] > A[k]) {
				R[t] = A[k];
				
				for ( int i = t+1; i < k+1; i++ ) 
					R[i] = A[i-1];
				
				for ( int i = k+1; i < n ; i++ )
					R[i] = A[i];
					
				A = R;
				break;
			}
		}
	}
	return A;
}

int main(){
	
	int c, n;
	vector<int> A, R;

	cin >> c;
	while(c-->0) {
		cin >> n;
		A = vector<int>(n);
		for (int i=0 ; i<n ; i++)
			cin >> A[i];
			
		R = bubble_sort(A);
		cout << "Bubble Sort:    ";
		print_vector(R);
		R = insertion_sort(A);
		cout << "Insertion Sort: ";
		print_vector(R);
	}

	return 0;
}
