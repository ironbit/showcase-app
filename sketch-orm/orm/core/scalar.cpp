#include "orm/core/scalar.h"

namespace orm::core {

Scalar::Scalar()
 : mValue{0}, mToken{Token::Integer64}
{ }

Scalar::Scalar(const char* data)
 : mValue{(const char*)data}, mToken{Token::String}
{ }

Scalar::Scalar(std::string&& data)
 : mValue{(const char*)data.c_str()}, mToken{Token::String}
{ }

Scalar::Scalar(const std::string& data)
 : mValue{(const char*)data.c_str()}, mToken{Token::String}
{ }

bool operator==(const Scalar& lhs, const Scalar& rhs) {
	if (lhs.mToken != rhs.mToken) {
		return false;
	}
	return orm::core::applier(lhs.mToken, Compare{}, lhs, rhs);
}

} // orm::core namespace
