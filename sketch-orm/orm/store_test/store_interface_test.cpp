#include "gtest/gtest.h"

#include <memory>
#include <cstring>

#include "orm/core/cast.h"
#include "orm/core/coder.h"
#include "orm/core/entity.h"
#include "orm/store/store.h"
#include "orm/store_mark/store.h"

using ::testing::Return;

class PersonCoder;

class Person : public orm::core::Entity {
public:
	using Coder = PersonCoder;

public:
	Person(std::int32_t identity)
	: mIdentity{identity}
	{ }

	std::int64_t identity() const {
		return mIdentity;
	}

	std::string& name() {
		return mName;
	}

	std::int32_t& age() {
		return mAge;
	}

	double& height() {
		return mHeight;
	}

private:
	std::int64_t mIdentity;
	std::string  mName;
	std::int32_t mAge;
	double       mHeight;
};

class PersonCoder : public orm::core::Coder<PersonCoder> {
public:
	inline static const std::string Age = "age";
	inline static const std::string Name = "name";
	inline static const std::string Height = "height";

public:
	std::shared_ptr<orm::core::Property> encode(Person& person) {
		auto outcome = std::make_shared<orm::core::Property>();
		(*outcome)(Age, person.age());
		(*outcome)(Name, person.name());
		(*outcome)(Height, person.height());
		return outcome;
	}

	void decode(Person& person, std::shared_ptr<orm::core::Property>& properties) {
		person.age() = std::any_cast<std::int32_t>(properties->get(Age));
		person.name() = std::any_cast<std::string>(properties->get(Name));
		person.height() = std::any_cast<double>(properties->get(Height));
	}
};

MATCHER_P(CompareProperty, expected, "") {
	try {
		auto data = static_cast<std::shared_ptr<orm::core::Property>>(arg);
		if (std::any_cast<std::int32_t>(arg->get(PersonCoder::Age)) != std::any_cast<std::int32_t>(expected->get(PersonCoder::Age))) {
			return false;
		}
		if (std::any_cast<std::string>(arg->get(PersonCoder::Name)) != std::any_cast<std::string>(expected->get(PersonCoder::Name))) {
			return false;
		}
		if (std::any_cast<double>(arg->get(PersonCoder::Height)) != std::any_cast<double>(expected->get(PersonCoder::Height))) {
			return false;
		}
	} catch (const std::bad_any_cast& e) {
		std::cout << "bad cast: " << e.what() << std::endl;
		return false;
	}
	return true;
}

class StoreInterfaceTest : public ::testing::Test {
public:
	// create data
	const std::int64_t ID = 1234;
	const std::int32_t AGE = 30;
	const std::string NAME = "Christian";
	const double HEIGHT = 1.80;
};

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
	auto expectedProperty = orm::core::genprop({{PersonCoder::Age, AGE},{PersonCoder::Name, NAME},{PersonCoder::Height, HEIGHT}});

	// test
	EXPECT_CALL(mock, insert(ID, CompareProperty(expectedProperty)));

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
	auto expectedProperty = orm::core::genprop({{PersonCoder::Age, AGE},{PersonCoder::Name, NAME},{PersonCoder::Height, HEIGHT}});

	// mock value
	EXPECT_CALL(mock, query(ID))
							.WillOnce(Return(expectedProperty));

	// execute main action
	store->query(person);

	// test populated object
	ASSERT_THAT(person.identity(), ID);
	ASSERT_THAT(person.age(), AGE);
	ASSERT_THAT(person.name(), NAME);
	ASSERT_THAT(person.height(), HEIGHT);
}
