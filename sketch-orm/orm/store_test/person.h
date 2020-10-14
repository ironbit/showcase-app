#ifndef TEST_PERSON
#define TEST_PERSON

#include <string>
#include <vector>

#include "orm/core/coder.h"
#include "orm/core/entity.h"
#include "orm/core/token.h"

class PersonCoder;

class Person : public orm::core::Entity {
public:
	using Coder = PersonCoder;

public:
	Person(std::int32_t identity);
	std::int64_t identity() const;
	std::string& name();
	std::int32_t& age();
	double& height();

private:
	std::int64_t mIdentity;
	std::string  mName;
	std::int32_t mAge;
	double       mHeight;
};

class PersonCoder : public orm::core::Coder<PersonCoder> {
public:
	inline static const std::string Age = "age";
	inline static const std::string Name = "name";
	inline static const std::string Height = "height";

	inline static const std::vector<std::string> attributes{"age", "name", "height"};
	inline static const std::vector<orm::core::Token> types{orm::core::Token::Integer32, orm::core::Token::String, orm::core::Token::Float64};

public:
	std::shared_ptr<orm::core::Property> encode(Person& person);
	void decode(Person& person, const std::shared_ptr<orm::core::Property>& properties);
};

#endif
