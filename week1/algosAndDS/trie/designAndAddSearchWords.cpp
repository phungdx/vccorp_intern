#include<iostream>
#include<vector>
using namespace std;


class WordDictionary {
public:
    // cấu trúc 1 node
    struct node{
        // các node con
        vector<node*> child;
        // đánh dấu kết thúc từ
        bool isEnd = false;

        // khởi tạo
        node(){
            child.resize(26, nullptr);
            isEnd = false;
        }
    };

private:
    // gốc của cây
    node *root = nullptr;

public:
    WordDictionary() {
        root = new node();
    }


    void addWord(string word) {
        // node hiện tại
        node *curr = root;

        // duyệt từng kí tự
        for(char ch: word){
            // nếu node con tương ứng chưa tồn tại, khởi tạo node mới
            if(curr->child[ch - 'a'] == nullptr)
                curr->child[ch - 'a'] = new node();

            // chuyển con trỏ xuống node vừa tạo để duyệt tiếp
            curr = curr->child[ch - 'a'];
        }
        // đánh dấu node cuối cùng, kết thúc 1 từ
        curr->isEnd = true;
    }


    bool find(const string &word, int index, node* curr){
        int size = word.size();
        // xét từng kí tự
        for(; index < size; ++index){
            // nếu kí tự đó là '.'
            if(word[index] == '.'){
                // kiểm tra node con nào phù hợp (node nào cũng đc vì '.' match với mọi kí tự)
                for(auto ch: curr->child){
                    if(ch && find(word, index + 1, ch)){
                        return true;
                    }
                }
                return false;
            }
            else if(curr->child[word[index]-'a']){
                curr=curr->child[word[index]-'a'];
            }
            else{
                return 0;
            }
        }
        return curr->isEnd;
    }


    bool search(string word){
        return find(word,0,root);
    }
};

int main(){
    string s1 = "phung";
    string s2 = "bad";
    string s5 = "bang";
    string s3 = "b..g";
    string s4 = "phu...";
    WordDictionary myDict;
    myDict.addWord(s1);
    myDict.addWord(s2);
    myDict.addWord(s5);
    cout << myDict.search(s3) << '\n';
    cout << myDict.search(s4) << '\n';
    return 0;
}