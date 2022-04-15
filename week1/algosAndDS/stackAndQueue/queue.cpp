#include<iostream>
using namespace std;

/*
Queue sẽ được biểu diễn như sau

            ---------------------------
            front                   rear
            ---------------------------
            Ra                      Vào

*/
class Queue{
    private:
        // Kichs thước tối đa queue
        constexpr static int size = 10;

        // Track vị trí đầu vào của queue
        int rear = -1;

        // Track vị trí đầu ra của queue
        int front = -1;

        // Khởi tạo mảng để mô phỏng queue
        int A[size];

    public:
        // Kiểm tra queue có rỗng không
        bool isEmpty(){
            if((front == -1 && rear == -1) || front > rear){
                return true;
            }
            return false;
        }

        // Kiểm tra queue có đầy không
        bool isFull(){
            if(rear == size - 1){
                return true;
            }
            return false;
        }

        // Thêm phần tử vào queue
        void enqueue(int x){
            // Nếu queue đầy thì dừng
            if(isFull()){
                cout <<"Queue is full"<<'\n';
                return;
            }

            // Nếu queue rỗng thì tăng chỉ số của front và rear lên 0
            // để chỉ vào phần tử thứ nhất của queue
            if(isEmpty()){
                front = rear = 0;
            }

            // Nếu queue có phần tử rồi thì tăng chỉ số của rear lên 1
            else{
                ++rear;
            }

            // gán phần tử mới cho vị trí mới mà rear chỉ.
            A[rear] = x;
        }

        // Xóa 1 phần tử ra khỏi queue
        void dequeue(){
            // nếu queue rỗng thì ngừng
            if(isEmpty()){
                cout <<"Queue is empty"<<'\n';

                // Đặt lại chỉ số của front và rear về ban đầu
                if(front > rear){
                    front = rear = -1;
                }
                return;
            }
            
            // Tăng chỉ số front lên 1 là bỏ được phần tử đầu khỏi queue
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

    
    cout << "Size of queue:" << q.getSize() <<'\n';
    q.print();
}