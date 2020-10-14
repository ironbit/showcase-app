#include "gtest/gtest.h"

#include "orm/core/property.h"
#include "orm/database/database.h"
#include "orm/database_mark/database.h"

class DatabaseTest : public ::testing::Test {
 protected:
  void SetUp() override {
		database = std::make_shared<orm::database_mark::Database>();
  }

  void TearDown() override {
     database.reset();
  }

	std::shared_ptr<orm::database::Database> database;
};

TEST_F(DatabaseTest, Insert) {
	// unique identity
	std::int64_t identity = 1234;

	// generate data
	auto data = orm::core::GenShareProperty({{"col1",(const char*)"sample"},
	                                         {"col2",(std::int32_t)9876},
	                                         {"col3",(double)3.1416}});

	// insert data
	database->insert(identity, data);

	// query data
	auto outcome = database->query(identity);

	// verify data
	ASSERT_TRUE(data->size() == outcome->size());
	for (const auto& attribute : data->attributes()) {
		ASSERT_TRUE(data->get(attribute) == outcome->get(attribute));
	}
}

TEST_F(DatabaseTest, Update) {
	// unique identity
	std::int64_t identity = 1234;

	// generate data
	auto data = orm::core::GenShareProperty({{"col1",(const char*)"sample"},
	                                         {"col2",(std::int32_t)9876},
	                                         {"col3",(double)3.1416}});

	// insert data
	database->insert(identity, data);

	// generate new data
	data = orm::core::GenShareProperty({{"col1",(const char*)"sample"},
	                                    {"col2",(std::int32_t)9876},
	                                    {"col3",(double)3.1416},
	                                    {"col4",(std::int64_t)23}});

	// insert data
	database->update(identity, data);

	// query data
	auto outcome = database->query(identity);

	// verify data
	ASSERT_TRUE(data->size() == outcome->size());
	for (const auto& attribute : data->attributes()) {
		ASSERT_TRUE(data->get(attribute) == outcome->get(attribute));
	}
}

TEST_F(DatabaseTest, Remove) {
	// unique identity
	std::int64_t identity = 1234;

	// generate data
	auto data = orm::core::GenShareProperty({{"col1",(const char*)"sample"},
	                                         {"col2",(std::int32_t)9876},
	                                         {"col3",(double)3.1416}});

	// insert data
	database->insert(identity, data);

	// remove data
	database->remove(identity);

	// query data
	auto outcome = database->query(identity);

	// verify data
	ASSERT_TRUE(outcome.operator bool() == false);
}
