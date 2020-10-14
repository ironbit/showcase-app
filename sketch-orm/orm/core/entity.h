#ifndef ORM_CORE_ENTITY
#define ORM_CORE_ENTITY

namespace orm::core {

class Entity {
public:
	virtual std::int64_t identity() const = 0;
};

} // orm::core namespace

#endif
