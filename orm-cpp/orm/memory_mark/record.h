#ifndef ORM_STORE_MARK_RECORD
#define ORM_STORE_MARK_RECORD

#include <shared_mutex>

#include "orm/database/database.h"
#include "orm/memory/data.h"
#include "orm/memory/record.h"

namespace orm::memory_mark {

class Record : public orm::memory::Record {
public:
	Record(std::int64_t identity);

public:
	std::int64_t identity() override;

	std::vector<std::string> attributes() override;

	std::shared_ptr<orm::core::Property> get() override;

	std::shared_ptr<orm::core::Property> get(const std::vector<std::string>& attributes) override;

	void set(const std::shared_ptr<orm::core::Property>& record) override;

	void update(const std::shared_ptr<orm::core::Property>& record) override;

	void commit(orm::database::Database* db) override;

private:
	void store(const std::shared_ptr<orm::core::Property>& record);

	std::shared_ptr<orm::core::Property> fetch(const std::vector<std::string>& attributes = std::vector<std::string>());

private:
	std::shared_mutex mMutex;
	orm::memory::Data mData;
};

} // orm::memory_mark namespace

#endif
