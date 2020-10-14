#ifndef ORM_STOREMARK_STORE
#define ORM_STOREMARK_STORE

#include <memory>
#include <mutex>

#include "orm/store/store.h"

namespace orm::database {
class Database;
}

namespace orm::memory {
class Record;
}

namespace orm::store_mark {

class Store : public orm::store::Store {
public:
	Store(std::shared_ptr<orm::memory::Record>& record,
	      std::shared_ptr<orm::database::Database>& database);
	
public:
	std::shared_ptr<orm::core::Property> query(std::int64_t identity = 0) override;

	bool commit() override;

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
	std::mutex mMutex;
	std::shared_ptr<orm::memory::Record> mRecord;

private:
	std::shared_ptr<orm::database::Database> mDatabase;
};

} // orm::store_mark namespace

#endif
