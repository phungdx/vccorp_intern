#include <iostream>
#include<vector>
#include<fstream>
using namespace std;


// cấu tạo 1 node trong trie
class TrieNode {
    public:
        // các node con của 1 node
	    vector<TrieNode*> children;

        // đánh dấu node đó kết thúc 1 word
	    bool isWordEnd;

        TrieNode(){
            isWordEnd = false;
            children.resize(26, nullptr); // tạo ra 26 node con giá trị ban đầu là null
        }
};

class Trie{
    private:
        TrieNode* root; // gốc của cây

    public:
        Trie(){
            root = new TrieNode(); // khởi tạo gốc cây
        }

        // chèn 1 node (word) mới vào cây
        void insert(string word){
            // node hiện tại
            TrieNode* curr = root;

            for(int i = 0; i < word.size(); ++i){
                // xét node con tại vị trí tương ứng, tạo mới nếu chưa được khởi tạo
                if(curr->children[word[i] - 'a'] == nullptr) curr->children[word[i] - 'a'] = new TrieNode();
                curr = curr->children[word[i] - 'a']; // trỏ xuống con trỏ hiện tại để xét tiếp
            }

            curr->isWordEnd = true; // đánh dấu kết thúc từ
        }

        // kiểm tra 1 node là node lá hay không (không có con)
        bool isLastNode(TrieNode* curr){
            for(auto child: curr->children){
                // nếu có con
                if(child){
                    return 0;
                }
            }
            return 1; // nếu ko có node con
        }

        // đệ quy tìm từ gợi ý
        void suggestionsRec(TrieNode* root, string prefix){
            // base case: nếu node hiện tại là kết thúc từ --> ta được 1 gợi ý, in ra
            if(root->isWordEnd){
                cout << prefix << '\n';
            }

            for(int i = 0; i < 26; ++i){
                // kiểm tra node con tương ứng, nếu tồn tại thì đệ quy tìm tiếp bên dưới
                if(root->children[i]){
                    char addition = i + 'a';
                    suggestionsRec(root->children[i], prefix + addition);
                }
            }
        }

        // in ra tất cả các gợi ý hợp lệ
        int printAutoSuggestions(const string query){
            TrieNode* curr = root;
            for(int i = 0; i < query.size(); ++i){
                // nếu node hiện tại ko có con ở vị trí tương ứng, dừng luôn
                if(!curr->children[query[i] - 'a']){
                    return 0;
                }
                // nếu có thì đi xuống tiếp
                curr = curr->children[query[i] - 'a'];
            }

            // node hiện tại có phải node lá không
            if(isLastNode(curr)){
                cout << query << '\n';
                return -1;
            }

            // gọi hàm tìm gợi ý
            suggestionsRec(curr, query);
            return 1;


        }
};



int main()
{
	// Trie* root = new Trie();
	// root->insert("hello");
    // root->insert("dog");
    // root->insert("hell");
    // root->insert("cat");
    // root->insert("a");
    // root->insert("hel");
    // root->insert("help");

    // string prefix = "hello";

    // for(int i = 0; i < prefix.size(); ++i){
    //     if(prefix[i] >= 'A' && prefix[i] <= 'Z'){
    //         prefix[i] = prefix[i] + 32;
    //     }
    // }

	// int comp = root->printAutoSuggestions(prefix);

	// if (comp == -1)
	// 	cout << "No other strings found with this prefix\n";

	// else if (comp == 0)
	// 	cout << "No string found with this prefix\n";

    string data;
    fstream dictionary;
    Trie* myTrie = new Trie();

    dictionary.open("data/dictionary.txt", fstream::in);
    if(dictionary.is_open()){
        while(dictionary){
            dictionary >> data;
            myTrie->insert(data);
        }
    }

    else{
        cout << "Error : file not open" << '\n';
        return -1;
    }

    dictionary.close();
    data.clear();

    cout << "enter search query" << '\n';
    getline(cin, data);
    for(int i = 0; i < data.size(); ++i){
        if(data[i] >= 'A' && data[i] <= 'Z'){
            data[i] = data[i] + 32;
        }
    }
    cout << "your search options are: " << '\n';
    int comp = myTrie->printAutoSuggestions(data);

	if (comp == -1)
		cout << "No other strings found with this prefix\n";

	else if (comp == 0)
		cout << "No string found with this prefix\n";

	return 0;
}
