#include<iostream>
using namespace std;


class Stack{
    private:
        // Kích thước tối đa của stack
        constexpr static int size = 10;

        // Track vị trí top của stack
        int top_index = -1;

        // Mảng mô phỏng stack
        int A[size];

    public:
        // Check xem stack có rỗng hay không
        bool isEmpty(){
            if(top_index < 0){
                return true;
            }
            return false;
        }

        // Check xem stack đã đầy chưa
        bool isFull(){
            if(top_index == size - 1){
                return true;
            }
            return false;
        }


        // Thêm phần tử vào stack
        void push(int x){
            // nếu stack đầy thì dừng
            if(isFull()){
                cout << "Stack is full" << '\n';
                return;
            }

            // Tăng chỉ số top lên 1 và thêm giá trị mới vào
            top_index += 1;
            A[top_index] = x;
        }


        // Xóa 1 phần tử top của stack
        void pop(){
            // Nếu stack rỗng thì dừng
            if(isEmpty()){
                cout << "Stack is empty"<< '\n';
                return;
            }

            // Giảm chỉ số của top đi 1 thì sẽ xóa nó khỏi stack
            top_index -= 1;
        }

        // Lấy giá trị đỉnh stack
        int top(){
            // Nếu stack rỗng thì dừng
            if(isEmpty()){
                cout << "Stack is empty"<< '\n';
                return -1;
            }

            return A[top_index];
        }

        // In stack ra màn hình
        void print(){
            if(isEmpty()){
                cout << "Stack is empty"<<'\n';
                return;
            }
            for (int i = 0; i <= top_index; ++i){
                cout << A[i] << " ";
            }
            cout << endl;
        }
};

int main(){
    Stack s;
    s.push(5);
    s.push(8);
    s.push(9);
    s.pop();
    s.pop();
    s.pop();
    s.print();
    return 0;
}