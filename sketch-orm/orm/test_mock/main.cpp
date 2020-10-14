#include <any>
#include <iostream>

#include "orm/database/database.h"
#include "orm/database_mem/database.h"

struct Sample {
	std::int64_t id;
	std::string  title;
	std::int32_t timestamp;
};

int main() {
	//db::Store store;
	//store.insert(1234, db::property("title", "sample")("timestamp", 12345.6789));
	//store.insert(1234, db::property("title", "sample")("timestamp", 1111, 2222));
	std::unique_ptr<orm::database::Database> db = std::make_unique<orm::database_mem::Database>();

	db->insert(1234, orm::core::property("title", "sample")("time", 5050));

	auto x = db->query(1234);
	if (!x) {
		std::cout << "data not found" << std::endl;
	} else {
		std::cout << "title | " << std::any_cast<const char*>(x->get("title")) << std::endl;
		std::cout << "time | " << std::any_cast<int>(x->get("time")) << std::endl;
	}
}