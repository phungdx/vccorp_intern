#include<iostream>
#include<cstring>
using namespace std;


class Stack{
    private:
        constexpr static int size = 30;
        int top_index = -1;
        char A[size];

    public:
        void push(char x){
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
                cout << A[i];
            }
            cout << endl;
        }

        int getSize(){
            return top_index + 1;
        }

        void pushMultiple(char s[]){
            int n = strlen(s);
            for (int i = 0; i < n; ++i){
                push(s[i]);
            }
        }
};


bool isValid(char s[]){
    int n = strlen(s);
    Stack myStack;

    for(int i = 0; i < n; ++i){
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            myStack.push(s[i]);
        }
        else if(s[i] == ')' || s[i] == '}' || s[i] == ']'){
            if(myStack.isEmpty()){
                return false;
            }
            else{
                char top = myStack.top();
                if(s[i] == ')' && top == '(' ||
                    s[i] == '}' && top == '{' ||
                    s[i] == ']' && top == '['){

                        myStack.pop();
                    }

                else{
                    return false;
                }
            }
        }
    }

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