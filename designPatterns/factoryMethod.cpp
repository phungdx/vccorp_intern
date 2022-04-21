#include<iostream>
using namespace std;

// biến enum cho các kiểu database
enum eConnectionType
{
    CONNECTION_TYPE_ORACLE = 0,
    CONNECTION_TYPE_SQLSERVER,
    CONNECTION_TYPE_MYSQL,
    CONNECTION_TYPE_DEFAULT
};

class Connection
{
    // định nghĩa interfaces
    virtual string description() = 0;
};

class OracleConnection : public Connection
{
    // implement interfaces của class Connection
    string description()
    {
        return "OracleConnection";
    };
};

class SqlServerConnection : public Connection
{
    // implement interfaces của class Connection
    string description()
    {
        return "SqlServerConnection";
    };
};

class MySqlConnection : public Connection
{
    // implement interfaces của class Connection
    string description()
    {
        return "MySqlConnection";
    };
};

// tạo factory
class DbConnectionFactory
{
public:
    // hàm khởi tạo object với kiểu bất kì
    static Connection* createConnection(eConnectionType connectionType);
};


Connection* DbConnectionFactory::createConnection(eConnectionType connectionType)
{
    Connection *connection = nullptr; // tạo một con trỏ kiểu connection

    // tạo object theo type đầu vào
    switch (connectionType)
    {
    case CONNECTION_TYPE_ORACLE:
        connection = new OracleConnection();
        break;
    case CONNECTION_TYPE_SQLSERVER:
        connection = new SqlServerConnection();
        break;
    case CONNECTION_TYPE_MYSQL:
        connection = new MySqlConnection();
        break;
    default:
        connection = new OracleConnection(); // default is Oracle
        break;
    }

    // trả ra object vừa đc tạo
    return connection;
}

int main(){
    // tạo 1 object kiểu SQL
    Connection *connection = DbConnectionFactory::createConnection(CONNECTION_TYPE_SQLSERVER);
    return 0;
}