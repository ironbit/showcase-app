#include "orm/store_test/person.h"

Person::Person(std::int32_t identity)
 : mIdentity{identity}
{ }

std::int64_t Person::identity() const {
	return mIdentity;
}

std::string& Person::name() {
	return mName;
}

std::int32_t& Person::age() {
	return mAge;
}

double& Person::height() {
	return mHeight;
}

std::shared_ptr<orm::core::Property> PersonCoder::encode(Person& person) {
	auto outcome = std::make_shared<orm::core::Property>();
	(*outcome)(Age, person.age());
	(*outcome)(Name, person.name());
	(*outcome)(Height, person.height());
	return outcome;
}

void PersonCoder::decode(Person& person, const std::shared_ptr<orm::core::Property>& properties) {
	person.age() = properties->get(Age).To<std::int32_t>();
	person.name() = std::string(properties->get(Name).To<const char*>());
	person.height() = properties->get(Height).To<double>();
}
