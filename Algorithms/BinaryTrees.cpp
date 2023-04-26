#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct TreeNode {
	public:
	string value;
	TreeNode *left,
			 *right;
	TreeNode (string s) {
		value = s;
		left = NULL;
		right = NULL;
	}
	TreeNode (string s, TreeNode *l, TreeNode *r) {
		value = s;
		left = l;
		right = r;
	}
};


void preorder(TreeNode *n) {
	if (n == NULL)
		return;
	cout << n->value << " ";
	preorder(n->left);
	preorder(n->right);
}

void inorder(TreeNode *n) {
	if (n == NULL)
		return;
	inorder(n->left);
	cout << n->value << " ";
	inorder(n->right);
}

void postorder(TreeNode *n) {
	if (n == NULL)
		return;
	postorder(n->left);
	postorder(n->right);
	cout << n->value << " ";
}


int main() {

	TreeNode *T;
	T = new TreeNode("*",
			new TreeNode("+",
				new TreeNode("23"),
				new TreeNode("5")),
			new TreeNode("/",
				new TreeNode("100"),
				new TreeNode("5")
			)
		);

	preorder(T);
	cout << endl;
	inorder(T);
	cout << endl;
	postorder(T);
	cout << endl;

	return 0;
}
