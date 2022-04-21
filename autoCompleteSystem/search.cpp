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

	dictionary.open("dictionary.txt", std::fstream::in); // mở file data
	if (dictionary.is_open())
	{	
		while (dictionary)
		{
			dictionary >> data; // đọc dữ liệu từng dòng vào biến data
			complete_query.insert(data); // insert data vào trie
		}
	}
	else
	{
		std::cout << "error:  file not open." << std::endl;
		return -1;
	}
	dictionary.close();
	data.clear(); // xóa dữ liệu để lưu data do user nhập vào
	std::cout << "enter search query:" << std::endl;
	std::getline(std::cin, data);
	complete_query.is_space(data); // kiểm tra có space trong input của user
	std::cout << "your search options are:  " << std::endl;
	if (complete_query.getSpace() == true) // kiểm tra input có dấu cách (nhiều hơn 1 word)
	{
		complete_query.remove_prefix(data); // lấy phần đã hoàn thiện trong input lưu vào thuộc tính no_prefix

		// tìm kiếm với phần prefix trong input (break_string() thực hiện trả phần prefix trong input)
		complete_query.search(complete_query.break_string(data));
	}
	else // nếu không có dấu cách thì pass thằng input vào để search
		complete_query.search(data);
	return 0;
} 	
