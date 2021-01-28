//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Types.h"
#include "ClassReader.h"
#include "SerializedArray.h"
#include "Attributes/AttributeInfo.h"

class CClassReader;

namespace Parse
{
    struct EFieldAccessFlag
    {
        // Declared public; may be accessed from outside its package.
        static constexpr u2 ACC_PUBLIC      = 0x0001;

        // Declared private; usable only within the defining class.
        static constexpr u2 ACC_PRIVATE     = 0x0002;

        // Declared protected; may be accessed within subclasses.
        static constexpr u2 ACC_PROTECTED   = 0x0004;

        // Declared static.
        static constexpr u2 ACC_STATIC      = 0x0008;

        // Declared final; never directly assigned to after object construction (JLS §17.5).
        static constexpr u2 ACC_FINAL       = 0x0010;

        // Declared volatile; cannot be cached.
        static constexpr u2 ACC_VOLATILE    = 0x0040;

        // Declared transient; not written or read by a persistent object manager.
        static constexpr u2 ACC_TRANSIENT   = 0x0080;

        // Declared synthetic; not present in the source code.
        static constexpr u2 ACC_SYNTHETIC   = 0x1000;

        // Declared as an element of an enum.
        static constexpr u2 ACC_ENUM        = 0x4000;
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

//        [[nodiscard]]
//        FORCEINLINE u2 GetAttributesCount() const
//        {
//            return AttributesCount;
//        }

        void DeserializeFrom(CClassReader& Reader);

        friend void operator>>(CClassReader& Reader, CFieldInfo& Instance);

    private:
        u2 AccessFlags = (u2)0;
        u2 NameIndex = (u2)0;
        u2 DescriptorIndex = (u2)0;

        Util::TStandardSerializedArray<std::shared_ptr<CAttributeInfo>> Attributes;
    };
}
