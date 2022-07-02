//
// Created by ASUS on 01/02/2021.
//

#pragma once

#include "Util/Types.h"
#include "Util/SerializedArray.h"

namespace Compiler
{
    class CClassInfo;
    class CClassReader;

    class CAttributeInfo;
    using CSharedAttributeInfo = std::shared_ptr<CAttributeInfo>;

    struct EMethodAccessFlags
    {
        using Type = u2;


        // Declared public; may be accessed from outside its package.
        static constexpr Type ACC_PUBLIC          = 0x0001;

        // Declared private; accessible only within the defining class.
        static constexpr Type ACC_PRIVATE         = 0x0002;

        // Declared protected; may be accessed within subclasses.
        static constexpr Type ACC_PROTECTED       = 0x0004;

        // Declared static.
        static constexpr Type ACC_STATIC          = 0x0008;

        // Declared final; must not be overridden (§5.4.5).
        static constexpr Type ACC_FINAL           = 0x0010;

        // Declared synchronized; invocation is wrapped by a monitor use.
        static constexpr Type ACC_SYNCHRONIZED    = 0x0020;

        // A bridge method, generated by the compiler.
        static constexpr Type ACC_BRIDGE          = 0x0040;

        // Declared with variable number of arguments.
        static constexpr Type ACC_VARARGS         = 0x0080;

        // Declared native; implemented in a language other than Java.
        static constexpr Type ACC_NATIVE          = 0x0100;

        // Declared abstract; no implementation is provided.
        static constexpr Type ACC_ABSTRACT        = 0x0400;

        // Declared strictfp; floating-point mode is FP-strict.
        static constexpr Type ACC_STRICT          = 0x0800;

        // Declared synthetic; not present in the source code.
        static constexpr Type ACC_SYNTHETIC       = 0x1000;
    };

    class CMethodInfo
    {
    public:
        friend void operator>>(CClassReader& Reader, CMethodInfo& Instance);

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

        [[nodiscard]]
        FORCEINLINE const Util::TStandardSerializedArray<CSharedAttributeInfo>& GetAttributes() const
        {
            return Attributes;
        }

        template <class T>
        std::shared_ptr<T> GetAttribute() const
        {
            return CAttributeInfo::GetAttributeOfType<T>(Attributes);
        }

        template <class T>
        std::vector<std::shared_ptr<T>> GetAttributes() const
        {
            return CAttributeInfo::GetAttributesOfType<T>(Attributes);
        }

        // Sugar

        [[nodiscard]] FORCEINLINE bool IsNative() const
        {
            return Util::CMathUtils::EnumHasFlag(AccessFlags, EMethodAccessFlags::ACC_NATIVE);
        }

        [[nodiscard]]
        std::string Debug_ToString(const CClassInfo& ClassInfo) const;

    private:
        EMethodAccessFlags::Type AccessFlags = (EMethodAccessFlags::Type)0;
        u2 NameIndex        = (u2)0;
        u2 DescriptorIndex  = (u2)0;

        Util::TStandardSerializedArray<CSharedAttributeInfo> Attributes;
    };
}
