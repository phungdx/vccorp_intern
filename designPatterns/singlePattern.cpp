#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
/**
 * Singleton class định nghĩa `GetInstance` method hoạt động thay thế phương thức khởi tạo,
 * và để client truy cập duy nhất chỉ 1 object duy nhất mỗi lần gọi.
 */
class Singleton
{

    /**
     * Method khởi tạo của class Singleton luôn để private
     */
private:
    static Singleton * pinstance_; // instance duy nhất của class
    static std::mutex mutex_; // mutex để giải quyết vấn đề đa luồng.-

protected:
    Singleton(const std::string value): value_(value)
    {
    }
    ~Singleton() {}
    std::string value_;

public:
    /**
     * Singletons không thể bị sao chép
     */
    Singleton(Singleton &other) = delete;
    /**
     * Singletons không thể sử dụng toán tử gán nạp chồng.
     */
    void operator=(const Singleton &) = delete;


    /**
     * Đây là phương thức kiểm xoát việc truy cập đến instance duy nhất của class.
     * Lần đầu được gọi thì nó sẽ tạo ra 1 static instance mới,
     * Ở những lần chạy tiếp theo thì nó chỉ return lại instance đã tồn tại.
     */
    static Singleton *GetInstance(const std::string& value);

    /**
     * Một vài chức năng của class
     */
    void SomeBusinessLogic()
    {
        // ...
    }
    
    std::string value() const{
        return value_;
    } 
};

/**
 * Static methods nên được định nghĩa bên ngoài class
 */

Singleton* Singleton::pinstance_{nullptr}; // khởi tạo instance
std::mutex Singleton::mutex_;

/**
 * Lần đầu gọi GetInstance, ta sẽ lock vùng địa chỉ truy cập lại,
 * đảm bào rằng instance lad null và chúng ra sẽ khởi tạo cho nó giá trị.
 */
Singleton *Singleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}

void ThreadFoo(){
    // Mô phỏng quá trình khởi tạo chậm
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar(){
    // Mô phỏng quá trình khởi tạo chậm
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main()
{   
    std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    
    return 0;
}