#pragma once

namespace Hawk {

#define BIT(X) (1 <<X )

#define BIND_EVENT_FN(f, c) std::bind(&f, c, std::placeholders::_1)

#define BIND_EVENT_FN_DEFAULT(f) BIND_EVENT_FN(f, this)

	//TODO support other platforms such as unix etc.. 
	//TODO Enable assertions in debug mode only
#ifdef HK_ENABLE_ASSERTS
#define HK_ASSERT(clause, ...) {if(!(clause)) {HK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HK_CORE_ASSERT(clause, ...) {if(!(clause)) {HK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
#define HK_ASSERT(clause, ...)
#define HK_CORE_ASSERT(clause, ...)

#endif
	//TODO change later into respective classes
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

}





