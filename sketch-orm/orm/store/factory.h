#ifndef ORM_STORE_FACTORY
#define ORM_STORE_FACTORY

#include <memory>

namespace orm::database {
class Database;
}

namespace orm::memory {
class Record;
}

namespace orm::store {
class Store;
}

namespace orm::store {

class Factory {
public:
	virtual std::unique_ptr<orm::store::Store> create() = 0;

public:
	virtual Factory& resetRecord() = 0;

	virtual Factory& setRecord(const std::shared_ptr<orm::memory::Record>& record) = 0;
 
	virtual Factory& setDatabase(const std::shared_ptr<orm::database::Database>& database) = 0;
};

} // orm::store namespace

#endif
