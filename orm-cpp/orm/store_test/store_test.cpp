#include "gtest/gtest.h"

#include "orm/core/scalar.h"
#include "orm/core/property.h"
#include "orm/store_mark/factory.h"
#include "orm/database_mark/database.h"
#include "orm/store_test/person.h"

using orm::core::Scalar;
using orm::core::Token;

class StoreTest : public ::testing::Test {
public:
  void SetUp() override {
		database = std::make_shared<orm::database_mark::Database>();
		factory = std::make_shared<orm::store_mark::Factory>();
		factory->setDatabase(database);
		populate();
  }

  void TearDown() override {
     database.reset();
		 factory.reset();
  }

	void populate() {
		identities.emplace_back(10);
		identities.emplace_back(11);
		identities.emplace_back(12);

		persons.emplace_back(orm::core::GenShareProperty({{PersonCoder::Age, 30},
		                                                  {PersonCoder::Name, "Christian"},
		                                                  {PersonCoder::Height, 1.8}}));

		persons.emplace_back(orm::core::GenShareProperty({{PersonCoder::Age, 40},
		                                                  {PersonCoder::Name, "Maria"},
		                                                  {PersonCoder::Height, 1.5}}));

		persons.emplace_back(orm::core::GenShareProperty({{PersonCoder::Age, 20},
		                                                  {PersonCoder::Name, "Susan"},
		                                                  {PersonCoder::Height, 1.6}}));
	}

	void saveToDatabase() {
		for (std::size_t i = 0; i < persons.size(); ++i) {
			database->insert(identities[i], persons[i]);
		}
	}

	std::shared_ptr<orm::store::Factory> factory;
	std::shared_ptr<orm::database::Database> database;

	std::vector<std::int64_t> identities;
	std::vector<std::shared_ptr<orm::core::Property>> persons;
};

TEST_F(StoreTest, FunctionalInsertTest) {
	// create store
	auto store = factory->create();

	// use insert function
	for (std::size_t i = 0; i < persons.size(); ++i) {
		store->insert(identities[i], persons[i]);
		store->commit();
	}

	// retrieve records from database
	for (std::size_t i = 0; i < persons.size(); ++i) {
		auto record = store->query(identities[i]);
		for (const auto& attribute : persons[i]->attributes()) {
			ASSERT_TRUE(persons[i]->get(attribute) == record->get(attribute));
		}
	}
}

TEST_F(StoreTest, FunctionalUpdateTest) {
	// create store
	auto store = factory->create();

	// constants
	auto identity = identities[0];

	// use insert function
	store->insert(identity, persons[0]);
	store->commit();

	// use update function
	store->update(identity, persons[1]);
	store->commit();

	// test id 0 with the record of person 1
	auto data = store->query(identity);
	for (const auto& attribute : persons[1]->attributes()) {
		ASSERT_TRUE(persons[1]->get(attribute) == data->get(attribute));
	}
}

TEST_F(StoreTest, FunctionalCloneSibling) {
	// store all record in database
	saveToDatabase();

	// constants
	std::int32_t age = 25;
	auto id = identities[0];

	// create main store
	auto store_1 = factory->create();
	store_1->query(id);

	// create sibling store
	auto store_2 = store_1->clone();

	// update record using store 2
	store_2->update(id, orm::core::GenShareProperty({{PersonCoder::Age, age}}));

	// test if 'age' attribute changed (store 1)
	auto record = store_1->fetch();
	ASSERT_TRUE(record->get(PersonCoder::Age) == age);
}

TEST_F(StoreTest, FunctionalCloneSiblingDatabase) {
	// store all record in database
	saveToDatabase();

	// constants
	std::int32_t age = 25;
	auto id = identities[0];

	// create main store
	auto store_1 = factory->create();
	store_1->query(id);

	// create sibling store
	auto store_2 = store_1->clone();

	// update record using store 2
	store_2->update(id, orm::core::GenShareProperty({{PersonCoder::Age, age}}));
	store_2->commit();

	// test if 'age' attribute changed (store 1)
	auto record = store_1->query();
	for (const auto& attribute : PersonCoder::attributes) {
		if (attribute == PersonCoder::Age) {
			ASSERT_TRUE(record->get(attribute) == age);
		} else {
			ASSERT_TRUE(record->get(attribute) == persons[0]->get(attribute));
		}
	}
}

TEST_F(StoreTest, FunctionalCloneBrokeLink) {
	// store all record in database
	saveToDatabase();

	// constants
	std::int32_t age = 55;
	auto id_1 = identities[0];
	auto id_2 = identities[1];

	// create main store
	auto store_1 = factory->create();
	store_1->query(id_1);

	// create sibling store
	auto store_2 = store_1->clone();
	store_2->update(id_1, orm::core::GenShareProperty({{PersonCoder::Age, age}}));

	// broke link with store_1
	store_2->query(id_2);

	// test store_1
	// person[0] and age == 55
	auto record_1 = store_1->fetch();
	for (const auto& attribute : PersonCoder::attributes) {
		if (attribute == PersonCoder::Age) {
			ASSERT_TRUE(record_1->get(attribute) == age);
		} else {
			ASSERT_TRUE(record_1->get(attribute) == persons[0]->get(attribute));
		}
	}

	// test store_2
	// person[1]
	auto record_2 = store_2->fetch();
	for (const auto& attribute : PersonCoder::attributes) {
		ASSERT_TRUE(record_2->get(attribute) == persons[1]->get(attribute));
	}
}

TEST_F(StoreTest, FunctionalCloneBrokeLinkDatabase) {
	// store all record in database
	saveToDatabase();

	// constants
	std::int32_t age = 55;
	auto id_1 = identities[0];
	auto id_2 = identities[1];

	// create main store
	auto store_1 = factory->create();
	store_1->query(id_1);

	// create sibling store (id_1)
	auto store_2 = store_1->clone();
	store_2->update(id_1, orm::core::GenShareProperty({{PersonCoder::Age, age}}));
	store_2->commit();

	// broke link with store_1
	store_2->query(id_2);

	// test store_1
	// person[0] and age == 55
	auto record_1 = store_1->query();
	for (const auto& attribute : PersonCoder::attributes) {
		if (attribute == PersonCoder::Age) {
			ASSERT_TRUE(record_1->get(attribute) == age);
		} else {
			ASSERT_TRUE(record_1->get(attribute) == persons[0]->get(attribute));
		}
	}

	// test store_2
	// person[1]
	auto record_2 = store_2->fetch();
	for (const auto& attribute : PersonCoder::attributes) {
		ASSERT_TRUE(record_2->get(attribute) == persons[1]->get(attribute));
	}
}
