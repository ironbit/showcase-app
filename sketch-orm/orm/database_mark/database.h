#ifndef ORM_DATABASE_MARK_DATABASE
#define ORM_DATABASE_MARK_DATABASE

#include <map>
#include <shared_mutex>
#include <string>

#include "orm/core/scalar.h"
#include "orm/database/database.h"

namespace orm::database_mark {

class Database : public orm::database::Database {
public:
	std::shared_ptr<orm::core::Property> query(std::int64_t identity) override;

	bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) override;

	virtual bool update(std::int64_t identity, std::shared_ptr<orm::core::Property>& record) override;

	virtual bool remove(std::int64_t identity) override;

protected:
	std::shared_ptr<orm::core::Property> retrieveRecord(std::int64_t index);

private:
	std::shared_mutex mMutex;
	std::map<std::int64_t, std::map<std::string, orm::core::Scalar>> mData;
};

} // orm::database_mark namespace

#endif
