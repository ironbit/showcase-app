#include "orm/store_mark/factory.h"
#include "orm/store_mark/store.h"

namespace orm::store_mark {

std::unique_ptr<orm::store::Store> Factory::create() {
	return std::make_unique<orm::store_mark::Store>(mRecord, mDatabase);
}

Factory& Factory::resetRecord() {
	mRecord.reset();
	return *this;
}

Factory& Factory::setRecord(const std::shared_ptr<orm::memory::Record>& record) {
	mRecord = record;
	return *this;
}

Factory& Factory::setDatabase(const std::shared_ptr<orm::database::Database>& database) {
	mDatabase = database;
	return *this;
}

} // orm::store_mark namespace
