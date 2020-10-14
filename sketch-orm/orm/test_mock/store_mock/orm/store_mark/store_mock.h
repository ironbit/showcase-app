#ifndef TEST_ORM_STORE_MARK_STORE
#define TEST_ORM_STORE_MARK_STORE

#include <gmock/gmock.h>
#include <memory>

#include "orm/store/store.h"
#include "orm/core/property.h"

namespace test::mock {

class Store : public orm::store::Store {
public:
	MOCK_METHOD(std::shared_ptr<orm::core::Property>, query, (std::int64_t identity), (override));

	MOCK_METHOD(bool, commit, (), (override));

public:
	MOCK_METHOD(std::shared_ptr<orm::core::Property>, fetch, (), (override));

	MOCK_METHOD(bool, insert, (std::int64_t identity, std::shared_ptr<orm::core::Property>&& record), (override));

	MOCK_METHOD(bool, insert, (std::int64_t identity, const std::shared_ptr<orm::core::Property>& record), (override));

	MOCK_METHOD(bool, update, (std::int64_t identity, std::shared_ptr<orm::core::Property>&& record), (override));

	MOCK_METHOD(bool, update, (std::int64_t identity, const std::shared_ptr<orm::core::Property>& record), (override));

	MOCK_METHOD(bool, remove, (std::int64_t identity), (override));
	
public:
	MOCK_METHOD(std::unique_ptr<orm::store::Store>, clone, (),  (override));
};

} // test::mock namespace

#endif
