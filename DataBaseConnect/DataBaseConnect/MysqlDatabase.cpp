#include "MysqlDatabase.h"



MysqlDatabase::MysqlDatabase():driver(NULL),
    con(NULL),
    stmt(NULL),
    res(NULL),
    pstmt(NULL)
{

}


MysqlDatabase::~MysqlDatabase()
{
}


bool MysqlDatabase::exec(string sql) {
	pstmt = con->prepareStatement(sql);
	return pstmt->execute();

}
bool MysqlDatabase::connect(DBConfig config) {
	try {
		driver = get_driver_instance();
		con = driver->connect("tcp://" + config.hostname + ":" + config.port, config.username, config.password);
		con->setSchema(config.name);
		return true;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " 
			<< __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return false;
	
}

bool MysqlDatabase::insert() {
	return true;
}
void MysqlDatabase::close() {
	delete res;
	delete stmt;
	delete con;
	delete this;
}