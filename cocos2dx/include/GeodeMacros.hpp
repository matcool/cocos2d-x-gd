#pragma once

#pragma warning(default : 4067)
#pragma warning(disable : 4244) // narrowing conversion

#define GEODE_FRIEND_MODIFY
#define NOMINMAX

#define GEODE_CUSTOM_CONSTRUCTOR_BEGIN(...)
#define GEODE_CUSTOM_CONSTRUCTOR_COCOS(...)

#define GEODE_DLL
#define GEODE_IS_X64

#if defined(__cplusplus)

#include <cstring>
#include <type_traits>
#include <typeinfo>
#include <memory>

namespace gd = std;

#include <source_location>
[[noreturn]] void impl_ROB_UNIMPLEMENTED(std::source_location = std::source_location::current());

#define ROB_UNIMPLEMENTED() impl_ROB_UNIMPLEMENTED()

namespace geode::cast {
    template <class Type>
    struct ShrunkPointer {
        uint32_t m_ptrOffset;

        Type* into(uintptr_t base) {
            return reinterpret_cast<Type*>(base + m_ptrOffset);
        }
    };

    struct TypeDescriptorType {
        void* m_typeinfoTable;
        intptr_t m_spare;
        char m_typeDescriptorName[0x100];
    };

    struct ClassDescriptorType;

    struct BaseClassDescriptorType {
        ShrunkPointer<TypeDescriptorType> m_typeDescriptor;
        int32_t m_numContainedBases;
        int32_t m_memberDisplacement[3];
        int32_t m_attributes;
        ShrunkPointer<ClassDescriptorType> m_classDescriptor;
    };
    
    struct BaseClassArrayType {
        ShrunkPointer<BaseClassDescriptorType> m_descriptorEntries[0x100];
    };

    struct ClassDescriptorType {
        int32_t m_signature;
        int32_t m_attributes;
        int32_t m_numBaseClasses;
        ShrunkPointer<BaseClassArrayType> m_baseClassArray;
    };

    struct CompleteLocatorType {
        int32_t m_signature;
        int32_t m_offset;
        int32_t m_cdOffset;
        ShrunkPointer<TypeDescriptorType> m_typeDescriptor;
        ShrunkPointer<ClassDescriptorType> m_classDescriptor;
    #ifdef GEODE_IS_X64
        int32_t m_locatorOffset;
    #endif
    };

    struct MetaPointerType {
        CompleteLocatorType* m_completeLocator;
    };

    struct VftableType {
        void* m_vftable[0x100];
    };

    struct CompleteVftableType : MetaPointerType, VftableType {};

    template <class After, class Before>
    inline After typeinfo_cast(Before ptr) {
        static_assert(
            std::is_polymorphic_v<std::remove_pointer_t<Before>>, "Input is not a polymorphic type"
        );

        if (!ptr) {
            return After();
        }

        auto basePtr = dynamic_cast<void const*>(ptr);
        auto vftable = *reinterpret_cast<VftableType const* const*>(basePtr);

        auto metaPtr = static_cast<MetaPointerType const*>(static_cast<CompleteVftableType const*>(vftable));

        auto afterDesc =
            reinterpret_cast<TypeDescriptorType const*>(&typeid(std::remove_pointer_t<After>));

        auto afterIdent = static_cast<char const*>(afterDesc->m_typeDescriptorName);

    #ifdef GEODE_IS_X64
        auto locatorOffset = metaPtr->m_completeLocator->m_locatorOffset;
        auto base = reinterpret_cast<uintptr_t>(metaPtr->m_completeLocator) - locatorOffset;
    #else
        auto base = 0;
    #endif

        auto classDesc = metaPtr->m_completeLocator->m_classDescriptor.into(base);
        for (int32_t i = 0; i < classDesc->m_numBaseClasses; ++i) {
            auto entry = classDesc->m_baseClassArray.into(base)->m_descriptorEntries[i].into(base);
            auto optionIdent = static_cast<char const*>(
                entry->m_typeDescriptor.into(base)->m_typeDescriptorName
            );
            auto optionOffset = entry->m_memberDisplacement[0];

            if (std::strcmp(afterIdent, optionIdent) == 0) {
                auto afterPtr = reinterpret_cast<std::byte const*>(basePtr) + optionOffset;
                return (After)(afterPtr);
            }
        }

        return nullptr;
    }
}


#endif
