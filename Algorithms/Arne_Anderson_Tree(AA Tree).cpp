/*
	Nombre: Junior Miguel Lara Torres
	Codeforces: JMLTUnderCode
	SPOJ: jmlt_undercode
	Carnet: 1710303
	
	Especificaciones de implementacion:
	
	Un arbol AA Tress es un concepto propuesto por Arne Anderson en 1993. Es similar
	a un Red-Black Tree pero consta de la caracteristica de que aquellos nodos "Rojos"
	son hijos derecho de los nodos "Negros". 
	Adicionalmente, todos los nodos de tipo "Hoja" apuntan/conectan con un nodo tipo 
	"NILL" conocido como "Nodo Sentinela", dicho nodo conecta consigo mismo.

	Funciones del Arbol:
	- skew: Arregla hijos izquierdo rojos.
	- split: Arregla una cadena de hijos derechos rojos.
	- insert: Inserta un nodo en el AA Tree.
	- erase: Busca y elimina un nodo.
	- fixAfterDelete: Luego de aplicar ERASE, reordena/organiza los nodos para mantener 
	propiedades de AA Tree.
	
	Funciones de uso publico/usuario:
	- insert: Permite al usuario insertar un nodo.
	- erase: Permite al usuario seleccionar un nodo a eliminar.
	- draw: Muestra por consola/archivo el boseto del arbol.

	Funcionamiento del programa.
	- Realizar una busqueda sobre un Binary Search Tree(BST).
		- En caso de encontrar el elemento realizar la busqueda del 
		"inorder succesor" y sustituir por el nodo a eliminar. 
	- Se debe realizar un "FixAfterDelete" de manera recurrente
	para asegurar de mantener las propiedades de un AA Tree.

	inputs/outputs:
	Si NO esta ejecutando este programa por algun editor de texto(sublime, etc) que este
	modificado para programacion competitiva donde lea los input y muestre la salida
	por archivos, entonces se ha programa una interaccion con el usuario
	para trabajar en base a los deseos del mismo. De lo contrario, debe leer y entender 
	la lectura de datos en seccion "main" antes de tener errores.

*/

#include <bits/stdc++.h>
 
using namespace std;

// Estructura tipo nodo basado en las caracteristicas de un AA Tree.
struct AAnode {
	int key, value, level;	// Informacion basica del nodo.
	AAnode *left, *right;	// Hijos del nodo actual.

	// Constructor de la clase.
	AAnode(int _k, int _v, int _lv, AAnode *l, AAnode *r) {
		key = _k; value = _v; level = _lv; right = r; left = l;
	}
};

// Estructura de un arbol AA Tree.
class AAtree {
	AAnode *root, *nil;

	// Funcion basicas y esenciales del AA Tree.
	AAnode* insert(AAnode*, int, int);
	AAnode* skew(AAnode*);
	AAnode* split(AAnode*);
	AAnode* erase(AAnode*, int);
	AAnode* fixAfterDelete(AAnode*);

	// Determina la secuencia IN-ORDER del arbol.
	pair<int,int> inorder_succesor(AAnode*);
	
	public:
	
	// Constructor de la clase.
	AAtree() {
		nil = new AAnode(0, 0, 0, NULL, NULL);
		nil->left  = nil;
		nil->right = nil;
		root = nil;
	}

	// Funcion de tipo publico para el uso del usuario.
	void insert(int, int);  // Para agregar un nodo al arbol.
	void erase(int);	// Para eliminar un nodo del arbol.
	void draw() {		// Para mostrar el arbol creado.
		draw(root, 0);
	}

	// Funcion que muestra el valor y llave de cada nodo de forma ordenada.
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

// Realizamos la misma busqueda que en AVL Trees, a diferencia que
// al retornar nodos debes realizar un "fixAfterDelete" en vez de 
// "balance". Una vez hallado el nodo a sustituir se extrae el valor
// y la llave que lo identidica en el BST, (Ver implementacion para
// AVL'S en caso de estar viendo esta implementacion primero.)
AAnode* AAtree::erase(AAnode *p, int k) {
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

// Escribir "FastIO_RWFile();" justo despues al comienzo del "int main() {" para lectura y escritura
// de datos por archivos "input.txt" y "output.txt" respectivamente, con sincronizacion de velocidad 
// para Cin y Cout.
void FastIO_RWFile(){
	/*#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
 
	// Mejora de velocidad para el cin y cout.
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}

int main() {
	// Lectura de datos por archivos de texto y aumento de velocidad CIN-COUT.
	FastIO_RWFile();

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
		
	return EXIT_SUCCESS;
}
