#ifndef ORM_STOREMARK_FACTORY
#define ORM_STOREMARK_FACTORY

#include <memory>

#include "orm/database/database.h"
#include "orm/memory/record.h"
#include "orm/store/factory.h"
#include "orm/store/store.h"

namespace orm::store_mark {

class Factory : public orm::store::Factory {
public:
	std::unique_ptr<orm::store::Store> create() override;

public:
	Factory& resetRecord() override;

	Factory& setRecord(const std::shared_ptr<orm::memory::Record>& record) override;

	Factory& setDatabase(const std::shared_ptr<orm::database::Database>& database) override;

private:
	std::shared_ptr<orm::memory::Record> mRecord;
	std::shared_ptr<orm::database::Database> mDatabase;
};

} // orm::store_mark namespace

#endif
