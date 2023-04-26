/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class TreeNode
struct TN {
	public:
	string value;
	TN  *firstChild,
		*nextSabling;
	TN (string s) {
		value = s;
		firstChild = NULL,
		nextSabling = NULL;
	}
	TN (string s, TN *fC, TN *nS) {
		value = s;
		firstChild = fC;
		nextSabling = nS;
	}
};

// PreOrder for General Trees
void preorder(TN *n) {
	if (n == NULL)
		return;
	cout << n->value << " ";
	preorder(n->firstChild);
	preorder(n->nextSabling);
}

// PostOrder for General Trees
void postorder(TN *n) {
	if (n == NULL)
		return;
	postorder(n->firstChild);
	cout << n->value << " ";
	postorder(n->nextSabling);
}

int main() {

	TN *T, *T1, *T2;
	
	// Arbol Binario dado en clase practica
	T = new TN("*",
			new TN("+", new TN("23") , new TN("5")),
			new TN("/", new TN("100"), new TN("5"))
		);
	
	// Arbol Binario dado en clase teorica	
	T1 = new TN("1", 
			new TN("2", 
				new TN("4"),
				new TN("3",
					new TN("5",
						new TN("7",
							NULL,
							new TN("8")),
						new TN("6")),
					NULL)), 
			NULL
		);
		
	// Arbol General dado en clase teorica
	T2 = new TN("a", 
			new TN("b",
				new TN("e"),
				new TN("c",
					NULL,
					new TN("d",
						new TN("e",
							new TN("h",
								NULL,
								new TN("i")),
							new TN("g")),
						NULL))), 
			NULL
		);
		
	cout << "Tree T: " << endl;
	cout << "PreOrder:  "; preorder(T);
	cout << "\nPostOrder: "; postorder(T);
	cout << endl;
	
	cout << "\nTree T1: " << endl;
	cout << "PreOrder:  "; preorder(T1);
	cout << "\nPostOrder: "; postorder(T1);
	cout << endl;
	
	cout << "\nTree T2: " << endl;
	cout << "PreOrder:  "; preorder(T2);
	cout << "\nPostOrder: "; postorder(T2);
	cout << endl;
	
	return 0;
}
