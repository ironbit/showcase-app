#include "orm/store_mark/store.h"
#include "orm/store_mark/factory.h"
#include "orm/memory_mark/record.h"

namespace orm::store_mark {

Store::Store(std::shared_ptr<orm::memory::Record>& record,
             std::shared_ptr<orm::database::Database>& database)
 : mRecord{record}, mDatabase{database}
{ }

bool Store::commit() {
	std::unique_lock lock(mMutex);

	mRecord->commit(mDatabase.get());
	return true;
}

std::shared_ptr<orm::core::Property> Store::query(std::int64_t identity) {
	std::unique_lock lock(mMutex);

	if (identity == 0) {
		if (mRecord->identity() == 0) {
			return nullptr;
		}
		identity = mRecord->identity();
	}
	
	auto record = mDatabase->query(identity);

	if (!mRecord || (mRecord->identity() != identity)) {
		mRecord = std::make_shared<orm::memory_mark::Record>(identity);		
	}
	mRecord->set(record);

	return record;
}

std::shared_ptr<orm::core::Property> Store::fetch() {
	std::unique_lock lock(mMutex);
	return mRecord->get();
}

bool Store::insert(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) {
	return insert(identity, record);
}

bool Store::insert(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) {
	std::unique_lock lock(mMutex);

	if (!mRecord || (mRecord->identity() != identity)) {
		mRecord = std::make_shared<orm::memory_mark::Record>(identity);
	}
	mRecord->set(record);

	return true;
}

bool Store::update(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) {
	return update(identity, record);
}

bool Store::update(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) {
	std::unique_lock lock(mMutex);

	if (mRecord->identity() != identity) {
		mRecord = std::make_shared<orm::memory_mark::Record>(identity);
	}
	mRecord->update(record);

	return true;
}

bool Store::remove(std::int64_t identity) {
	std::unique_lock lock(mMutex);

	if (mRecord->identity() != identity) {
		return false;
	}

	mRecord = std::make_shared<orm::memory_mark::Record>(identity);
	return true;
}

std::unique_ptr<orm::store::Store> Store::clone() {
	std::unique_lock lock(mMutex);

	std::unique_ptr<orm::store::Factory> factory(new orm::store_mark::Factory());
	(*factory).setRecord(mRecord)
	          .setDatabase(mDatabase);

	return factory->create();
}

} // orm::store_mark namespace
