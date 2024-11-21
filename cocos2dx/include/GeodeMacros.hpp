#pragma once


#define GEODE_FRIEND_MODIFY

#define GEODE_CUSTOM_CONSTRUCTOR_BEGIN(...)
#define GEODE_CUSTOM_CONSTRUCTOR_COCOS(...)

#define GEODE_DLL

// namespace gd = std;
#define gd std

#if defined(__cplusplus)

#include <source_location>
[[noreturn]] void impl_ROB_UNIMPLEMENTED(std::source_location = std::source_location::current());

#define ROB_UNIMPLEMENTED() impl_ROB_UNIMPLEMENTED()

#endif
