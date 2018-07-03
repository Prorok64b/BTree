#include <iostream>
#include "Node.h"

// Constructors

Node::Node()
{
	id = 0;
	left = nullptr;
	right = nullptr;
}

Node::~Node()
{
}

// Public Methods

Node* Node::get(int n_id)
{
	Node* _parent = NULL;
	Node* my_node = search(this, &_parent, n_id);

	if(my_node && my_node->id == n_id) return my_node;

	return nullptr;
}

bool Node::push(int new_id)
{
	Node* _parent = NULL;
	Node* last_node = search(this, &_parent, new_id);

	if (last_node)
	{
		if (last_node->id == 0)
		{
			last_node->id = new_id;
		}
		else if (new_id > last_node->id)
		{
			last_node->right = new Node();
			last_node->right->id = new_id;
		}
		else if (new_id < last_node->id)
		{
			last_node->left = new Node();
			last_node->left->id = new_id;
		}
	}
	
	return true;
}

bool Node::remove(int n_id) // need fixes
{
	Node* parent = NULL;
	Node* my_node = search(this, &parent, n_id);

	if (!my_node || my_node->id != n_id) return false;

	Node* repl_node = nullptr;

	if (!my_node->left && !my_node->right)
	{
		if (my_node->id > parent->id)
			parent->right = nullptr;
		else if (my_node->id < parent->id)
			parent->left = nullptr;

		delete my_node;

		return true;
	}
	else if(my_node->left || my_node->right)
	{
		if (my_node->id > parent->id)
		{
			// we are located inside the right sub-tree (find the smallest node)
			repl_node = my_node->right->get_smallest();
			Node* repl_parent = get_parent_for(repl_node->id);

			parent->right = repl_node;

			Node* largest = repl_node->get_largest();
			if(largest)
				largest->right = my_node->right;

			Node* smallest = repl_node->get_smallest();
			if(smallest)
				smallest->left = my_node->left;

			if (repl_parent)
				repl_parent->left = nullptr;
		}
		else if (my_node->id < parent->id)
		{
			// we are located inside the left sub-tree (find the largest node)
			repl_node = my_node->left->get_largest();
			Node* repl_parent = get_parent_for(repl_node->id);

			parent->left = repl_node;

			Node* largest = repl_node->get_largest();
			if (largest)
				largest->right = my_node->right;

			Node* smallest = repl_node->get_smallest();
			if (smallest)
				smallest->left = my_node->left;

			if (repl_parent)
				repl_parent->right = nullptr;
		}

		delete my_node;
	}

	return true;
}

Node* Node::get_smallest()
{
	if (this && this->left)
	{
		Node* temp = get_min(this);
		return temp->left ? temp->left : temp;
	}

	return this;
}

Node* Node::get_largest()
{
	if (this && this->right)
	{
		Node* temp = get_max(this);
		return temp->right ? temp->right : temp;
	}

	return this;
}

// Private methods

Node* Node::search(Node* node, Node** parent, int n_id) // if node with n_id isn't found, return parent node
{
	if (node && node->id == n_id || node->id == 0) return node;
	else if (node)
	{
		if (n_id > node->id && node->right)
		{
			*parent = node;
			return search(node->right, parent, n_id);
		}
		else if (n_id < node->id && node->left)
		{
			*parent = node;
			return search(node->left, parent, n_id);
		}
	}

	return node;
}

Node* Node::get_parent_for(int n_id)
{
	Node* parent = NULL;
	Node* _my_node = search(this, &parent, n_id);

	return parent;
}

Node* Node::get_min(Node* root)
{
	if (!root) return nullptr;
	if (!root->left) return root;

	get_min(root->left);
}

Node* Node::get_max(Node* root)
{	
	if (!root) return nullptr;
	if (!root->right) return root;

	get_max(root->right);
}

void destroy_tree(Node* root)
{
	if (root != NULL)
	{
		destroy_tree(root->left);
		destroy_tree(root->right);
		delete root;
	}
}