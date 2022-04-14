#include<iostream>
using namespace std;

class Queue{
    private:
        constexpr static int size = 10;
        int rear = -1;
        int front = -1;
        int A[size];

    public:
        bool isEmpty(){
            if(front == -1 && rear == -1){
                return true;
            }
            return false;
        }

        bool isFull(){
            if(rear == size - 1){
                return true;
            }
            return false;
        }

        void enqueue(int x){
            if(isFull()){
                cout <<"Queue is full"<<'\n';
                return;
            }

            if(isEmpty()){
                front = rear = 0;
            }

            else{
                ++rear;
            }

            A[rear] = x;
        }

        void dequeue(){
            if(isEmpty()){
                cout <<"Queue is empty"<<'\n';
                return;
            }
            
            if(front == rear){
                front = rear = -1;
            }
            else{
                ++front;
            }
        }

        void print(){
            if(isEmpty()){
                cout <<"Queue is empty"<<'\n';
                return;
            }

            for(int i = front; i <= rear; ++i){
                cout<<A[i]<<" ";
            }
            cout <<endl;
        }

        int getSize(){
            return rear - front + 1;
        }

        int getFront(){
            return A[front];
        }

        int getBack(){
            return A[rear];
        }
};


class myStack{
    private:
        Queue q;

    public:
        void push(int x){
            q.enqueue(x);
        }

        int pop(){
            int len = q.getSize();
            for(int i = 0; i < len - 1; i++) {
                int tmp = q.getFront();
                q.dequeue();
                q.enqueue(tmp);
            }
            int res = q.getFront();
            q.dequeue();
            
            return res;
        }

        int top(){
            return q.getBack();
        }

        bool empty(){
            return q.isEmpty();
        }

        void print(){
            q.print();
        }
};


int main(){
    myStack s;
    s.push(5);
    s.push(6);
    s.push(9);
    cout << s.pop() << '\n';
    s.print();
    return 0;
}