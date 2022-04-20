// trie.cpp

#include <iostream>
#include <string>
#include "trie.h"
#include "node.h"

void Trie::insert(std::string data) // thêm word vào trie
{
	Node *tmp = root;
	char cstr[data.length()];

	data.copy(cstr, data.length()); // tạo mảng char chứa data
	for (int i = 0; i < data.length(); i++)
	{
		// kiểm tra node con tương ứng
		//  nếu tồn tại rồi thì chuyển tiếp xuống bên dưới
		if (tmp->child[static_cast<int>(cstr[i])] != NULL)
			tmp = tmp->child[static_cast<int>(cstr[i])];
		else
		{
			// tạo mới nếu chưa tồn tại
			tmp->child[static_cast<int>(cstr[i])] = new Node();
			tmp = tmp->child[static_cast<int>(cstr[i])];
			tmp->setChar(cstr[i]); // set giá trị cho node con
		}
	}
	tmp->setWord(true); //đánh dấu kết thúc từ
}


// nạp chồng với hàm print_tree bên dưới, gọi đệ quy để in ra tất cả các gợi ý
void Trie::print_tree(Node *root, std::string data, std::string str) // method that prints query options to completing the prefix
{
	for (int i = 0; i < 128; i++) // loops through all 128 pointers in node to check if there's a child
	{
		Node *adv = root;
		if (adv->child[i] != NULL) // child exists
		{
			adv = adv->child[i];   // advance pointer
			str += adv->getChar(); // append char to end of prefix
			if (adv->isWord())	   // if point at end of word, print word
			{
				if (this->getSpace() == true) // if the user's search query contained a space, print the search query minus prefix then print word
					std::cout << this->getNo_prefix();
				std::cout << str << std::endl;
			}
			print_tree(adv, str); // recursive call to keep moving down tree
		}
		str = data; // reset prefix string
	}
}


// gọi kiểm tra prefix đưa vào và gọi hàm print_tree bên trên.
void Trie::print_tree(Node *root, std::string str)
{
	std::string str_tmp = str;

	// duyệt qua từng node con của node root đưa vào
	for (int i = 0; i < 128; i++)
	{
		Node *adv = root;
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

// tìm kiếm gợi ý cho prefix đưa vào
void Trie::search(std::string data)
{
	Node *tmp = root;
	char cstr[data.length()];

	data.copy(cstr, data.length(), 0);

	// duyệt qua từng kí tự prefix đầu vào
	for (int i = 0; i < data.length(); i++)
	{

		// nếu prefix không trong trie (kí tự tiếp theo không phải node con)
		if (tmp->child[static_cast<int>(cstr[i])] == NULL)
		{
			std::cout << "error:  string not found" << std::endl;
			return;
		}
		else
			tmp = tmp->child[static_cast<int>(cstr[i])];


		// nêu prefix không trong trie (kí tự trong node hiện tại không tương thích)
		if (tmp->getChar() != cstr[i])
		{
			std::cout << "error:  string not found" << std::endl;
			return;
		}

	}
	// copy prefix để thực hiện add thêm kí tự
	std::string str = data;
	print_tree(tmp, data, str); // gọi hàm tìm gợi ý
}


// kiểm tra input user có dấu cách không, và set giá trị cho thuộc tính space
void Trie::is_space(std::string data)
{
	char cstr[data.length()];

	data.copy(cstr, data.length());
	// duyệt lần lượt
	for (int i = 0; i < data.length(); i++)
	{
		// duyệt lần lượt
		if (cstr[i] == ' ')
		{
			// nếu gặp dấu cách thì set giá trị của space và dừng
			space = true;
			return;
		}
		else
			continue;
	}
}


// trả ra phần prefix trong input
std::string Trie::break_string(std::string data)
{
	char cstr[data.length()];
	std::string str; // lưu prefix
	data.copy(cstr, data.length());

	for (int i = data.length(); i-- > 0;) // vòng lặp ngược
	{
		if (cstr[i] == ' ') // dừng khi gặp dấu cách
			break;
		else
			// copy từng kí tự ở cuối string input user chèn vào đầu biến str
			str.insert(str.begin(), cstr[i]);
	}
	return str; // trả về prefix
}


// lấy phần đã hoàn thiện trong input (ngoài phần prefix) nếu như có nhiều hơn 1 từ (có dấu cách)
void Trie::remove_prefix(std::string data)
{
	char cstr[data.length()];
	data.copy(cstr, data.length());

	for (int i = data.length(); i-- > 0;) // vòng lặp ngược
	{
		if (cstr[i] == ' ') // dừng khi gặp dấu cách
			break;
		else
			cstr[i] = '\0'; // convert kí tự thường về kí tự kết thúc 1 string.
	}
	no_prefix = cstr; // lưu phần đã hoàn thiện trong input vào thuộc tính no_prefix
}