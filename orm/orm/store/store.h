#ifndef ORM_STORE_STORE
#define ORM_STORE_STORE

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "orm/core/coder.h"
#include "orm/core/property.h"
#include "orm/core/types.h"

namespace orm::store {

// class Store;

// class Functor {
// public:
// 	virtual void operator()(Store* store) = 0;
// };

class Store {
public:
	virtual ~Store() {}

public:
	virtual std::shared_ptr<orm::core::Property> query(std::int64_t identity) = 0;

	virtual bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) = 0;

	virtual bool update(std::int64_t identity, orm::core::Property&& record) = 0;

	virtual bool remove(std::int64_t identity) = 0;

public:
	template <typename T>
	bool insert(T& object) {
		orm::core::Coder<typename T::Coder> coder;
		return insert(object.identity(), coder.encode(object));
	}

	template <typename T>
	void query(T& object) {
		auto properties = query(object.identity());

		orm::core::Coder<typename T::Coder> coder;
		coder.decode(object, properties);
	}
	
// public:
// 	virtual std::vector<std::shared_ptr<Store>> queryRange(std::int64_t min, std::int64_t max) = 0;
// 	virtual std::vector<std::shared_ptr<Store>> queryRange(std::string attribute, orm::core::Types types, std::any&& minValue, std::any&& maxValue) = 0;

public:
	virtual bool commit() = 0;
	
public:
	virtual std::unique_ptr<Store> clone() = 0;

// public:
// 	virtual void setOnUpdateFunctor(Functor&& functor) = 0;

// public:
// 	virtual void onUpdate() = 0;
};

} // orm::store namespace

#endif
