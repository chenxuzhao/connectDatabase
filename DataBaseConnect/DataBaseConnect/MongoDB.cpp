#include "MongoDB.h"


MongoDB::MongoDB()
{

}


MongoDB::~MongoDB()
{
}

bool MongoDB::exec(string sql) {
	
	return true;

}
bool MongoDB::connect(DBConfig config) {
	mongoc_init();
	string mg = "mongodb://127.0.0.1:27017";
	client = mongoc_client_new(mg.c_str());
	if(!client)
		return false;
	mongoc_client_set_error_api(client, 2);
	return true;

}

bool MongoDB::insert() {
	mongoc_collection_t * col=  mongoc_client_get_collection(this->client,"Customer","user");
	mongoc_bulk_operation_t *bulk;
	enum N { ndocs = 4 };
	bson_t *docs[ndocs];
	bson_error_t error;
	int i = 0;
	bool ret;

	bulk = mongoc_collection_create_bulk_operation(col, true, NULL);

	docs[0] = BCON_NEW("x", BCON_DOUBLE(1.0), "tags", "[", "dog", "cat", "]");
	docs[1] = BCON_NEW("x", BCON_DOUBLE(2.0), "tags", "[", "cat", "]");
	docs[2] = BCON_NEW(
		"x", BCON_DOUBLE(2.0), "tags", "[", "mouse", "cat", "dog", "]");
	docs[3] = BCON_NEW("x", BCON_DOUBLE(3.0), "tags", "[", "]");

	for (i = 0; i < ndocs; i++) {
		mongoc_bulk_operation_insert(bulk, docs[i]);
		bson_destroy(docs[i]);
		docs[i] = NULL;
	}

	ret = mongoc_bulk_operation_execute(bulk, NULL, &error);

	if (!ret) {
		fprintf(stderr, "Error inserting data: %s\n", error.message);
	}

	mongoc_bulk_operation_destroy(bulk);
	mongoc_collection_destroy(col);
	return ret;
}

void MongoDB::close() {
	mongoc_client_destroy(client);
	mongoc_cleanup();
	delete this;
}

