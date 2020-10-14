#ifndef ORM_MEMORY_DATA
#define ORM_MEMORY_DATA

#include <map>
#include <string>
#include <vector>

#include "orm/core/scalar.h"

namespace orm::memory {

class Data {
public:
	Data(std::int64_t identity);

public:
	std::int64_t identity();

	std::vector<std::string> attributes();

public:
	void clear();

	Data& set(const std::string& name, const orm::core::Scalar& scalar);
	
	orm::core::Scalar get(const std::string& name);

private:
	std::int64_t mIdentity;
	std::map<std::string, orm::core::Scalar> mValues;
};

} // orm::memory namespace

#endif
