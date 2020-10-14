#include "orm/memory/data.h"

#include <vector>

namespace orm::memory {

Data::Data(std::int64_t identity)
 : mIdentity{identity}
{ }

std::int64_t Data::identity() {
	return mIdentity;
}

std::vector<std::string> Data::attributes() {
	std::vector<std::string> outcome;
	outcome.reserve(mValues.size());
	
	for (auto& pair : mValues) {
		outcome.emplace_back(pair.first);
	}

	return outcome;
}

void Data::clear() {
	mValues.clear();
}

Data& Data::set(const std::string& name, const orm::core::Scalar& scalar) {
	mValues[name] = scalar;
	return *this;
}

orm::core::Scalar Data::get(const std::string& name) {
	auto iterator = mValues.find(name);
	if (iterator == mValues.end()) {
		return orm::core::Scalar{};
	}
	return iterator->second;
}

} // orm::memory namespace
