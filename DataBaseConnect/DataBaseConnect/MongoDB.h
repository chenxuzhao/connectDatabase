#pragma once
#include "Database.h"
#include <mongoc.h>

class MongoDB :
	public Database
{

private :
	mongoc_client_t *client;
public:
	MongoDB();
	virtual ~MongoDB();

	virtual bool exec(string sql);
	virtual bool connect(DBConfig config);
	virtual void close();

	virtual bool insert();
};

