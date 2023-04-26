/*
	Nombre: Junior Miguel Lara Torres
	Codeforces: JMLTUnderCode
	SPOJ: jmlt_undercode
	Carnet: 1710303
	
	Especificaciones de implementacion:
	
	Un árbol AVL es un tipo especial de árbol binario ideado por los matemáticos soviéticos 
	Adelson-Velskii y Landis. Fue el primer árbol de búsqueda binario auto-balanceable que se ideó. 
	Adicionalmente, unas de las propiedades es para UN nodo de búsqueda v, las alturas de sus 
	subárboles difieren en <= 1. 

	Funciones en general:
	- height: Retorna la altura de un nodo.
	- update_height: Configura la altura de un nodo en baso a sus nodos hijos.
	- balance_factor: Determina el favor de balance para un nodo dado.
	- rotate_right: Genera rotaciones a la derecha para mantener propiedades del AVL TREE.
	- rotate_left: Genera rotaciones a la izquierda para mantener propiedades del AVL TREE.
	- rotate_left_right: Genera rotaciones a la izquierda, luego a la derecha para mantener
				propiedades del AVL TREE.
	- rotate_right_left: Genera rotaciones a la derecha, luego izquierda  para mantener
				propiedades del AVL TREE.
	- balance: Rebalancea el arbol una vez se elimina o agrega un nodo.
	- inorder-succesor: Determina la succesion IN-ORDER del arbol.
	- insert: Agrega un nodo al arbol.
	- erase: Elimina un nodo del arbol.
	- draw: Muestra el arbol construido por consola/file.

	Funcionamiento del programa.
	- Realizar una busqueda sobre un Binary Search Tree(BST).
		- En caso de encontrar el elemento realizar la busqueda del 
		"inorder succesor" y sustituir por el nodo a eliminar. 
	- Se debe realizar las correspondientes rotaciones de manera recursiva, 
	esto con ayuda de la funcion "balance" para conseguir como resultado 
	un arbol que cumpla las propiedades de AVL.

	inputs/outputs:
	Si NO esta ejecutando este programa por algun editor de texto(sublime, etc) que este
	modificado para programacion competitiva donde lea los input y muestre la salida
	por archivos, entonces se ha programa una interaccion con el usuario
	para trabajar en base a los deseos del mismo. De lo contrario, debe leer y entender 
	la lectura de datos en seccion "main" antes de tener errores.

*/

#include <bits/stdc++.h>
 
using namespace std;

// Estructura tipo nodo basado en las caracteristicas de un AVL Tree.
struct AVLNode {
	int v; // Valor del nodo.
	int h; // Altura del nodo.
        AVLNode *left, *right; // Hijos del nodo actual.

        // Constructor de la estructura.
        AVLNode(int height, int val) : h(height), v(val) {
                left = nullptr; right = nullptr;
        }
};

// Funcion que configura la altura de un AVLNODE.
int height(AVLNode *n) {
        return (n == nullptr) ? -1 : n -> h;
}

// Funcion que actualiza la altura de un AVLNODE.
void update_height(AVLNode *n) {
        if(n != nullptr) {
                n->h = 1 + max(height(n->left), height(n->right));
        }
}

// Funcion que determina el factor de balance de un AVLNODE.
int balance_factor(AVLNode *n) {
        return height(n -> right) - height(n -> left);
}

// Funcion que actualiza el root del arbol en funcion de una rotacion a la
// derecha del grafo basado en concepto de un AVL TREE.
AVLNode *rotate_right(AVLNode *old_root) {

        assert(old_root->left != nullptr);
        AVLNode *new_root = old_root->left;
        AVLNode *node_c = new_root -> right;

        new_root -> right = old_root;
        old_root -> left = node_c;
        update_height(old_root);
        update_height(new_root);

        return new_root;
}

// Funcion que actualiza el root del arbol en funcion de una rotacion a la
// izquierda del grafo basado en concepto de un AVL TREE.
AVLNode *rotate_left(AVLNode *old_root) {

        assert(old_root->right != nullptr);
        AVLNode *new_root = old_root->right;
        AVLNode *node_c = new_root -> left;

        new_root -> left = old_root;
        old_root -> right = node_c;
        update_height(old_root);
        update_height(new_root);

        return new_root;
}

// Funcion que actualiza el root del arbol en funcion de una rotacion a la
// izquierda luego derecha del grafo basado en concepto de un AVL TREE.
AVLNode *rotate_left_right(AVLNode *root) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
}

// Funcion que actualiza el root del arbol en funcion de una rotacion a la
// derecha luego izquierda del grafo basado en concepto de un AVL TREE.
AVLNode *rotate_right_left(AVLNode *root) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
}

// Funcion que permite rebalancear un AVL TREE luego de eleminiar/agregar un
// nodo al grafo.
AVLNode *balance(AVLNode *root) {
        if (root == nullptr ) return root;

        if (balance_factor(root) > 1) {
                if(height(root->right->right) > height(root->right->left)) {
                        root = rotate_left(root);
                } else {
                        root = rotate_right_left(root);
                }
        } else if(balance_factor(root) < -1) {
                if(height(root->left->left) > height(root->left->right)) {
                        root = rotate_right(root);
                } else {
                        root = rotate_left_right(root);
                }               
        }

        update_height(root);
        return root;
}

