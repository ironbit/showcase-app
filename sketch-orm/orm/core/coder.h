#ifndef ORM_CORE_CODER
#define ORM_CORE_CODER

#include <memory>

#include "orm/core/property.h"

namespace orm::core {

template <typename T>
struct Coder {
	template <typename U>
	std::shared_ptr<orm::core::Property> encode(U& u) {
		return static_cast<T*>(this)->encode(u);
	}

	template <typename U, typename V>
	void decode(U& u, V& v) {
		static_cast<T*>(this)->decode(u, v);
	}
};

} // orm::core

#endif
