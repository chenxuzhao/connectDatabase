#pragma once
#include <string>
using namespace std;

struct DBConfig {
	string driver;
	string hostname;
	string port;
	string name;
	string username;
	string password;
};

class Database
{

public:
	Database();
	virtual ~Database();
	virtual bool exec(string sql)=0;
	virtual bool connect(DBConfig config) = 0;
	virtual void close() = 0;
	virtual bool insert() = 0;
};

