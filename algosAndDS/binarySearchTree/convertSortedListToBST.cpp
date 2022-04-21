#include<iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
private:
    ListNode* curr;
    TreeNode* treeify(int start, int end) {
        if (end < start) return nullptr;
        
        // left
        int mid = (start + end) / 2;
        TreeNode* node = new TreeNode();
        node->left = treeify(start, mid - 1);
        
        // root
        node->val = curr->val;
        curr = curr->next;
        
        // right
        node->right = treeify(mid + 1, end);
        return node;
    }
    
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int count = 0;
        curr = head;
        while (curr) curr = curr->next, count++;
        curr = head;
        return treeify(1, count);
    }
};

int main(){

    return 0;
}