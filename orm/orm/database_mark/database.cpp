#include <iterator>

#include "orm/database_mark/database.h"

namespace orm::database_mark {

std::optional<std::shared_ptr<orm::core::Property>> Database::query(std::int64_t identity) {
	// read lock
	std::shared_lock lock(mMutex);
	
	// get record
	auto mapper = mData.find(identity);
	
	// whether record not found
	if (mapper == mData.end()) {
		return std::optional<std::shared_ptr<orm::core::Property>>();
	}

	// create property
	auto property = std::make_shared<orm::core::Property>();
	for (auto it = mapper->second.begin(); it != mapper->second.end(); ++it) {
		(*property)(it->first, it->second);
	}

	// return optional - property
	return std::optional<std::shared_ptr<orm::core::Property>>{property};
}

bool Database::insert(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) {
	// write lock
	std::lock_guard lock(mMutex);

	// read attributes, read data & write in database
	for (auto& attribute : record->attributes()) {
		mData[identity][attribute] = record->get(attribute);
	}

	// normal execution
	return true;
}

bool Database::update(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) {
	return insert(identity, record);
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

std::vector<std::shared_ptr<orm::core::Property>>
Database::queryRange(std::int64_t min, std::int64_t max) {
	// default value
	std::vector<std::shared_ptr<orm::core::Property>> outcome;

	// verify input
	if (max < min) {
		return outcome;
	}
	if (max <= 0 || min <= 0 ) {
		return outcome;
	}

	{
		// read lock
		std::shared_lock lock(mMutex);

		// retrieve indexes
		auto minIndex = mIdentities.lower_bound(min);
		auto maxIndex = mIdentities.upper_bound(max);

		// populate properties output
		outcome.reserve(std::distance(minIndex, maxIndex));
		for (auto it = minIndex; it != maxIndex; ++it) {
			outcome.emplace_back(retrieveRecord(*it));
		}

		// vector of properties
		return outcome;
	}
}

std::vector<std::shared_ptr<orm::core::Property>>
Database::queryRange(const std::string& attribute, orm::core::Types types, std::any& minValue, std::any& maxValue) {
	// later implemented
	return std::vector<std::shared_ptr<orm::core::Property>>();
}

std::vector<std::shared_ptr<orm::core::Property>>
Database::queryRange(const std::string& attribute, orm::core::Types types, std::any&& minValue, std::any&& maxValue) {
	return queryRange(attribute, types, minValue, maxValue);
}

std::shared_ptr<orm::core::Property> Database::retrieveRecord(std::int64_t index) {
	// default output
	auto outcome = std::make_shared<orm::core::Property>();

	// find record
	auto record = mData.find(index);
	if (record == mData.end()) {
		return outcome;
	}

	// populate record
	for (auto& data : record->second) {
		(*outcome)(data.first, data.second);
	}

	// shared property
	return outcome;
}

} // orm::database_mem namespace
