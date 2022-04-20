//node.cpp
#include "node.h"

Node::Node() //Node constructor
{
	this->setChar('\0');
	this->setWord(false);
	for (int i = 0; i < 128; i++)
		this->child[i] = NULL;
}

