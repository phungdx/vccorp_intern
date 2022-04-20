//main
#include <iostream>
#include <string>
#include <fstream>
#include "node.cpp"
#include "trie.cpp"

int main(int argc, char const *argv[])
{
	std::string data;
	std::fstream dictionary;
	Trie complete_query;

	dictionary.open("dictionary.txt", std::fstream::out); //read dictionary file into trie tree structure
	if (dictionary.is_open())
	{	
		while (dictionary)
		{
			dictionary >> data;
			complete_query.insert(data);
		}
	}	
	else
	{
		std::cout << "error:  file not open." << std::endl;
		return -1;
	}
	dictionary.close();
	data.clear(); //clear string variable used for file input; string variable will read in user input
	std::cout << "enter search query:" << std::endl;
	std::getline(std::cin, data); //getline used over std::cin to catch spaces
	complete_query.is_space(data); //checks whether there's a space in user query
	std::cout << "your search options are:  " << std::endl;
	if (complete_query.getSpace() == true) //if a space exists, remove prefix and pass prefix only to search method
	{
		complete_query.remove_prefix(data);
		complete_query.search(complete_query.break_string(data));
	}
	else //if no method exists, pass user's query to search method to auto-complete the query
		complete_query.search(data);
	return 0;
} 	
