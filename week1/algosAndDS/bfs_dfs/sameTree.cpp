#include<iostream>
#include<queue>
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

// Solution 1: using recursive
bool isSameTree_recursive(TreeNode *p, TreeNode *q){
    if(p == nullptr && q == nullptr) return true;
    if(p == nullptr || q == nullptr) return false;
    if(p->val != q->val) return false;
    return isSameTree_recursive(p->left, q->left) && isSameTree_recursive(p->right, q->right);
}


// Solution 2: using iterative

bool check(TreeNode *p, TreeNode *q){
    if(p == nullptr && q == nullptr) return true;
    if(p == nullptr || q == nullptr) return false;
    if(p->val != q->val) return false;
    return true;
}


bool isSameTree_iterative(TreeNode *p, TreeNode *q){
    if(p == nullptr && q == nullptr) return true;
    if(!check(p,q)) return false;

    // khởi tạo 2 hàng đợi
    queue<TreeNode*> Queue_P;
    queue<TreeNode*> Queue_Q;
    Queue_P.push(p);
    Queue_Q.push(q);

    while(!Queue_P.empty()){
        p = Queue_P.front();
        Queue_P.pop();
        q = Queue_Q.front();
        Queue_Q.pop();

        if(!check(p,q)) return false;
        if(p != nullptr){
            if(!check(q->left, q->left)) return false;
            if(p->left != nullptr){
                Queue_P.push(p->left);
                Queue_Q.push(q->left);
            }

            if(!check(p->right, q->right)) return false;
            if(p->right != nullptr){
                Queue_P.push(p->right);
                Queue_Q.push(q->right);
            }

        }


    }
    return true;
}

int main(){
    return 0;
}