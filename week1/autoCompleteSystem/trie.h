/****************************
 * Matthew Wilkerson        *
 * CECS 503-50              *
 * Project 1                *
 ****************************/

//trie.h

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include "node.h"

class Trie
{
	friend class Node;
private:
	bool space; //true - string that stores user query contains space
	std::string no_prefix; //if space in string exists - string that stores user query minux prefix used for query completion
	Node* root;
public:
	Trie() {root = new Node(); this->space = false;}
	~Trie() {}
	void is_space(std::string data); //searches user's query string for space and sets bool space appropriately
	bool getSpace() {return space;}
	void insert(std::string data); //builds trie tree struction
	void search(std::string data); //wrapper for main auto-completion method; advances to last char in user's prefix
	void print_tree(Node* root, std::string data, std::string str); //prints suggested queries
	void print_tree(Node* root, std::string str); //overloaded print_tree method used for recursion
	void remove_prefix(std::string data); //removes the prefix (if space in string)
	std::string getNo_prefix() {return no_prefix;}
	std::string break_string(std::string); //returns only prefix (if space in string) used in search and print_tree methods
};

#endif
