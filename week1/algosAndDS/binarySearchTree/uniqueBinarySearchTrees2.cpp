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



// Sử dụng đệ quy
class Solution {
public:
    vector<TreeNode*> rec(int start, int end) {
        vector<TreeNode*> res;
        if (start > end) return {NULL};
        
        if (start == end) return {new TreeNode(start)};
        
        for (int i = start; i <= end; i++) {
            vector<TreeNode*> left = rec(start, i-1);
            vector<TreeNode*> right = rec(i+1, end);
            
            for (auto l : left)
                for (auto r : right)
                    res.push_back(new TreeNode(i, l, r));
        }
        return res;
    }
    
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> res = rec(1, n);
        return res;
    }
};

int main(){

    return 0;
}