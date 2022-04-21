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
    if(p == nullptr && q == nullptr) return true; // nếu 2 node đang xét cùng null thì return true
    if(p == nullptr || q == nullptr) return false; // nếu 1 trong 2 node null thì trả về false
    if(p->val != q->val) return false; // nếu 2 giá trị trong 2 node khác nhau thì trả về null

    // gọi đệ quy với các node bên trái và bên phải 2 node hiện tại
    return isSameTree_recursive(p->left, q->left) && isSameTree_recursive(p->right, q->right);
}


// Solution 2: using iterative

// check tính hợp lệ của 2 trees
// sử dụng 1 hàng đợi để check lần lượt 2 node liền kề
bool isSameTree_iterative(TreeNode* p, TreeNode* q) {
    queue<TreeNode *> queue; // khởi tạo queue
    queue.push(p); // thêm 1 node đang xét
    queue.push(q); // thêm node còn lại
    while (queue.size()!=0){ // lặp đến khi queue rỗng
        TreeNode * q2=queue.front(); // 
        queue.pop();
        TreeNode * q1=queue.front();
        queue.pop();
        if (q1==nullptr && q2==nullptr) continue; // nếu 2 node đang xét cùng null thì return true
        if (q1==nullptr || q2==nullptr) return false; // nếu 1 trong 2 node null thì trả về false
        if (q1->val!=q2->val) return false; // nếu 2 giá trị trong 2 node khác nhau thì trả về null

        // thêm các node bên trái và bên phải của 2 node hiện tại
        queue.push(q1->left);
        queue.push(q2->left);
        queue.push(q1->right);
        queue.push(q2->right);
    }
    return true;
}


int main(){
    return 0;
}