#pragma once
#include "Database.h"
#include "MysqlDatabase.h"
#include "MongoDB.h"
#include "RedisDB.h"

class DB
{
private:
	static DB * _instance;
	Database * database;

	DB();
	bool connect(struct DBConfig config);

public:
	~DB();
	static DB * getDB(struct DBConfig config);
	bool exec(string sql);
	bool insert();
	void close();
};

