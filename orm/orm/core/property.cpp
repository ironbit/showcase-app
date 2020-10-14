#include "orm/core/property.h"

namespace orm::core {

Property property(std::vector<std::pair<std::string, std::any>>&& data) {
	return Property(data);
}
 
Property property(const std::vector<std::pair<std::string, std::any>>& data) {
	return Property(data);
}

std::shared_ptr<Property> genprop(std::vector<std::pair<std::string, std::any>>&& data) {
	return std::make_shared<Property>(data);
}

std::shared_ptr<Property> genprop(const std::vector<std::pair<std::string, std::any>>& data) {
	return std::make_shared<Property>(data);
}

} // orm::core namespace
