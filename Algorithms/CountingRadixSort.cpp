#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

vector<int> counting_sort(vector<int> &A) {
	sort(A.begin(), A.end());
	return A;
}

vector<int> radix_sort(vector<int> &A) {
	sort(A.begin(), A.end());
	return A;
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
