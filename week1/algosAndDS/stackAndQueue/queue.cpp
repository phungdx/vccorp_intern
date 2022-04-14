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
            return rear - front;
        }

        int getFront(){
            return A[front];
        }

        int getBack(){
            return A[rear];
        }
};


int main(){
    Queue q;
    q.enqueue(2);
    q.enqueue(5);
    q.enqueue(7);
    q.dequeue();
    q.enqueue(3);
    q.enqueue(1);
    q.enqueue(9);
    q.enqueue(10);
    q.enqueue(4);
    q.enqueue(6);
    q.dequeue();
    q.enqueue(2);
    q.enqueue(15);
    q.enqueue(99);

    
    cout << "Size of queue:" <<q.getSize() <<'\n';
    q.print();
}