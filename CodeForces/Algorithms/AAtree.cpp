/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	
	Idea principal para la implementacion: 
	
	 Realizar una busqueda sobre un BST, en caso de encontrar el elemento
	 realizar la busqueda del inorder succesor y sustituir por el nodo a
	 eliminar. Luego, se debe realizar un FixAfterDelete de manera recurrente
	 para asegurar de mantener las propiedades de un AA Tree. 
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <utility>

using namespace std;

struct AAnode {
	int key,
		value,
		level;
	AAnode *left,
		   *right;
	AAnode(int _k, int _v, int _lv, AAnode *l, AAnode *r) {
		key = _k;
		value = _v;
		level = _lv;
		right = r;
		left = l;
	}
};

class AAtree {

	AAnode *root,
	       *nil;

	AAnode* insert(AAnode*, int, int);
	AAnode* skew(AAnode*);
	AAnode* split(AAnode*);

	AAnode* rotate_right(AAnode*);
	AAnode* rotate_left(AAnode*);
	AAnode* rotate_left_right(AAnode*);
	AAnode* rotate_right_left(AAnode*);
	AAnode* balance(AAnode*);
	pair<int,int> inorder_succesor(AAnode*);
	
	AAnode* erase(AAnode*, int);
	AAnode* fixAfterDelete(AAnode*);
	

	public:
	
	AAtree() {
		nil = new AAnode(0, 0, 0, NULL, NULL);
		nil->left  = nil;
		nil->right = nil;
		root = nil;
	}
	void insert(int, int);
	void erase(int);

	void draw() {
		draw(root, 0);
	}
	void draw(AAnode *p, int ind) {
		if (p != nil) {
			draw(p->right, ind+1);
			for (int i=0 ; i<ind ; i++)
				cout << "\t\t";
			cout << "(k:" << p->key << ",v:"
			     << p->value << ",l:"
			     << p->level << ")" << endl;
			draw(p->left, ind+1);
		}
	}
};

void AAtree::insert(int k, int v) {
	root = insert(root, k, v);
}

AAnode* AAtree::insert(AAnode *p, int k, int v) {
	if (p == nil) {
		p = new AAnode(k, v, 1, nil, nil);
	} else if (k < p->key) {
		p->left = insert(p->left, k, v);
	} else if (k > p->key) {
		p->right = insert(p->right, k, v);
	} else {
		p->value = v;
	}
	return split(skew(p));
}

AAnode* AAtree::skew(AAnode *p) {
	if (p == nil) return p;
	if (p->left->level == p->level) {
		AAnode* q = p->left;
		p->left = q->right;
		q->right = p;
		return q;
	}
	return p;
}

AAnode* AAtree::split(AAnode *p) {
	if (p == nil) return p;
	if (p->right->right->level == p->level) {
		AAnode* q = p->right;
		p->right = q->left;
		q->left = p;
		q->level++;
		return q;
	}
	return p;
}

// Determina el Inorder Succesor, retorna su valor y llave.
pair<int,int> AAtree::inorder_succesor(AAnode *p) {
	
	if ( p -> left -> left == nil ) {
		int k_r = p -> left -> key;
		int v_r = p -> left -> value;
		
		p -> left = p -> left -> right;
		return {k_r,v_r};
		
	} else {
		return inorder_succesor(p -> left);
	}
}

void AAtree::erase(int k) {
	root = erase(root, k);
}

AAnode* AAtree::erase(AAnode *p, int k) {
	
	// Realizamos la misma busqueda que en AVL Trees, a diferencia que
	// al retornar nodos debes realizar un "fixAfterDelete" en vez de 
	// "balance". Una vez hallado el nodo a sustituir se extrae el valor
	// y la llave que lo identidica en el BST, (Ver implementacion para
	// AVL'S en caso de estar viendo esta implementacion primero.)
	
	if( p == nil ) {
		return p;
		
	} else if ( k < p -> key ) {
		p -> left = erase(p -> left, k );
		p -> left = fixAfterDelete(p -> left);
		
	} else if ( k > p -> key ) {
		p -> right = erase(p -> right, k );
		p -> right = fixAfterDelete(p -> right);
		
	} else if ( k == p -> key ) {
	
 		if ( p -> right == nil ) {
			return p -> left;
			
		} else if ( p -> right -> left == nil ){
			p -> right -> left = p -> left; 
			return p -> right;
			
		} else {
			pair<int,int> data = inorder_succesor(p -> right);
			p -> key = data.first;
			p -> value = data.second;
			p -> right = fixAfterDelete(p -> right);

		}
	}

	return fixAfterDelete(p);
}


AAnode* AAtree::fixAfterDelete(AAnode *p) {
	int l = 1 + min(p->left->level, p->right->level);
	if (p->level > l) {
		p->level = l;
		if (p->right->level > 1) 
			p->right->level = l;
	}
	p = skew(p);
	p->right = skew(p->right);
	p->right->right = skew(p->right->right);
	p = split(p);
	p->right = split(p->right);
	return p;
}

int main() {
	
	srand (time(NULL));
	
	AAtree T;
	
    // Generamos un arbol random, o usar "r = i;" para tener un secuencia.
	for (int i=15 ; i>=1 ; i--) {
		T.insert(i, rand() % 100);
	}
	
	// Mostramos el arbol generado anteriormente.
	T.draw();
	cout << "\n\n\n\n" << endl ;
	
	// Interactuamos con el usuario en querer Delete o Insert 
	int op, k, val;
	cout << "0 -> Insert,  1 -> Delete, AnyNumber -> Exit: ";
	cin >> op;

	while ( op == 1 || op == 0 ){
		if( op == 0 ) {
			cout << "Insert: " << endl;
			cout << "Key: "; cin >> k;
			cout << "Value:"; cin >> val; 
			T.insert(k, val);
		} else {
			cout << "Delete: "; cin >> k;
			T.erase(k);
		}
			
		T.draw();
		cout << endl << endl;	
		cout << "0 -> Insert,  1 -> Delete, AnyNumber -> Exit: ";
		cin >> op;
	}
		
	return 0;
}
