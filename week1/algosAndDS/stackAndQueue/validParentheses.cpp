#include<iostream>
#include<cstring>
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



/* Kiểm tra tính hợp lệ của 1 string chứa toàn các dấu mở và đóng ngoặc

Quy tắc tiên quyết:
    - Loại dấu ngoặc nào mở ra cuối cùng thì sẽ phải đóng vào đầu tiên.

*/
bool isValid(char s[]){
    // Lấy length của string input
    int n = strlen(s);

    // Khởi tạo 1 stack để chứa các dấu mở ngoặc
    Stack myStack;

    for(int i = 0; i < n; ++i){
        // lần lượt đưa các dấu mở ngoặc vào stack
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            myStack.push(s[i]);
        }

        // Nếu gặp phải dấu đóng ngoặc
        else if(s[i] == ')' || s[i] == '}' || s[i] == ']'){
            // Kiểm tra xem stack có rỗng không, nếu rỗng --> string input không hợp lệ
            if(myStack.isEmpty()){
                return false;
            }

            // Nếu stack không rỗng
            else{
                // Lấy giá trị top của stack
                char top = myStack.top();

                // Kiểm tra xem dấu mở ra cuối cùng và dấu đóng vào mới nhất có cùng loại không
                if(s[i] == ')' && top == '(' ||
                    s[i] == '}' && top == '{' ||
                    s[i] == ']' && top == '['){
                        // Nếu cùng loại thì hợp lệ, xóa top của stack đi để duyệt tiếp
                        myStack.pop();
                    }

                // Nếu không cùng loại thì ---> string input không hợp lệ
                else{
                    return false;
                }
            }
        }
    }

    // sau khi duyệt xong string input mà stack của ta rỗng thì chứng tỏ string input hợp lệ,
    // và ngược lại
    return myStack.isEmpty() ? true:false;
}

int main(){
    char input1[] = "{{}}()[()]";
    char input2[] = "{][}";
    char input3[] = ")";
    cout << isValid(input1)<<'\n';
    cout << isValid(input2)<<'\n';
    cout << isValid(input3)<<'\n';
}