//node.cpp
#include "node.h"

Node::Node() //Khởi tạo node
{
	this->setChar('\0'); // biểu thị kí tự null
	this->setWord(false);
	for (int i = 0; i < 128; i++)
		this->child[i] = NULL; // khởi tạo các node con
}

