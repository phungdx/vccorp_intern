from mysql.connector import Error
from mysql.connector import pooling

try:
    connection_pool = pooling.MySQLConnectionPool(pool_name="pynative_pool",
                                                  pool_size=5,
                                                  pool_reset_session=True,
                                                  host='localhost',
                                                  database='python_db',
                                                  user='root',
                                                  password='12345')

    print("Printing connection pool properties ")
    print("Connection Pool Name - ", connection_pool.pool_name)
    print("Connection Pool Size - ", connection_pool.pool_size)

    # Get connection object from a pool
    connection_object = connection_pool.get_connection()

    if connection_object.is_connected():
        db_Info = connection_object.get_server_info()
        print("Connected to MySQL database using connection pool ... MySQL Server version on ", db_Info)

        cursor = connection_object.cursor()
        cursor.execute("select database();")
        record = cursor.fetchone()
        print("Your connected to - ", record)

except Error as e:
    print("Error while connecting to MySQL using Connection pool ", e)
finally:
    # closing database connection.
    if connection_object.is_connected():
        cursor.close()
        connection_object.close()
        print("MySQL connection is closed")