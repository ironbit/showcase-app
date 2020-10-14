#include "orm/core/property.h"

namespace orm::core {

Property::Property()
{ }

Property::Property(Property&& property)
 : mProperties{std::move(property.mProperties)}
{ }

Property::Property(std::vector<std::pair<std::string, orm::core::Scalar>>&& data) {
	populate(data);
}

Property::Property(const std::vector<std::pair<std::string, orm::core::Scalar>>& data) {
	populate(data);
}

Property& Property::operator()(const std::string& attribute, const orm::core::Scalar& scalar) {
	populate(attribute, scalar);
	return *this;
}

Property& Property::operator()(std::vector<std::pair<std::string, orm::core::Scalar>>&& data) {
	populate(data);
	return *this;
}

Property& Property::operator()(const std::vector<std::pair<std::string, orm::core::Scalar>>& data) {
	populate(data);
	return *this;
}

std::size_t Property::size() {
	return mProperties.size();
}

orm::core::Scalar Property::get(const std::string& attribute) {
	return mProperties[attribute];
}

std::vector<std::string> Property::attributes() {
	std::vector<std::string> outcome;
	outcome.reserve(mProperties.size());
	for (auto it = mProperties.begin(); it != mProperties.end(); ++it) {
		outcome.push_back(it->first);
	}
	return outcome;
}

void Property::populate(const std::string& attribute, const orm::core::Scalar& scalar) {
	mProperties[attribute] = scalar;
}

void Property::populate(const std::vector<std::pair<std::string, orm::core::Scalar>>& data) {
	for (auto& pair : data) {
		mProperties[pair.first] = pair.second;
	}
}

Property GenProperty(std::vector<std::pair<std::string, orm::core::Scalar>>&& data) {
	return Property(data);
}
 
Property GenProperty(const std::vector<std::pair<std::string, orm::core::Scalar>>& data) {
	return Property(data);
}

std::shared_ptr<Property> GenShareProperty(std::vector<std::pair<std::string, orm::core::Scalar>>&& data) {
	return std::make_shared<Property>(data);
}

std::shared_ptr<Property> GenShareProperty(const std::vector<std::pair<std::string, orm::core::Scalar>>& data) {
	return std::make_shared<Property>(data);
}

} // orm::core namespace
