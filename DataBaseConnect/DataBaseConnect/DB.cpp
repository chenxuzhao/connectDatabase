#include "DB.h"

DB* DB::_instance = NULL;

DB::DB():database(NULL)
{
}

DB* DB::getDB(struct DBConfig config) {
	if (_instance == NULL) {
		_instance = new DB();
		if (!_instance->connect(config)) {
			cout << "connect error" << endl;
			delete _instance;
			_instance = NULL;
		}
	}
	
	return _instance;
}

bool DB::connect(struct DBConfig config) {
	//TODO
	if (config.driver == "mysql") {
		this->database = new MysqlDatabase();
		return this->database->connect(config);
	}

	if (config.driver == "mongodb") {
		this->database = new MongoDB();
		return this->database->connect(config);
	}

	if (config.driver == "redis") {
		this->database = new RedisDB();
		return this->database->connect(config);
	}


	return false;
		

	
}
bool DB::exec(string sql) {
	if(this->database!=NULL)
	return database->exec(sql);
	return false;
}

bool DB::insert() {
	if (this->database != NULL)
		return database->insert();
	return false;
}

void DB::close() {
	if (this->database != NULL)
		this->database->close();
	delete _instance;
}

DB::~DB()
{
}
