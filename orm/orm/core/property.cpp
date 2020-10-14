#include "orm/core/property.h"

namespace orm::core {

Property property(std::vector<std::pair<std::string, std::any>>&& data) {
	return Property(data);
}
 
Property property(const std::vector<std::pair<std::string, std::any>>& data) {
	return Property(data);
}

} // orm::core namespace
