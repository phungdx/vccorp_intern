#include <string>
#include <iostream>

using namespace std;

// tạo class Database
class Database
{
private:
    int mRecord; // bản ghi trong database
    string mName; // tên data base
    static Database* mInstancePtr; // static object duy nhất của class

    // hàm khởi tạo database trong dạng private để tránh bị gọi bên ngoài class
    Database(string name)
    {
        mName = name;
        mRecord = 0;
    }

public:
    // in ra tên hoạt động đang thao tác với bản ghi trong database cụ thể
    void editRecord(string operation)
    {
        cout << "Performing a " << operation <<
                "operation on record " << mRecord <<
                " in database " << mName << endl;
    }

    string getName() // lấy tên database
    {
        return mName;
    }

    static Database* getInstance(string name) // tạo 1 hàm static để khởi tạo database
    {
        // chỉ tạo mới nếu object chưa đc khởi tạo
        if (nullptr == mInstancePtr)
            mInstancePtr = new Database(name);
        return mInstancePtr; // trả ra object
    }
};

Database* Database::mInstancePtr = nullptr; // gán giá trị null ban đầu cho object

int main()
{
    Database *database;
    database = Database::getInstance("products");
    cout << "This is the " << database->getName() << " database." << endl;
    database = Database::getInstance("employees");
    cout << "This is the " << database->getName() << " database." << endl;
    return 0;
}