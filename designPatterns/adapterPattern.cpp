#include<iostream>
using namespace std;


/*
Trong ví dụ này:
UI đang làm việc với backend A thì chuyển sang làm việc với backend B
Backend B thì sử lý tên người dùng theo first và last name
còn backend A thì sử lý chung trong 1 string name
Tạo adapter để không cần phải sửa UI và backend B sao cho
chúng có thể làm việc với nhau.

*/


// Interface mà Back-end A quy định cho đối tượng user
class BackendAUserInterface
{
public:
    virtual void setName(std::string name) = 0;
    virtual std::string getName() = 0;
};

// Class User hiện tại đang implement BackendAUserInterface như sau
class User : public BackendAUserInterface 
{
private:
    std::string mName;

public:
    void setName(std::string name)
    {
        mName = name;
    }

    std::string getName()
    {
        return mName;
    }
};


// Interface mà Back-end B quy định cho đối tượng user
class BackendBUserInterface
{
public:
    virtual void setFirstName(std::string firstName) = 0;
    virtual void setLastName(std::string lastName) = 0;
    virtual std::string getFirstName() = 0;
    virtual std::string getLastName() = 0;
};


// Giả sử có class UserB implement BackendBUserInterface như sau
class UserB : public BackendBUserInterface
{
private:
    std::string mFirstname;
    std::string mLastname;
public:
    void setFirstName(std::string firstName)
    {
        mFirstname = firstName;
    }

    void setLastName(std::string lastName)
    {
        mLastname = lastName;
    }

    std::string getFirstName()
    {
        return mFirstname;
    }

    std::string getLastName()
    {
        return mLastname;
    }
};



// Tạo adapter
class UserAtoBAdapter : public BackendBUserInterface
{
private:
    User mUser;
    std::string mFirstname;
    std::string mLastname;

public:
    UserAtoBAdapter(User user)
    {
        mUser = user;
        
        // tách first name và last name
        unsigned int splitPostion = user.getName().find_first_of(" ");
        if (splitPostion != string::npos)
        {
            mFirstname = user.getName().substr(0, splitPostion + 1);
            mLastname = user.getName().substr(splitPostion + 1, user.getName().length() - mFirstname.length());
        }
    }

    void setFirstName(std::string firstName)
    {
        mFirstname = firstName;
    }

    void setLastName(std::string lastName)
    {
        mLastname = lastName;
    }

    std::string getFirstName()
    {
        return mFirstname;
    }

    std::string getLastName()
    {
        return mLastname;
    }
};

int main()
{    
    // tạo User object
    User user;
    user.setName("Phung Dao Xuan");

    // tạo adapter
    UserAtoBAdapter adapter(user);
    cout << "First name: " << adapter.getFirstName() << endl;
    cout << "Last name: " << adapter.getLastName() << endl;

    return 0;
}