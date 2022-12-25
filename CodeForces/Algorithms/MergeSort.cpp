#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

void merge(vector<int> &A, int l, int m, int r) {
	vector<int> R(r-l);
	
	int i = l,
		j = m,
		k = 0;
		
	while ( i < m && j < r ){
		if ( A[i] < A[j]) {
			R[k++] = A[i++];
		} else{
			R[k++] = A[j++];
		}
	}

	while ( i < m )
		R[k++] = A[i++];
		
	while ( j < r )
		R[k++] = A[j++];
		
	for ( int k = 0; k < R.size(); k++ ) 
		A[l+k] = R[k];
}


void merge_sort(vector<int> &A, int l, int r) {
		
	if ( r-l <= 1)
		return;
	
	int m = (r+l) / 2;
	merge_sort(A, l, m);
	merge_sort(A, m, r);
	
	merge(A, l, m, r);
	
}

void merge_sort(vector<int> &A) {
	merge_sort(A, 0, A.size());
}


void print_vector(vector<int> &A) {
	for (int i=0 ; i<A.size() ; i++)
		cout << A[i] << " ";
	cout << endl;
}

int main() {

	int c, n;
	vector<int> A;

	cin >> c;
	while(c-->0) {
		cin >> n;
		A = vector<int>(n);
		for (int i=0 ; i<n ; i++)
			cin >> A[i];
		merge_sort(A);
		cout << "Merge Sort: ";
		print_vector(A);
	}

	return 0;
}
