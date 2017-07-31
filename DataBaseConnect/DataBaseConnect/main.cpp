#include <iostream>
#include "DB.h"

int main() {
	struct DBConfig config;
	config.driver = "redis";
	config.hostname = "localhost";
	config.name = "test";
	config.password = "root";
	config.port = "3306";
	config.username = "root";

	DB * db = DB::getDB(config);
	//string sql = "insert into `user` (`firstName`,`lastName`) values (\"chen\",\"xu\")";
	//db->exec(sql);
	if (!db) {
		cout << "database connect error" << endl;
	}
	else {
		db->insert();
	}

	cout << "end" << endl;
	

	while (true)
	{

	}
}