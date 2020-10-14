#ifndef ORM_CORE_MAPPER
#define ORM_CORE_MAPPER

#include <cstdint>
#include <string>

#include "orm/core/token.h"

namespace orm::core {

template <orm::core::Token T>
struct MapTokenToType {
	using Type = std::int64_t;
};

template <>
struct MapTokenToType<Token::Integer32> {
	using Type = std::int32_t;
};

template <>
struct MapTokenToType<Token::Integer64> {
	using Type = std::int64_t;
};

template <>
struct MapTokenToType<Token::Float32> {
	using Type = float;
};

template <>
struct MapTokenToType<Token::Float64> {
	using Type = double;
};

template <>
struct MapTokenToType<Token::String> {
	using Type = const char*;
};

template <orm::core::Token T>
using MapType = typename MapTokenToType<T>::Type;


template <typename T>
struct MapTypeToToken {};

template <>
struct MapTypeToToken<std::int32_t> {
	static constexpr orm::core::Token Token = orm::core::Token::Integer32;
};

template <>
struct MapTypeToToken<std::int64_t> {
	static constexpr orm::core::Token Token = orm::core::Token::Integer64;
};

template <>
struct MapTypeToToken<float> {
	static constexpr orm::core::Token Token = orm::core::Token::Float32;
};

template <>
struct MapTypeToToken<double> {
	static constexpr orm::core::Token Token = orm::core::Token::Float64;
};

template <>
struct MapTypeToToken<const char*> {
	static constexpr orm::core::Token Token = orm::core::Token::String;
};

template <typename T>
inline constexpr orm::core::Token MapToken = MapTypeToToken<T>::Token;


template <typename Functor, typename ... Args>
decltype(auto) applier(orm::core::Token token, Functor functor, Args&& ... args) {
	switch (token) {
		case Token::Integer32:
			return functor.template operator()<MapType<Token::Integer32>>(std::forward<Args>(args)...);
		case Token::Integer64:
			return functor.template operator()<MapType<Token::Integer64>>(std::forward<Args>(args)...);
		case Token::Float32:
			return functor.template operator()<MapType<Token::Float32>>(std::forward<Args>(args)...);
		case Token::Float64:
			return functor.template operator()<MapType<Token::Float64>>(std::forward<Args>(args)...);
		case Token::String:
			return functor.template operator()<MapType<Token::String>>(std::forward<Args>(args)...);
	}
}

} // orm::core

#endif
