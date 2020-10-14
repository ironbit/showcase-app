#include "orm/core/scalar.h"

namespace orm::core {

Scalar::Scalar()
: mValue{0}, mToken{Token::Integer64}
{ }

bool operator==(const Scalar& lhs, const Scalar& rhs) {
	if (lhs.mToken != rhs.mToken) {
		return false;
	}

	return orm::core::applier(lhs.mToken, Compare{}, lhs, rhs);
}

} // orm::core namespace
