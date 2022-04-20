#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include "node.h"

class Trie
{
	friend class Node;
private:
	bool space; // đánh dấu xem input có dấu cách không
	std::string no_prefix; // lưu phần đã hoàn thiện (ngoài prefix ra) của input đầu vào, nếu input có nhiều từ.
	Node* root; // node gốc
public:
	Trie() {root = new Node(); this->space = false;} // khởi tạo trie
	~Trie() {}
	void is_space(std::string data); // kiểm tra input user có dấu cách không, và set giá trị thuộc tính space
	bool getSpace() {return space;} // lấy giá trị space
	void insert(std::string data); // thêm word vào trie
	void search(std::string data); // tìm kiếm gợi ý cho prefix đưa vào

	// nạp chồng với hàm print_tree bên dưới, gọi đệ quy để in ra tất cả các gợi ý
	void print_tree(Node* root, std::string data, std::string str);
	
	// gọi kiểm tra prefix đưa vào và gọi hàm print_tree bên trên.
	void print_tree(Node* root, std::string str); // gọi hàm 

	// lấy phần đã hoàn thiện trong input (ngoài phần prefix) nếu như có nhiều hơn 1 từ (có dấu cách)
	void remove_prefix(std::string data);

	// trả ra phần đã hoàn thiện trong input
	std::string getNo_prefix() {return no_prefix;}

	// trả ra phần prefix trong input
	std::string break_string(std::string);
};

#endif