// Funcion que permite agregar un nodo AVL Tree.
AVLNode *insert(AVLNode *root, int val) {
        if( root == nullptr ) {
            return new AVLNode(0, val);
        } 

        if( val < root->v ) {
            root->left = insert(root->left, val);
        }

        if( val > root->v ) {
            root -> right = insert(root->right, val);
        }

        return balance(root);
}

// Determina el Inorder Succesor, retorna su valor
int inorder_succesor(AVLNode *root) {
	// Como el succesor buscado siempre estara lo mas a la izquierda posible
	// una vez nos movamos a la derecha del valor a eliminar entonces 
	// 
	if ( root -> left -> left == nullptr ) {
		//
		//             /
		//           val
		//       /        \
		//     n1          n3  <- root
		//      \       /    \
		//       n2    n4     n6
		//		      /  \
		//         null   n5
		// 
		// Se toma el valor de n4 (succesor), reasignamos los hijos de los
		// nodos correspondientes y retornamos valor a restituir.
		int val = root -> left -> v;
		root -> left = root -> left -> right;
		return val;
		
	} else {
		// Si no pasa lo anterior, llamamos recursivamente, tanto a la izquierda
		// como se pueda.
		return inorder_succesor(root -> left);
	}
}

AVLNode *erase(AVLNode *root, int val) {
	
	// Caso Base, cuando no se haya encontrado "val" en el arbol
	if( root == nullptr ) {
		return root;
		
	// Buscamos por la izquierda del arbol
	} else if ( val < root -> v ) {
		root-> left = erase(root -> left, val );
		// Balanceamos el hijo izquierdo una vez se haya borrado "val"
		root-> left = balance(root-> left);
		
	//Buscamos por la derecha del arbol
	} else if ( val > root -> v ) {
		root-> right = erase(root -> right, val );
		// Balanceamos el hijo derecho una vez se haya borrado "val"
		root-> right = balance(root-> right);
		
	// Cuando encontremos el "val" en el arbol
	} else if ( val == root -> v ) {
		// Buscamos como sustituto al "val" el INORDER SUCCESOR de "val"
		
		// En caso de tener hijo derecho como null entonces se toma el
		// INORDER PREDESECCESOR. Esto ocurre porque en caso de haber un
		// PREDESECCESOR  "n2"
		//           /
		//         val
		//       /   \
		//     n1     null
		//      \ 
		//       n2 
		//
		// Ya dicho arbol no es AVL.
 		if ( root -> right == nullptr ) {
			return root -> left;
			
		// Si al irnos a derecha, luego ir todo lo que podemos a izquierda
		// tenemos el caso sencillo
		//            /
		//          val
		//       /      \
		//     n1        n3
		//      \      /   \
		//       n2  null   n4
		//
		// Se toma directamente el hijo derecho de "val" y realizamos las 
		// respectivas asignaciones de hijos izquierdo a la nueva raiz.
		} else if ( root -> right -> left == nullptr ){
			root -> right -> left = root -> left; 
			return root -> right;
			
		// Ya en caso de tener una subarbol para el succesor mas desarrolado
		// buscamos dicho succesor y tomamos un balanceo del hijo derecho.
		} else {
			root -> v = inorder_succesor(root -> right);
			root -> right = balance(root -> right);
		}
	}
	return balance(root);
}

// Mostrar el arbol por pantalla de manera vertical.
void draw(AVLNode *p, int ind) {
	if (p != nullptr) {
		draw(p->right, ind+1);
		for (int i=0 ; i<ind ; i++)
			cout << "\t\t";
		cout << "(v:" << p->v << " ,h:"
			     << height(p) << " ,b:" << balance_factor(p) << ")"<< endl;
		draw(p->left, ind+1);
	}
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

	AVLNode *root = nullptr;
	// Generamos un arbol random, o usar "r = i;" para tener un secuencia.
	for(int i =0 ; i < 20 ; i++) {
		int r = rand() % 99;
		root = insert(root, r);
	}
	
	// Mostramos el arbol generado anteriormente.
	draw(root, 0);
	cout << "\n\n\n\n" << endl ;
	
	// Interactuamos con el usuario en querer Delete o Insert 
	int op, node;
	cout << "0 -> Insert,  1 -> Delete, AnyNumber -> Exit: ";
	cin >> op;
		
	while ( op == 1 || op == 0 ) {
		if( op == 0 ) {
			cout << "Insert: "; cin >> node;
			root = insert(root, node);
		} else {
			cout << "Delete: "; cin >> node;
			root = erase(root, node);
		}
			
		draw(root, 0);
		cout << endl << endl;	
		cout << "0 -> Insert,  1 -> Delete, AnyNumber -> Exit: ";
		cin >> op;
	}
		
	return EXIT_SUCCESS;
}
