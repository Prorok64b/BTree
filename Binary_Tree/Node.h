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
	Node* get_samllest();
	Node* get_largest();

	// Private Methods
private:
	Node* search_for(int new_id, int auto_create); // search suitable position for 'new_id'
	Node* get_min(Node* root);
	Node* get_max(Node* root);
	Node* delete_node(Node* node, int n_id);
};