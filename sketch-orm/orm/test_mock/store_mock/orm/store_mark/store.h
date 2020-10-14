#ifndef ORM_STORE_MARK_STORE
#define ORM_STORE_MARK_STORE

#include "orm/store/store.h"
#include "orm/store_mark/store_mock.h"

namespace orm::store_mark {

class Store : public orm::store::Store {
public:
	test::mock::Store& mock();

public:
	std::shared_ptr<orm::core::Property> query (std::int64_t identity) override;

	bool commit () override;

public:
	std::shared_ptr<orm::core::Property> fetch() override;

	bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) override;

	bool insert(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) override;

	bool update(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) override;

	bool update(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) override;

	bool remove(std::int64_t identity) override;
	
public:
	std::unique_ptr<orm::store::Store> clone() override;

private:
	test::mock::Store mMock;
};

} // orm::store_mark namespace

#endif
