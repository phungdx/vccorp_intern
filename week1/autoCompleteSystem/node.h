/****************************
 * Matthew Wilkerson        *
 * CECS 503-50              *
 * Project 1                *
 ****************************/

//node.h

#ifndef NODE_H
#define NODE_H

#include <iostream>

// Cấu trúc của 1 node trong Trie
class Node
{
	friend class Trie;
private:
	char c;
	bool word; // đánh dấu node kết thúc 1 từ.
	Node* child[128]; //chỉ vào các node con; mỗi node con là 1 kí tự trong bảng ASCII (0-127)
public:
	Node();
	~Node() {}
	void setWord(int boo) {this->word = boo;} 
	bool isWord() {return this->word;}
	void setChar(char ch) {this->c = ch;}
	char getChar() const {return this->c;}
};

#endif