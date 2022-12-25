#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
 
using namespace std;

#define MAX_PRIORITY 100000

struct TreapNode {
	int key,
		priority;
	TreapNode *left,
		   *right;
	TreapNode(int k) {
		key = k;
		priority = rand() % MAX_PRIORITY;
		left = NULL;
		right = NULL;
	}
};

class Treap {

	TreapNode *root;

	TreapNode* find(TreapNode*, int);
	TreapNode* insert(TreapNode*, int);
	TreapNode* erase(TreapNode*, int);

	TreapNode* rotateLeft(TreapNode*);
	TreapNode* rotateRight(TreapNode*);
	TreapNode* lowestPriority(TreapNode*);
	TreapNode* restructure(TreapNode*);

	public:
	
	Treap() {
		root = NULL;
	}
	bool contains(int);
	void insert(int);
	void erase(int);

	void draw() {
		draw(root, 0);
	}
	void draw(TreapNode *p, int ind) {
		if (p != NULL) {
			draw(p->right, ind+1);
			for (int i=0 ; i<ind ; i++)
				cout << "\t\t";
			cout << "(" << p->key << ", "
			     << p->priority << ")" << endl;
			draw(p->left, ind+1);
		}
	}
};

bool Treap::contains(int k) {
	return find(root, k) != NULL;
}

TreapNode* Treap::find(TreapNode *p, int k) {
	if (p == NULL)
		return NULL;
	if (p->key < k)
		return find(p->right, k);
	if (p->key > k)
		return find(p->left, k);
	return p;
}

void Treap::insert(int k) {
	root = insert(root, k);
}

TreapNode* Treap::insert(TreapNode *p, int k) {
	if (p == NULL) {
		p = new TreapNode(k);
		return p;
	} else if (p->key < k) {
		p->right = insert(p->right, k);
	} else if (p->key > k) {
		p->left = insert(p->left, k);
	}
	return restructure(p);
}

void Treap::erase(int k) {
	// TODO
}

TreapNode* Treap::erase(TreapNode *p, int k) {
	// TODO
	return NULL;
}

TreapNode* Treap::rotateLeft(TreapNode *p) {
	TreapNode* q = p->right;
	p->right = q->left;
	q->left = p;
	return q;
}

TreapNode* Treap::rotateRight(TreapNode *p) {
	TreapNode* q = p->left;
	p->left = q->right;
	q->right = p;
	return q;
}

TreapNode* Treap::lowestPriority(TreapNode *p) {
	TreapNode *q = p;
	if (p->left != NULL  &&  p->left->priority < q->priority)
		q = p->left;
	if (p->right != NULL && p->right->priority < q->priority)
		q = p->right;
	return q;
}

TreapNode* Treap::restructure(TreapNode *p) {
	TreapNode *q = lowestPriority(p);
	if (q == p->left)
		return rotateRight(p);
	if (q == p->right)
		return rotateLeft(p);
	return p;
}

int main() {

	srand(time(NULL));

	Treap T;
	for (int i=0 ; i<10 ; i++) {
		T.insert(i);
	}
	T.draw();

	return 0;
}
