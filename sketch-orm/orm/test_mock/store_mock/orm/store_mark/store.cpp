#include "orm/store_mark/store.h"

namespace orm::store_mark {

test::mock::Store& Store::mock() {
	return mMock;
}

std::shared_ptr<orm::core::Property> Store::query(std::int64_t identity) {
	return mMock.query(identity);
}

bool Store::commit() {
	return mMock.commit();
}

std::shared_ptr<orm::core::Property> Store::fetch() {
	return mMock.fetch();
}

bool Store::insert(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) {
	return mMock.insert(identity, std::forward<std::shared_ptr<orm::core::Property>>(record));
}

bool Store::insert(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) {
	return mMock.insert(identity, record);
}

bool Store::update(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) {
	return mMock.update(identity, std::forward<std::shared_ptr<orm::core::Property>>(record));
}

bool Store::update(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) {
	return mMock.update(identity, record);
}

bool Store::remove(std::int64_t identity) {
	return mMock.remove(identity);
}

std::unique_ptr<orm::store::Store> Store::clone() {
	return mMock.clone();
}

} // orm::store_mark namespace
