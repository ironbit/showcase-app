#ifndef ORM_DATABASE_DATABASE
#define ORM_DATABASE_DATABASE

#include <any>
#include <memory>
#include <optional>
#include <string>

#include "orm/core/property.h"

namespace orm::database {

class Database {
public:
	virtual ~Database()
	{ }

public:
	virtual std::shared_ptr<orm::core::Property> query(std::int64_t identity) = 0;
	
	virtual bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) = 0;

	virtual bool update(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) = 0;

	virtual bool remove(std::int64_t identity) = 0;
};

} // orm::database namespace

#endif
