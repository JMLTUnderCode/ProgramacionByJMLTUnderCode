#include <iostream>
#include <vector>
#include <queue>
#include <deque>
 
using namespace std;

vector<int> sol_nk(vector<int> &A, int n, int k) {
	vector<int> R;
	for (int i=0 ; i<=n-k ; i++) {
		R.push_back(A[i]);
		for (int j=1 ; j<k ; j++)
			R[i] = max(R[i], A[i+j]);
	}
	return R;
}

vector<int> sol_nlog(vector<int> &A, int n, int k) {
	vector<int> R;
	priority_queue<int> Aft, Bef;
	for (int i=0 ; i<k ; i++) {
		Aft.push(A[i]);
	}
	R.push_back(Aft.top());
	for (int i=k ; i<n ; i++) {
		Bef.push(A[i-k]);
		Aft.push(A[i]);
		while (!Bef.empty() && Bef.top()==Aft.top()) {
			Bef.pop();
			Aft.pop();
		}
		R.push_back(Aft.top());
	}
	return R;
}

vector<int> sol_n(vector<int> &A, int n, int k) {
	vector<int> R;
	deque<int> D;
	// SOLVE
	// https://www.cplusplus.com/reference/deque/deque/
	return R;
}

int main() {

	int n, k, temp;
	vector<int> A, R;

	cin >> n;
	for (int i=0 ; i<n ; i++) {
		cin >> temp;
		A.push_back(temp);
	}
	cin >> k;

//	R = sol_nk  (A, n, k); // realmente -> O(nk)
//	R = sol_nlog(A, n, k); // realmente -> O(nlogn)
	R = sol_n   (A, n, k); // realmente -> O(n)

	for (int i=0 ; i<R.size() ; i++)
		cout << (i==0 ? "" : " ") << R[i];
	cout << endl;

	return 0;
}
