#include "gtest/gtest.h"

#include <memory>
#include <cstring>

#include "orm/store/store.h"
#include "orm/store_mark/store.h"
#include "orm/store_test/person.h"

using ::testing::Return;

MATCHER_P(CompareProperty, expected, "") {
	try {
		for (const auto& attribute : PersonCoder::attributes) {
			if (!(arg->get(attribute) == expected->get(attribute))) {
				return false;
			}
		}
		return true;
	} catch(const std::bad_variant_access& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
}

class StoreInterfaceTest : public ::testing::Test {
public:
	// create data
	const std::int64_t ID = 1234;
	const std::int32_t AGE = 30;
	const std::string NAME = "Christian";
	const double HEIGHT = 1.80;
};

using ::testing::Matcher;

TEST_F(StoreInterfaceTest, EncodeTest) {
	// retrieve mock
	std::shared_ptr<orm::store::Store> store = std::make_shared<orm::store_mark::Store>();
	auto& mock = static_cast<orm::store_mark::Store*>(store.get())->mock();

	// populate data
	Person person(ID);
	person.age() = AGE;
	person.name() = NAME;
	person.height() = HEIGHT;
	
	// create expected result
	auto expectedProperty = orm::core::GenShareProperty({{PersonCoder::Age, AGE},
	                                                     {PersonCoder::Name, NAME},
	                                                     {PersonCoder::Height, HEIGHT}});

	// test
	EXPECT_CALL(mock, insert(ID, Matcher<std::shared_ptr<orm::core::Property>&&>(CompareProperty(expectedProperty))));

	// execute main action
	store->insert(person);
}

TEST_F(StoreInterfaceTest, DecodeTest) {
	// retrieve mock
	std::shared_ptr<orm::store::Store> store = std::make_shared<orm::store_mark::Store>();
	auto& mock = static_cast<orm::store_mark::Store*>(store.get())->mock();

	// populate data
	Person person(ID);
	
	// create expected result
	auto expectedProperty = orm::core::GenShareProperty({{PersonCoder::Age, AGE},
	                                                     {PersonCoder::Name, NAME},
	                                                     {PersonCoder::Height, HEIGHT}});

	// mock value
	EXPECT_CALL(mock, query(ID))
	           .WillOnce(Return(expectedProperty));

	// execute main action
	store->query(person);

	// test populated object
	ASSERT_TRUE(person.identity() == ID);
	ASSERT_TRUE(person.age() == AGE);
	ASSERT_TRUE(person.name() == NAME);
	ASSERT_TRUE(person.height() == HEIGHT);
}
