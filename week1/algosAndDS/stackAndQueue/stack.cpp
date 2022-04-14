#include<iostream>
using namespace std;


class Stack{
    private:
        constexpr static int size = 10;
        int top_index = -1;
        int A[size];

    public:
        void push(int x){
            if(isFull()){
                cout << "Stack is full" << '\n';
                return;
            }

            top_index += 1;
            A[top_index] = x;
        }


        void pop(){
            if(isEmpty()){
                cout << "Stack is empty"<< '\n';
                return;
            }

            top_index -= 1;
        }

        int top(){
            if(isEmpty()){
                cout << "Stack is empty"<< '\n';
                return -1;
            }

            return A[top_index];
        }

        bool isEmpty(){
            if(top_index < 0){
                return true;
            }
            return false;
        }

        bool isFull(){
            if(top_index == size - 1){
                return true;
            }
            return false;
        }

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