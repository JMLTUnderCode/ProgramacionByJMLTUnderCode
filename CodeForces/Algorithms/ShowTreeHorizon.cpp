#include

void gotoxy(int x,int y){  
    HANDLE hcon;  
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD dwPos;  
    dwPos.X = x;  
    dwPos.Y= y;  
    SetConsoleCursorPosition(hcon,dwPos);  
}

int auxX = 0;
void mostrarArbol(AVLNode *tree, int auxY) {

    if(tree == nullptr) {
    	return;	
	} else {
		auxX += 7;

    	mostrarArbol(tree -> left, auxY+2);

		// 5+auxX-auxY, 10 + auxY  o   10+auxX-auxY, 15 + auxY
    	gotoxy(auxX-auxY-5 , 5+auxY);//posiciona el nodo segun sus variables en X y en Y
		
		//cout << tree -> v << endl << endl;
		//cout << tree -> v << " (" << balance_factor(tree) << ")" << endl << endl;
		cout << tree -> v << "-" << height(tree) << endl << endl;
		
	
    	mostrarArbol(tree -> right,auxY+2);
	}
}
