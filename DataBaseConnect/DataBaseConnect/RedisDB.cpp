#include "RedisDB.h"

RedisDB::RedisDB() {

}

RedisDB::~RedisDB() {

}


bool RedisDB::exec(string sql) {
	return true;
}

bool RedisDB::connect(DBConfig config) {
	
#ifdef _WIN32
	//! Windows netword DLL init
	WORD version = MAKEWORD(2, 2);
	WSADATA data;

	if (WSAStartup(version, &data) != 0) {
		std::cout << "WSAStartup() failure" << std::endl;
		return false;
	}
#endif /* _WIN32 */
	cout << "conneting ..." << endl;
	client = new cpp_redis::redis_client();
	cout << "conneting ..." << endl;
	client->connect("127.0.0.1", 6379, [](cpp_redis::redis_client&) {
		std::cout << "client disconnected (disconnection handler)" << std::endl;
	});
	client->auth("root", [](cpp_redis::reply&) {
		std::cout << "client auth (disconnection handler)" << std::endl;
	});
		
		return true;
}

void RedisDB::close() {
	delete client;
#ifdef _WIN32
	WSACleanup();
#endif /* _WIN32 */


}

bool RedisDB::insert() {
	client->set("hello", "42", [](cpp_redis::reply& reply) {
		std::cout << "set hello 42: " << reply << std::endl;
		// if (reply.is_string())
		//   do_something_with_string(reply.as_string())
	});

	// same as client.send({ "DECRBY", "hello", 12 }, ...)
	client->decrby("hello", 12, [](cpp_redis::reply& reply) {
		std::cout << "decrby hello 12: " << reply << std::endl;
		// if (reply.is_integer())
		//   do_something_with_integer(reply.as_integer())
	});

	// same as client.send({ "GET", "hello" }, ...)
	client->get("hello", [](cpp_redis::reply& reply) {
		std::cout << "get hello: " << reply << std::endl;
		// if (reply.is_string())
		//   do_something_with_string(reply.as_string())
	});

	client->zadd("zhello", {}, { { "1", "a" },
	{ "2", "b" },
	{ "3", "c" },
	{ "4", "d" } },
		[](cpp_redis::reply& reply) {
		std::cout << "zadd zhello 1 a 2 b 3 c 4 d: " << reply << std::endl;
	});

	// commands are pipelined and only sent when client.commit() is called
	// client.commit();

	// synchronous commit, no timeout
	client->sync_commit();

	return true;

}