#include<iostream>
#include<queue>
#include<cmath>
using namespace std;

// Khai báo cấy trúc một của một node trong tree
struct Node{
    int data;
    Node* left;
    Node* right;
};

// Class binary tree
class bst{
    private:
        // Khai báo root cho tree
        Node* root;

    public:
        // Ban đầu cây rỗng
        bst(){
            root = NULL;
        }
        
        // Tạo 1 node mới từ dữ liệu được cho
        Node* getNewNode(int x){
            Node* newNode = new Node();
            newNode->data = x;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }

        // insert 1 node mới vào cây
        void insert(Node*& root, int data);
        void insertNode(int data);

        // Tìm kiếm 1 node xem có trong cây không
        bool search(Node* root, int data);
        bool searchNode(int data);

        // Tìm giá trí nhỏ nhất trong tree
        int minData(Node* root);
        int findMin();

        // Tìm giá trị lớn nhất trong tree
        int maxData(Node* root);
        int findMax();

        // Lấy chiều cao của cây
        int height(Node* root);
        int getHeight();

        // Duyệt cây theo chiều rộng
        void traverse_BFS(Node* root);
        void traverse_level_order();

        /*
        Duyệt cây theo chiều sâu theo 3 cách:
            +) Left - root - right (LDR)
            +) root - left - right (DLR)
            +) left - right - root (LRD)

        */
        void traverse_DFS_LDR(Node* root);
        void traverse_DFS_DLR(Node* root);
        void traverse_DFS_LRD(Node* root);
        void traverse_depth_order(string type);

        void delete_(Node*& root, int data);
        void deleteNode(int data);

        void delete__(Node*& root);
        void deleteTree();
};


void bst::insert(Node*& root, int data){
    // Nếu root là NULL thì gán root = node mới luôn
    if (root == NULL){
        root = getNewNode(data);
    }

    else{
        // Nếu dữ liệu đó đã có trong cây rồi thì dừng, 
        // giả sử cây chỉ chứa các giá trị khác nhau.
        if(root->data == data) return;

        // Nếu dữ liệu mới nhỏ hơn giá trị nằm ở root,
        // thì tiếp túc tìm kiếm vị trí phù hợp ở subtree bên trái root.
        else if(root->data > data) insert(root->left, data);

        // Nếu dữ liệu mới lớn hơn giá trị nằm ở root,
        // thì tiếp túc tìm kiếm vị trí phù hợp ở subtree bên phải root.
        else insert(root->right, data);
    }

}


void bst::insertNode(int data){
    insert(root, data);
}


bool bst::search(Node* root, int data){
    // Nếu cây rỗng hoặc soát hết ko tìm thấy thì dừng.
    if(root == NULL) return false;

    // nếu tìm thấy thì trả về true
    if (root->data == data) return true;

    // nếu giá trị mới nhỏ hơn giá trị ở root,
    // tìm tiếp ở subtree bên trái root
    else if(root->data > data) return search(root->left, data);

    // nếu giá trị mới lớn hơn giá trị ở root,
    // tìm tiếp ở subtree bên phải root 
    else return search(root->right, data);

}


bool bst::searchNode(int data){
    return search(root, data);
}


/*
Cách hoạt động giống như hàng đợi queue.
Ta lần lượt đưa các node trên cùng level vào hàng đợi.
Sau đó lấy ra lần lượt các node.
*/
void bst::traverse_BFS(Node* root){
    // nếu cây rỗng thì dừng
    if(root == NULL) return;

    // Khởi tạo hàng đợi q
    queue<Node*> q;

    // Đưa root vào trước
    q.push(root);

    // Lặp đến khi nào cây rỗng
    while(!q.empty()){
        // lấy node ở đầu queue
        Node* current = q.front();
        // In node ở đầu queue
        cout << current->data <<' ';
        // Check xem node ở đầu queue có node con không
        // nếu có thêm vào queue luôn
        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);

        // Xóa node đầu khỏi queue sau khi duyệt xong
        q.pop();
    }
    cout << '\n';
}


