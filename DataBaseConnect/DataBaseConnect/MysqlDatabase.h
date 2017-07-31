#pragma once
#include "Database.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>

using namespace std;
using namespace sql;

class MysqlDatabase :
	public Database
{
private:
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;

public:
	MysqlDatabase();
	virtual ~MysqlDatabase();

public:
	virtual bool exec(string sql);
	virtual bool connect(DBConfig config);
	virtual void close();
	virtual bool insert();
};

