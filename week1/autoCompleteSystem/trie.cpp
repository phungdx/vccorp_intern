/****************************
 * Matthew Wilkerson        *
 * CECS 503-50              *
 * Project 1                *
 ****************************/

//trie.cpp

#include <iostream>
#include <string>
#include "trie.h"
#include "node.h"

void Trie::insert(std::string data) //constructions trie tree structure
{
	Node* tmp = root;
	char cstr[data.length()];
	
	data.copy(cstr, data.length()); //create char array containing data from string object
	for (int i = 0; i < data.length(); i++)
	{
		if (tmp->child[static_cast<int>(cstr[i])] != NULL) //walk ptr through struct, preventing duplicate nodes (prefix)
			tmp = tmp->child[static_cast<int>(cstr[i])];
		else
		{
			tmp->child[static_cast<int>(cstr[i])] = new Node(); //create new node
			tmp = tmp->child[static_cast<int>(cstr[i])];
			tmp->setChar(cstr[i]); //insert char in new node
		}
	}
	tmp->setWord(true); //mark word
}

void Trie::print_tree(Node* root, std::string data, std::string str) //method that prints query options to completing the prefix
{
	for (int i = 0; i < 128; i++) //loops through all 128 pointers in node to check if there's a child
	{
		Node* adv = root;
		if (adv->child[i] != NULL) //child exists
		{
			adv = adv->child[i]; //advance pointer
			str += adv->getChar(); //append char to end of prefix
			if (adv->isWord()) //if point at end of word, print word
			{
				if (this->getSpace() == true) //if the user's search query contained a space, print the search query minus prefix then print word
					std::cout << this->getNo_prefix();
				std::cout << str << std::endl;
			}
			print_tree(adv, str); //recursive call to keep moving down tree
		}
		str = data; //reset prefix string
	}
}

void Trie::print_tree(Node* root, std::string str) //overloaded function for recursive calls
{
	std::string str_tmp = str;

	for (int i = 0; i < 128; i++)
	{
		Node* adv = root;
		if (adv->child[i] != NULL)
		{
			adv = adv->child[i];
			str += adv->getChar();
			if (adv->isWord())
			{
				if (this->getSpace() == true)
					std::cout << this->no_prefix;
				std::cout << str << std::endl;
			}
			print_tree(adv, str);
		}
		str = str_tmp;
	}
}

void Trie::search(std::string data) //wrapper for function that completes the prefix, generating search options
{
	Node* tmp = root;
	char cstr[data.length()];

	data.copy(cstr, data.length(), 0); 
	for (int i = 0; i < data.length(); i++) //for loop advances point through tree structure stopping at node containing last char in user's search prefix
	{
		if (tmp->child[static_cast<int>(cstr[i])] == NULL) //lets user know if prefix not in dictionary (next char not a child)
		{
			std::cout << "error:  string not found" << std::endl;
			return;
		}
		else
			tmp = tmp->child[static_cast<int>(cstr[i])];
			
		if (tmp->getChar() != cstr[i]) //lets user know if prefix not in dictionary (char does not match corresponding char in prefix)
		{
			std::cout << "error:  string not found" << std::endl;
			return;
		}
	}
	std::string str = data; //copy user's query prefix into generic string used for appending operations to complete query prefix in print_tree method
	print_tree(tmp, data, str);	//passes pointer that has advanced to last char in query prefix to printing method
}

void Trie::is_space(std::string data) //checks user query string for space char and sets bool space appropriately
{
	char cstr[data.length()];

	data.copy(cstr, data.length());
	for (int i = 0; i < data.length(); i++)
	{
		if (cstr[i] == ' ')
		{
			space = true;
			return;
		}
		else
			continue;
	}
}	

std::string Trie::break_string(std::string data) //isolates and returns prefix only, if query string contains a space
{
	char cstr[data.length()];
	std::string str;
	data.copy(cstr, data.length());

	for (int i = data.length(); i-- > 0;) //reverse loop
	{
		if (cstr[i] == ' ') //if space, stop and return generic string
			 break;
		else
			str.insert(str.begin(),cstr[i]); //copies chars in generic string begining at the last character until loop encounters a space
	}
	return str; //returns the prefix only
}

void Trie::remove_prefix(std::string data) //method removes the user's query prefix and copies to no_prefix attribute; print to screen along with
												//completed words to offer user search options
{
	char cstr[data.length()];
	data.copy(cstr, data.length());

	for (int i = data.length(); i-- > 0;) //reverse loop
	{
		if (cstr[i] == ' ') //break loop when space encountered
			break;
		else
			cstr[i] = '\0'; //each full iteration, last char changed to null char
	}
	no_prefix = cstr; //copies chars up to first null char into no_prefix string
}