void bst::traverse_level_order(){
    traverse_BFS(root);
}


void bst::traverse_DFS_DLR(Node* root){
    if(root == NULL) return;
    cout << root->data << ' ';
    traverse_DFS_DLR(root->left);
    traverse_DFS_DLR(root->right);
}


void bst::traverse_DFS_LDR(Node* root){
    if(root == NULL) return;
    traverse_DFS_LDR(root->left);
    cout << root->data <<' ';
    traverse_DFS_LDR(root->right);
}


void bst::traverse_DFS_LRD(Node* root){
    if(root == NULL) return;
    traverse_DFS_LRD(root->left);
    traverse_DFS_LRD(root->right);
    cout << root->data <<' ';
}


void bst::traverse_depth_order(string type){
    if(!type.empty()){
        cout << type << ':';
        if(type == "DLR") traverse_DFS_DLR(root);
        else if (type == "LDR") traverse_DFS_LDR(root);
        else if(type == "LRD") traverse_DFS_LRD(root);
    }

    else traverse_DFS_LDR(root);

    cout <<'\n';
}


int bst::height(Node* root){
    if(root == NULL) return -1;
    int height_left = height(root->left);
    int height_right = height(root->right);
    return max(height_left, height_right) + 1;
}

int bst::getHeight(){
    return height(root);
}


int bst::minData(Node* root){
    if(root == NULL){
        cout << "Tree is empty\n";
        return -1;
    }
    // Iterative solution
    // Node* temp = root;
    // while(temp->left != NULL){
    //     temp = temp->left;
    // }
    // return temp->data;


    // Recursive solution
    if(root->left == NULL){
        return root->data;
    }
    return minData(root->left);



}


int bst::findMin(){
    return minData(root);
}


int bst::maxData(Node* root){
    if(root == NULL){
        cout << "Tree is empty\n";
        return -1;
    }
    // Iterative solution
    // Node* temp = root;
    // while(temp->right != NULL){
    //     temp = temp->right;
    // }
    // return temp->data;


    // Recursive solution
    if(root->right == NULL){
        return root->data;
    }
    return maxData(root->right);



}


int bst::findMax(){
    return maxData(root);
}


void bst::delete_(Node*& root, int data){
    if(root == NULL) return;

    if(root->data == data){
        // Node cần xóa ko có child nào
        if(root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        }

        // Node cần xóa có 1 con trái
        else if(root->left != NULL && root->right == NULL){
            Node* temp = root;
            root = root->left;
            delete temp;
        }

        // node cần xóa có 1 con phải
        else if(root->left == NULL && root->right != NULL){
            Node* temp = root;
            root = root->right;
            delete temp;
        }

        // Node cần xóa có 2 con
        else{
            // Tìm giá trị nhỏ nhất bên phải của root
            // để thay thế cho giá trị hiện tại của root
            // Hoặc có thể thay bằng giá trị lớn nhất bên trái của root
            int min_right_subtree = minData(root->right);
            root->data = min_right_subtree;

            // Sau khi thay thế xong thì xóa cái giá trị dùng để thay thế đi
            delete_(root->right, min_right_subtree);
        }
    }
    else if(root->data > data) delete_(root->left, data);
    else delete_(root->right, data);


}

void bst::deleteNode(int data){
    delete_(root, data);
}

void bst::delete__(Node*& root){
    if(root == NULL) return;
    delete__(root->left);
    delete__(root->right);
    delete root;
    root = NULL;
}


void bst:: deleteTree(){
    delete__(root);
}


int main(){
    bst tree;
    tree.insertNode(15);
    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(25);
    tree.insertNode(8);
    tree.insertNode(12);
    tree.insertNode(11);
    tree.deleteNode(10);

    tree.traverse_level_order();
    cout << "Height:" << tree.getHeight() <<'\n';
    cout << "Min:" << tree.findMin() << '\n';
    cout << "Max:" << tree.findMax() << '\n';
    tree.deleteTree();
    tree.traverse_level_order();
    return 0;
}