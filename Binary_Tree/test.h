#pragma once

#include <iostream>
#include "Node.h"

void TEST_LOG(const char* action, int id)
{
	std::cout << action << " " << id << std::endl;
}

void test()
{
	Node* root = new Node();

	for (int i = 5; i < 15; i++)
	{
		if (root->push(i)) TEST_LOG("pushed ", i);
		else TEST_LOG("pushing failed ", i);
	}

	for (int i = 5; i < 15; i++)
	{
		if (root->remove(i)) TEST_LOG("removed", i);
		else TEST_LOG("removing failed", i);
	}

	delete root;
}