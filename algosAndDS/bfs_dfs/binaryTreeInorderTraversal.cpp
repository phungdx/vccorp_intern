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


 class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder_list;
        traverse(root, inorder_list);
        return inorder_list;
    }
    
    void traverse(TreeNode* root, vector<int>& inorder_list){
        if(root == NULL) return;
        traverse(root->left, inorder_list);
        inorder_list.push_back(root->val);
        traverse(root->right, inorder_list);
    }
};

int main(){
}