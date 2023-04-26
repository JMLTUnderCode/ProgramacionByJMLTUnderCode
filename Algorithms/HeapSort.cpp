#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;

struct BinaryHeap {
	int n;
	vector<int> T;
	BinaryHeap() {
		n = 0;
		T = vector<int>(100);
	}
	int top();
	void pop();
	void insert(int v);
	bool empty();
};

int BinaryHeap::top() {
	if (n == 0)
		exit(0);
	return T[0];
}

void BinaryHeap::pop() {
	T[0] = T[--n];
	int i = 0, next, son;
	while (true) {
		next = i;
		son = 2*i + 1;
		for (int j=0 ; j<2 ; j++) {
			son += j;
			if (son < n && T[son] < T[next])
				next = son;
		}
		if (next == i) break;
		swap(T[i], T[next]);
		i = next;
	}
}

void BinaryHeap::insert(int v) {
	int i = n, dad;
	T[n++] = v;
	while (i > 0) {
		dad = (i-1)/2;
		if (T[i] >= T[dad])
			break;
		swap(T[i], T[dad]);
		i = dad;
	}
}

bool BinaryHeap::empty() {
	return n == 0;
}

void heap_sort(vector<int> &A) {
	BinaryHeap H;
	for (int i=0 ; i<A.size() ; i++)
		H.insert(A[i]);
	for (int i=0 ; i<A.size() ; i++) {
		A[i] = H.top();
		H.pop();
	}
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
		heap_sort(A);
		cout << "Heap Sort: ";
		print_vector(A);
	}

	return 0;
}
