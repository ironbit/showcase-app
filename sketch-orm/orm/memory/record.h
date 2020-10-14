#ifndef ORM_MEMORY_RECORD
#define ORM_MEMORY_RECORD

#include <memory>
#include <string>

namespace orm::core {
class Property;
}

namespace orm::database {
class Database;
}

namespace orm::memory {

class Record {
public:
	virtual std::int64_t identity() = 0;

	virtual std::vector<std::string> attributes() = 0;

	virtual std::shared_ptr<orm::core::Property> get() = 0;

	virtual std::shared_ptr<orm::core::Property> get(const std::vector<std::string>& attributes) = 0;

	virtual void set(const std::shared_ptr<orm::core::Property>& record) = 0;

	virtual void update(const std::shared_ptr<orm::core::Property>& record) = 0;

	virtual void commit(orm::database::Database*) = 0;
};

} // orm::memory namespace

#endif
