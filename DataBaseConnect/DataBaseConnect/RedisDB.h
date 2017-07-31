#pragma once
#include "Database.h"
#include <cpp_redis/cpp_redis>

#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */


class RedisDB :
	public Database
{

private :
	cpp_redis::redis_client * client;

public:
	RedisDB();
	~RedisDB();

	virtual bool exec(string sql);
	virtual bool connect(DBConfig config);
	virtual void close();
	virtual bool insert();
};

