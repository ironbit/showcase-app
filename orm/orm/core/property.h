#ifndef ORM_CORE_PROPERTY
#define ORM_CORE_PROPERTY

#include <any>
#include <map>
#include <vector>

#include "orm/core/types.h"

namespace orm::core {

/**
 * Future development.
 * store the value and the type. 
 */
struct Data {
	std::any value;
	orm::core::Types type;
};

/**
 * Adapter class used to gather information (literal and no literal).
 * It can be used in two modalities:
 * Property("attribute 1", 1234)("attribute 2", "sample")
 * Property({{"attribute 1", 1234}, {"attribute 2", "sample"}})
 */
class Property {
public:
	Property() {}

	Property(std::vector<std::pair<std::string, std::any>>&& data) {
		populate(data);
	}

	Property(const std::vector<std::pair<std::string, std::any>>& data) {
		populate(data);
	}

public:
	template <typename Type>
	Property& operator()(const std::string& attribute, const Type& value) {
		mProperties[attribute] = value;
		return *this;
	}

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
		mProperties[attribute] = value;
		return *this;
	}

	Property& operator()(std::vector<std::pair<std::string, std::any>>&& data) {
		populate(data);
		return *this;
	}

	Property& operator()(const std::vector<std::pair<std::string, std::any>>& data) {
		populate(data);
		return *this;
	}

public:
	std::any get(const std::string& attribute) {
		return mProperties[attribute];
	}

	std::vector<std::string> attributes() {
		std::vector<std::string> outcome;
		outcome.reserve(mProperties.size());
		for (auto it = mProperties.begin(); it != mProperties.end(); ++it) {
			outcome.push_back(it->first);
		}
		return outcome;
	}

protected:
	void populate(const std::vector<std::pair<std::string, std::any>>& data) {
		for (auto& pair : data) {
			mProperties[pair.first] = pair.second;
		}
	}

private:
	std::map<std::string, std::any> mProperties;
	//std::map<std::string, std::pair<std::any, std::any>> mRanges;
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
Property property(std::string&& key, Type&& value) {
	Property record;
	return record(key, value);
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
Property property(const std::string& key, Type&& value) {
	Property record;
	return record(key, value);
}

/**
 * Helper function for the Property class.
 * Sample: property({{"attribute 1", 1234},{"attribute 2", "string"}})
 * Take all the data is processed in the Property class.
 * 
 * @param  data  an array of pairs, which content an attribute namme and value. 
 */ 
Property property(std::vector<std::pair<std::string, std::any>>&& data);

/**
 * Helper function for the Property class.
 * Sample: property({{"attribute 1", 1234},{"attribute 2", "string"}})
 * Take all the data is processed in the Property class.
 * 
 * @param  data  an array of pairs, which content an attribute namme and value. 
 */ 
Property property(const std::vector<std::pair<std::string, std::any>>& data);


// template <typename T, typename U>
// Property property(std::string&& key, T&& valueT, U&& valueU) {
// 	Property property;
// 	return property(key, valueT, valueU);
// }

// template <typename T, typename U>
// Property property(const std::string& key, T&& valueT, U&& valueU) {
// 	Property property;
// 	return property(key, valueT, valueU);
// }

} // orm::core namespace

#endif
