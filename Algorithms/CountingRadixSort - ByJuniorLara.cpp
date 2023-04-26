#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

vector<int> counting_sort(vector<int> &A, vector<int> &S) {

	// Precondicion: A.size() == S.size()
	
	int m = A[0], n = A.size();
	
	for ( int i = 1; i < n; i++)
		m = max(m, A[i]);
	
	vector<int> accum(m+1, 0);
	vector<int> R(n);
		
	for ( int i = 0; i < n; i++ )
		accum[A[i]]++;
	
	for ( int i = 1; i <= m; i++ )
		accum[i] += accum[i-1];
		
	for ( int i = n-1; i >= 0; i-- ) {
		accum[A[i]]--;
		R[accum[A[i]]] = S[i];
	}

	return R;
}

vector<int> counting_sort(vector<int> &A) {
	return counting_sort(A, A);
}

vector<int> radix_sort(vector<int> &A) {
	
	int n = A.size(), d = 1, m = A[0];
	
	vector<int> dig(n), R(A);
	
	for ( int i = 1; i < n; i++) {
		m = max(m, A[i]);
	}
	
	while ( m >= d ) {
		for ( int i=0; i<n; i++ )
			dig[i] = ( R[i]/d ) % 10;
		R = counting_sort(dig, R);
		d *= 10;
	}
	return R;
}

void print_vector(vector<int> &A) {
	for (int i=0 ; i<A.size() ; i++)
		cout << A[i] << " ";
	cout << endl;
}

int main() {

	int c, n;
	vector<int> A, R;

	cin >> c;
	while(c-->0) {
		cin >> n;
		A = vector<int>(n);
		for (int i=0 ; i<n ; i++)
			cin >> A[i];
		R = counting_sort(A);
		cout << "Counting Sort: ";
		print_vector(R);
		R = radix_sort(A);
		cout << "Radix Sort:    ";
		print_vector(R);
	}

	return 0;
}
