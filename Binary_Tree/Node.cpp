#include <iostream>
#include "Node.h"

Node* search_buf = nullptr;  // is used for saving temporary data during search

const int AUTO_CREATE = 1;
const int NO_AUTO_CREATE = 0;
// Constructors

Node::Node()
{
	id = 0;
	left = nullptr;
	right = nullptr;
}

Node::~Node()
{
	std::cout << "destroyed node: " << id << std::endl;

	if (this->left)
		delete this->left;
	if (this->right)
		delete this->right;
}

// Public Methods

Node* Node::get(int n_id)
{
	search_buf = this;
	Node* my_node = search_for(n_id, NO_AUTO_CREATE);

	if(my_node && my_node->id == n_id) return my_node;

	return nullptr;
}

bool Node::push(int new_id)
{
	search_buf = this;
	Node* new_node = search_for(new_id, AUTO_CREATE);

	if (new_node->id == 0) new_node->id = new_id;
	if (new_node->id == new_id) return true;
	
	return false;
}

bool Node::remove(int n_id) // need fixes
{
	Node* my_node = get(n_id);
	if (!my_node) return false;

	Node* repl_node = nullptr;

	if (!my_node->left && !my_node->right)
	{
		delete my_node;
	}
	else if(my_node->left || my_node->right)
	{
		if (my_node->id > this->id)
		{
			// we are located in right sub-tree (find the smallest node)
			repl_node = my_node->right->get_samllest();
			
			Node* new_parent = nullptr;
			if (repl_node->left) new_parent = repl_node->right->get_samllest();
			if (new_parent) new_parent->left = repl_node->left;
			
			repl_node->left = nullptr;
			my_node = repl_node;
		}
		else if (my_node->id < this->id)
		{
			// we are located in left sub-tree (find the largest node)
			repl_node = my_node->left->get_largest();

			if (repl_node->left) repl_node->left->get_largest()->right = repl_node->right;

			repl_node->left = nullptr;
			my_node = repl_node;
		}
	}

	return (get(n_id) ? 1 : 0);
}

Node* Node::get_samllest()
{
	return get_min(this);
}

Node* Node::get_largest()
{
	return get_max(this);
}

// Private methods

Node* Node::search_for(int new_id, int auto_create)
{
	if (search_buf && search_buf->id == 0)
	{
		search_buf->id = new_id;
		return search_buf;
	}
	else if(search_buf && search_buf->id == new_id)
	{
		return search_buf;
	}
	else
	{
		if(new_id > search_buf->id)
		{
			if (!search_buf->right)
			{
				if (!auto_create) return nullptr;
				search_buf->right = new Node();
				return search_buf->right;
			}
			else
			{
				search_buf = search_buf->right;
				search_buf->search_for(new_id, auto_create);
			}
		}
		else if(new_id < search_buf->id)
		{
			if (!search_buf->left)
			{
				if (!auto_create) return nullptr;
				search_buf->left = new Node();
				return search_buf->left;
			}
			else
			{
				search_buf = search_buf->left;
				search_buf->search_for(new_id, auto_create);
			}
		}

		return search_for(new_id, auto_create);
	}

	return nullptr;
}

Node* Node::get_min(Node* root)
{
	if (!root) return nullptr;
	if (root && !root->left) return root;

	get_min(root->left);
}

Node* Node::get_max(Node* root)
{	
	if (!root) return nullptr;
	if (root && !root->right) return root;

	get_max(root->right);
}