#include "gtest/gtest.h"

#include <any>
#include <string>
#include <vector>

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

TEST_F(DatabaseTest, InsertQuery) {
	// unique identity
	std::int64_t identity = 1234;

	// generate data
	auto data = std::shared_ptr<orm::core::Property>(new orm::core::Property({{"col1", "sample"}, {"col2", 9876}, {"col3", 3.14}}));
	
	// insert data
	database->insert(identity, data);

	// query data
	auto outcome = database->query(identity);

	// verify data
	ASSERT_EQ(std::any_cast<const char*>((*outcome)->get("col1")), std::any_cast<const char*>(data->get("col1")));
	ASSERT_EQ(std::any_cast<int>((*outcome)->get("col2")), std::any_cast<int>(data->get("col2")));
	ASSERT_EQ(std::any_cast<double>((*outcome)->get("col3")), std::any_cast<double>(data->get("col3")));
}
