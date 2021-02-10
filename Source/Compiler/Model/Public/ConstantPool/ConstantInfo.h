//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Types.h"
#include "Assert.h"
#include "ClassReader.h"

#include <string>

namespace Compiler
{
    class CClassReader;

    enum class EConstantPoolInfoTag : u1
    {
        Utf8 = 1,
        Integer = 3,
        Float = 4,
        Long = 5,
        Double = 6,
        Class = 7,
        String = 8,
        FieldRef = 9,
        MethodRef = 10,
        InterfaceMethodRef = 11,
        NameAndType = 12,
        MethodHandle = 15,
        MethodType = 16,
        InvokeDynamic = 18,

        Invalid_NotATag = 255
    };


    class CConstantInfo
    {
    public:
        FORCEINLINE explicit CConstantInfo(const EConstantPoolInfoTag InConstantPoolInfoTag)
            : ConstantPoolInfoTag(InConstantPoolInfoTag)
        {
        }

        virtual ~CConstantInfo() = default;

        [[nodiscard]]
        FORCEINLINE EConstantPoolInfoTag GetConstantPoolInfoTag() const
        {
            return ConstantPoolInfoTag;
        }

        [[nodiscard]]
        virtual std::string ToString() const = 0;

        virtual void DeserializeFrom(CClassReader& Reader) = 0;

        [[nodiscard]]
        FORCEINLINE bool IsA(EConstantPoolInfoTag InConstantPoolInfoTag) const
        {
            return GetConstantPoolInfoTag() == InConstantPoolInfoTag;
        }

        template<typename T>
        [[nodiscard]]
        FORCEINLINE bool IsA() const
        {
            if constexpr (std::is_base_of_v<CConstantInfo, T>)
            {
                return IsA(T::StaticTag);
            }
            else
            {
                return false;
            }
        }

        static std::shared_ptr<CConstantInfo> NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag);

        static const char* ConstantPoolInfoTagToString(EConstantPoolInfoTag ConstantPoolInfoTag);

        template <typename T>
        static std::shared_ptr<T> CastConstantInfo(const std::shared_ptr<CConstantInfo>& ConstantInfo)
        {
            static_assert(std::is_base_of_v<CConstantInfo, T>, "T must be a subclass of CConstantInfo");

            ASSERT(ConstantInfo != nullptr);

            ASSERT_MSG(ConstantInfo->IsA<T>(),
                "Cannot cast \"%s\" to \"%s\". You can only cast from base CConstantInfo to it's subtype.",
                ConstantPoolInfoTagToString(ConstantInfo->ConstantPoolInfoTag),
                ConstantPoolInfoTagToString(T::StaticTag)
            );

            return std::static_pointer_cast<T>(ConstantInfo);
        }

        friend void operator>>(CClassReader& Reader, CConstantInfo& Instance);

    private:
        const EConstantPoolInfoTag ConstantPoolInfoTag;
    };
}
