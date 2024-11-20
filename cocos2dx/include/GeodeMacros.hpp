#pragma once

#define GEODE_FRIEND_MODIFY

#define GEODE_CUSTOM_CONSTRUCTOR_BEGIN(...)
#define GEODE_CUSTOM_CONSTRUCTOR_COCOS(...)

#define GEODE_DLL

// namespace gd = std;
#define gd std

#define ROB_UNIMPLEMENTED() { \
    CCLOG("Unimplemented function %s at %s:%d", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
    std::abort(); \
}