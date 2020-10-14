#ifndef ORM_CORE_SCALAR
#define ORM_CORE_SCALAR

#include <any>
#include <variant>

#include "orm/core/mapper.h"
#include "orm/core/token.h"

namespace orm::core {

class Scalar {
public:
	Scalar();

	template <typename T>
	Scalar(const T& data)
	 : mValue{data}, mToken{MapToken<T>}
	{ }

	template <typename T>
	decltype(auto) To() {
		return std::get<T>(mValue);
	}

private:
	using variant = std::variant<std::int32_t, std::int64_t, float, double, const char*>;
	variant mValue;
	Token   mToken;

private:
	friend struct Compare;
	friend bool operator==(const Scalar& lhs, const Scalar& rhs);
};

struct Compare {
	template <typename T>
	bool operator()(const Scalar& lhs, const Scalar& rhs) {
		return std::get<T>(lhs.mValue) == std::get<T>(rhs.mValue);
	}
};

bool operator==(const Scalar& lhs, const Scalar& rhs);

} // orm::core namespace

#endif
