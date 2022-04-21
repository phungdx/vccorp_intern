#include<iostream>
#include<vector>
using namespace std;

// Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

// Thứ tự traverse sẽ là left - root - right

 class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder_list; // khai báo 1 mảng để lưu các giá trị khi traverse
        traverse(root, inorder_list); // gọi đến hàm traverse
        return inorder_list; // trả về các giá trị theo thứ tự nhận được
    }
    
    void traverse(TreeNode* root, vector<int>& inorder_list){
        if(root == NULL) return; // nếu node hiện tại đang xét là null thì trả về
        traverse(root->left, inorder_list); // gọi đệ quy để traverse sang trái
        inorder_list.push_back(root->val); // lưu vào mảng giá trị
        traverse(root->right, inorder_list); // gọi đệ quy để traverse sang trái
    }
};

int main(){
}