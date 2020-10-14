#ifndef ORM_CORE_PROPERTY
#define ORM_CORE_PROPERTY

#include <map>
#include <memory>
#include <vector>

#include "orm/core/token.h"
#include "orm/core/scalar.h"

namespace orm::core {

/**
 * REQUIRE DOC UPDATE
 * Adapter class used to gather information (literal and no literal).
 * It can be used in two modalities:
 * Property("attribute 1", 1234)("attribute 2", "sample")
 * Property({{"attribute 1", 1234}, {"attribute 2", "sample"}})
 */
class Property {
public:
	Property();

	Property(Property&& property);

public:
	template <typename T>
	Property(const std::string& attribute, const T& data) {
		populate(attribute, data);
	}

public:
	Property(std::vector<std::pair<std::string, orm::core::Scalar>>&& data);

	Property(const std::vector<std::pair<std::string, orm::core::Scalar>>& data);

public:
	Property(const Property&) = delete;

	Property& operator=(Property&&) = delete;

	Property& operator=(const Property&) = delete;

public:
	template <typename Type>
	Property& operator()(std::string&& attribute, Type&& value) {
		return operator()(attribute, value);
	}

	template <typename Type>
	Property& operator()(std::string&& attribute, const Type& value) {
		return operator()(attribute, value);
	}

	template <typename Type>
	Property& operator()(const std::string& attribute, Type&& value) {
		return operator()(attribute, value);
	}

	template <typename Type>
	Property& operator()(const std::string& attribute, const Type& value) {
		mProperties[attribute] = orm::core::Scalar{value};
		return *this;
	}

public:
	Property& operator()(const std::string& attribute, const orm::core::Scalar& scalar);

	Property& operator()(std::vector<std::pair<std::string, orm::core::Scalar>>&& data);

	Property& operator()(const std::vector<std::pair<std::string, orm::core::Scalar>>& data);

public:
	std::size_t size();

	std::vector<std::string> attributes();

	orm::core::Scalar get(const std::string& attribute);

protected:
	template <typename T>
	void populate(const std::string& attribute, const T& data) {
		mProperties[attribute] = Scalar{data};
	}

	void populate(const std::string& attribute, const orm::core::Scalar& data);

	void populate(const std::vector<std::pair<std::string, orm::core::Scalar>>& data);

private:
	std::map<std::string, orm::core::Scalar> mProperties;
};

/**
 * Helper function for the Property class.
 * Sample: property("attribute 1", 1234)("attribute 2", "string")
 * Take the first pair and populate in the Property class.
 * The next pair is processed in the operator() of the Property class.
 * 
 * @param  key    attribute name.
 * @param  value  attribute value.
 */ 
template <typename Type>
Property GenProperty(std::string&& key, Type&& value) {
	return Property(key, value);
}

/**
 * Helper function for the Property class.
 * Sample: property("attribute 1", 1234)("attribute 2", "string")
 * Take the first pair and populate in the Property class.
 * The next pair is processed in the operator() of the Property class.
 *
 * @param  key    attribute name.
 * @param  value  attribute value.
 */ 
template <typename Type>
Property GenProperty(const std::string& key, Type&& value) {
	return Property(key, value);
}

/**
 * Helper function for the Property class.
 * Sample: property({{"attribute 1", 1234},{"attribute 2", "string"}})
 * Take all the data is processed in the Property class.
 * 
 * @param  data  an array of pairs, which content an attribute namme and value. 
 */ 
Property GenProperty(std::vector<std::pair<std::string, orm::core::Scalar>>&& data);

/**
 * Helper function for the Property class.
 * Sample: property({{"attribute 1", 1234},{"attribute 2", "string"}})
 * Take all the data is processed in the Property class.
 * 
 * @param  data  an array of pairs, which content an attribute namme and value. 
 */ 
Property GenProperty(const std::vector<std::pair<std::string, orm::core::Scalar>>& data);

/**
 * Factory method called "generate property" object.
 * genprop({{"attribute 1", value 1},{"attribute 2", value 2},...)
 *
 * @param  data  list of pairs, which content an attribute and a value.
 * @return       shared pointer of property type.
 */
std::shared_ptr<Property> GenShareProperty(std::vector<std::pair<std::string, orm::core::Scalar>>&& data);

/**
 * Factory method called "generate property" object.
 * genprop({{"attribute 1", value 1},{"attribute 2", value 2},...)
 *
 * @param  data  list of pairs, which content an attribute and a value.
 * @return       shared pointer of property type.
 */
std::shared_ptr<Property> GenShareProperty(const std::vector<std::pair<std::string, orm::core::Scalar>>& data);

} // orm::core namespace

#endif
