#ifndef ORM_DATABASE_DATABASE
#define ORM_DATABASE_DATABASE

#include <any>
#include <memory>
#include <optional>
#include <string>

#include "orm/core/property.h"
#include "orm/core/types.h"

namespace orm::database {

class Database {
public:
	virtual ~Database()
	{ }

public:
	virtual std::optional<std::shared_ptr<orm::core::Property>> query(std::int64_t identity) = 0;
	
	virtual bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) = 0;

	virtual bool update(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) = 0;

	virtual bool remove(std::int64_t identity) = 0;

public:
	virtual std::vector<std::shared_ptr<orm::core::Property>>
		queryRange(std::int64_t min, std::int64_t max) = 0;

	virtual std::vector<std::shared_ptr<orm::core::Property>>
		queryRange(const std::string& attribute, orm::core::Types types, std::any& minValue, std::any& maxValue) = 0;

	virtual std::vector<std::shared_ptr<orm::core::Property>>
		queryRange(const std::string& attribute, orm::core::Types types, std::any&& minValue, std::any&& maxValue) = 0;
};

} // orm::database namespace

#endif
