#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

// Classes

class List {
	
	class NodeList {
		 
		public:
		int value;
		NodeList *next;
			
		// Constructor of NodeList
		NodeList() {
			next = NULL;
		}
	};
	
	NodeList *head;
	int n;
	
	public:
		
	// Constructor of List
	List() {
		n = 0;
		head = NULL;
	}
	
	// Funtions of Class
	int  size();
	int  get(int);
	void append(int);
	void insert(int, int);
	void erase(int);
};

int List :: size() {
	return n;
}

// Precondicion: 0 <= pos < n
int List :: get(int pos) {
	int ind = 0;
	NodeList *curr;
	curr = head;
	while ( curr != NULL ) {
		if ( ind == pos ) {
			return curr->value;
		}
		curr = curr->next;
		ind++;
	}
	return -1;
}

void List :: append(int value) {
	insert(value, n);
}

void List :: insert(int value, int pos) {
	/*
		TAREA: implementar esta funcion usando solo
		       prev (eliminando la variable curr)
	*/
	int ind = 0;
	NodeList *prev, *temp;
	temp = head;
	prev = NULL;
	n++;
	if (head == NULL) {
		head = new NodeList();
		head->value = value;
		return;
	}
	while (head != NULL) {
		if (ind == pos) {
			temp = new NodeList();
			temp->value = value;
			temp->next  = prev->next;
			if (prev == NULL) {
				head = temp;
			} else {
				prev->next = temp;
			}
			return;
		}
		prev = temp;
		temp = temp->next;
		ind++;
	}
	temp = new NodeList();
	temp->value = value;
	temp->next  = prev->next;
	prev->next  = temp;
}

void List :: erase( int pos ) {
	int ind = 0;
	NodeList *curr, *prev;
	curr = head;
	prev = NULL;
	while ( curr != NULL ) {
		if ( ind == pos ) {
			if ( prev == NULL ) {
				head = curr->next;	
			} else {
				prev->next = curr->next;
			}
			n--;
			return;
		}
		prev = curr;
		curr = curr->next;
		ind++;
	}
}

int main() {
	
	List L;
	
	for ( int i = 0; i < 10; i++ ) {
		L.append(i);
	}
	L.erase(4);
	L.insert(99, 4);
	L.insert(-99, L.size()-1);
	cout << "Size: " << L.size() << endl;
	
	for ( int i = 0; i < L.size(); i++ ) {
		cout << "Elemento #" << i << ": " << L.get(i) << endl;
	}
	return 0;
}
