#pragma once

class Node
{
	// Constructors
public:
	Node();
	~Node();

	// Public Members
public:
	Node* left;
	Node* right;
	int	  id;

	// Public Methods
public:
	Node* get(int n_id);
	bool  push(int new_id);
	bool  remove(int n_id);
	Node* get_smallest();
	Node* get_largest();

	// Private Methods
private:
	Node* search(Node* node, Node** parent, int n_id); // search suitable position for 'new_id'
	Node* get_parent_for(int n_id); // return parent node for node with id: n_id
	Node* get_min(Node* root);
	Node* get_max(Node* root);
};

void destroy_tree(Node* root);