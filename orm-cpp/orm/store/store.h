#ifndef ORM_STORE_STORE
#define ORM_STORE_STORE

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "orm/core/coder.h"
#include "orm/core/property.h"

namespace orm::store {

class Store {
public:
	virtual ~Store() {}

public:
	virtual std::shared_ptr<orm::core::Property> query(std::int64_t identity = 0) = 0;

	virtual bool commit() = 0;

public:
	virtual std::shared_ptr<orm::core::Property> fetch() = 0;

	virtual bool insert(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) = 0;

	virtual bool insert(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) = 0;

	virtual bool update(std::int64_t identity, std::shared_ptr<orm::core::Property>&& record) = 0;

	virtual bool update(std::int64_t identity, const std::shared_ptr<orm::core::Property>& record) = 0;

	virtual bool remove(std::int64_t identity) = 0;

public:
	virtual std::unique_ptr<Store> clone() = 0;

public:
	template <typename T>
	void query(T& object) {
		orm::core::Coder<typename T::Coder> coder;
		coder.decode(object, query(object.identity()));
	}

	template <typename T>
	bool insert(T& object) {
		orm::core::Coder<typename T::Coder> coder;
		return insert(object.identity(), coder.encode(object));
	}

	template <typename T>
	bool update(T& object) {
		orm::core::Coder<typename T::Coder> coder;
		return update(object.identity(), coder.encode(object));
	}
};

} // orm::store namespace

#endif
