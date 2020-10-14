#ifndef ORM_DATABASE_MARK_DATABASE
#define ORM_DATABASE_MARK_DATABASE

#include <any>
#include <map>
#include <optional>
#include <set>
#include <shared_mutex>
#include <string>

#include "orm/database/database.h"

namespace orm::database_mark {

class Database : public orm::database::Database {
public:
	std::optional<std::shared_ptr<orm::core::Property>> query(std::int64_t identity) override;

	bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) override;

	virtual bool update(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) override;

	virtual bool remove(std::int64_t identity) override;

public:
	std::vector<std::shared_ptr<orm::core::Property>>
		queryRange(std::int64_t min, std::int64_t max) override;

	std::vector<std::shared_ptr<orm::core::Property>>
		queryRange(const std::string& attribute, orm::core::Types types, std::any& minValue, std::any& maxValue) override;

	std::vector<std::shared_ptr<orm::core::Property>>
		queryRange(const std::string& attribute, orm::core::Types types, std::any&& minValue, std::any&& maxValue) override;

protected:
	std::shared_ptr<orm::core::Property> retrieveRecord(std::int64_t index);

private:
	std::shared_mutex mMutex;
	std::set<std::int64_t> mIdentities;
	std::map<std::int64_t, std::map<std::string, std::any>> mData;
};

} // orm::database_mark namespace

#endif
