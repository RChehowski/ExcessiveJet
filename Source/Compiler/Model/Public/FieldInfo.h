//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "SerializedArray.h"
#include "Attributes/AttributeInfo.h"

#if UNLOCK_DEBUG_METHODS
    #include <string>
#endif // UNLOCK_DEBUG_METHODS

namespace Compiler
{
    class CClassReader;

#if UNLOCK_DEBUG_METHODS
    class CClassInfo;
#endif // UNLOCK_DEBUG_METHODS

    struct EFieldAccessFlags
    {
        using Type = u2;


        // Declared public; may be accessed from outside its package.
        static constexpr Type ACC_PUBLIC      = 0x0001;

        // Declared private; usable only within the defining class.
        static constexpr Type ACC_PRIVATE     = 0x0002;

        // Declared protected; may be accessed within subclasses.
        static constexpr Type ACC_PROTECTED   = 0x0004;

        // Declared static.
        static constexpr Type ACC_STATIC      = 0x0008;

        // Declared final; never directly assigned to after object construction (JLS §17.5).
        static constexpr Type ACC_FINAL       = 0x0010;

        // Declared volatile; cannot be cached.
        static constexpr Type ACC_VOLATILE    = 0x0040;

        // Declared transient; not written or read by a persistent object manager.
        static constexpr Type ACC_TRANSIENT   = 0x0080;

        // Declared synthetic; not present in the source code.
        static constexpr Type ACC_SYNTHETIC   = 0x1000;

        // Declared as an element of an enum.
        static constexpr Type ACC_ENUM        = 0x4000;
    };

    class CFieldInfo
    {
    public:
        CFieldInfo() = default;
        ~CFieldInfo() = default;

        [[nodiscard]]
        FORCEINLINE u2 GetAccessFlags() const
        {
            return AccessFlags;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameIndex() const
        {
            return NameIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
            return DescriptorIndex;
        }

        template <class T>
        std::shared_ptr<T> GetAttributeOfType() const
        {
            return CAttributeInfo::GetAttributeOfType<T>(Attributes);
        }

        template <class T>
        std::vector<std::shared_ptr<T>> GetAttributesOfType() const
        {
            return CAttributeInfo::GetAttributesOfType<T>(Attributes);
        }

        void DeserializeFrom(CClassReader& Reader);

        friend void operator>>(CClassReader& Reader, CFieldInfo& Instance);

#if UNLOCK_DEBUG_METHODS
        [[nodiscard]]
        std::string Debug_ToString(const CClassInfo& ClassInfo) const;
#endif // UNLOCK_DEBUG_METHODS

    private:
        EFieldAccessFlags::Type AccessFlags = (EFieldAccessFlags::Type)0;
        u2 NameIndex        = (u2)0;
        u2 DescriptorIndex  = (u2)0;

        Util::TStandardSerializedArray<CSharedAttributeInfo> Attributes;
    };
}
