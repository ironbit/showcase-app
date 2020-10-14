#include "orm/database_mark/database.h"

namespace orm::database_mark {

std::shared_ptr<orm::core::Property> Database::query(std::int64_t identity) {
	// read lock
	std::shared_lock lock(mMutex);
	
	// get record
	return retrieveRecord(identity);
}

bool Database::insert(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) {
	// write lock
	std::lock_guard lock(mMutex);

	// erase identity
	auto iterator = mData.find(identity);
	if (iterator != mData.end()) {
		mData.erase(iterator);
	}

	// read attributes, read data & write in database
	for (auto& attribute : record->attributes()) {
		mData[identity][attribute] = record->get(attribute);
	}

	// normal execution
	return true;
}

bool Database::update(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) {
	// write lock
	std::lock_guard lock(mMutex);

	// read attributes, read data & write in database
	for (auto& attribute : record->attributes()) {
		mData[identity][attribute] = record->get(attribute);
	}

	// normal execution
	return true;
}

bool Database::remove(std::int64_t identity) {
	// write lock
	std::lock_guard lock(mMutex);

	// verify whether record exists
	auto record = mData.find(identity);
	if (record != mData.end()) {
		// erase record
		mData.erase(record);
		return true;
	}

	// record not found
	return false;
}

std::shared_ptr<orm::core::Property> Database::retrieveRecord(std::int64_t index) {
	// default output
	auto outcome = std::make_shared<orm::core::Property>();

	// find record
	auto record = mData.find(index);
	if (record == mData.end()) {
		outcome.reset();
		return outcome;
	}

	// populate record
	for (const auto& data : record->second) {
		(*outcome)(data.first, data.second);
	}

	// shared property
	return outcome;
}

} // orm::database_mem namespace
