#include "orm/memory_mark/record.h"

namespace orm::memory_mark {

Record::Record(std::int64_t identity)
: mData{orm::memory::Data(identity)}
{ }

std::int64_t Record::identity() {
	std::shared_lock lock(mMutex);
	return mData.identity();
}

std::vector<std::string> Record::attributes() {
	std::shared_lock lock(mMutex);
	return mData.attributes();
}

std::shared_ptr<orm::core::Property> Record::get() {
	std::shared_lock lock(mMutex);
	return fetch();
}

std::shared_ptr<orm::core::Property> Record::get(const std::vector<std::string>& attributes) {
	std::shared_lock lock(mMutex);
	return fetch(attributes);
}

void Record::set(const std::shared_ptr<orm::core::Property>& record) {
	std::unique_lock lock(mMutex);

	mData.clear();
	store(record);
}

void Record::update(const std::shared_ptr<orm::core::Property>& record) {
	std::unique_lock lock(mMutex);
	store(record);
}

void Record::commit(orm::database::Database* db) {
	std::unique_lock lock(mMutex);
	auto data = fetch();
	db->insert(mData.identity(), data);
}

void Record::store(const std::shared_ptr<orm::core::Property>& record) {
	// implement iterable class (Property)
	for (auto& attribute : record->attributes()) {
		mData.set(attribute, record->get(attribute));
	}
}

std::shared_ptr<orm::core::Property> Record::fetch(const std::vector<std::string>& attributes) {
	auto outcome = std::make_shared<orm::core::Property>();
	if (!attributes.empty()) {
		for (const auto& attribute : attributes) {
			(*outcome)(attribute, mData.get(attribute));
		}
	} else {
		for (const auto& attribute : mData.attributes()) {
			(*outcome)(attribute, mData.get(attribute));
		}
	}
	return outcome;
}

} // orm::store_mark namespace
