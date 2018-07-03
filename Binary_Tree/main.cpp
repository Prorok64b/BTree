#include <iostream>
#include "Node.h"

int main()
{
	for (;;) {
		Node* root = new Node();

		root->push(2);
		root->push(4);
		root->push(3);
		root->push(6);
		root->push(5);
		root->push(7);

		root->push(-2);
		root->push(-1);
		root->push(-5);
		root->push(-7);
		root->push(-4);
		root->push(1);


		if(!root->remove(4)) break;
		if(!root->remove(-2)) break;

		destroy_tree(root);
	}

	system("pause");
	
	return 0;
}