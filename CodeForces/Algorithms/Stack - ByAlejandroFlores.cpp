


#include <iostream>
#include <vector>

using namespace std;

// Implementacion de una Pila

class Stack {
	// Variables de clase
	// vector<int> L;
	int *L;
	int last, n;

	public:
	// Funciones / Operaciones
	Stack() {
		// L = vector<int>(2);
		L = new int[2];
		last = -1;
		n = 2;
	}
	void push(int);
	int  top();
	void pop();
	bool empty();
};

void Stack::push(int v) {
	
	if (n-1 == last) {
		// Lnew = vector<int>(2 * n);
		int *Lnew = new int[2 * n];
		for (int i=0 ; i<n ; i++) {
			Lnew[i] = L[i];
		}
		L = Lnew;
		n *= 2;
	}

	L[last+1] = v;
	last++;
}

int Stack::top() {
	if (last == -1) {
		cerr << "Error: La cagaste" << endl;
		exit(1);
	}
	return L[last];
}

void Stack::pop() {
	if (last == -1) {
		cerr << "Error: La cagaste" << endl;
		exit(1);
	}
	last--;
}

bool Stack::empty() {
	return (last == -1);
}

int main() {

	Stack S;
	
	for (int i=1 ; i<=10 ; i++)	{
		S.push(i);
	}

	while (!S.empty()) {
		int v = S.top();
		S.pop();
		cout << v << endl;
	}

	return 0;
}
