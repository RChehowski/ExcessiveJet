//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "ExcessiveAssert.h"
#include "ClassReader.h"

#include <string>

namespace Compiler
{
    class CClassReader;

    enum class EConstantPoolInfoTag : u1
    {
        Utf8 = 1,
        // Note that there is no index '2'
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

        // 13, 14 are also skipped
        MethodHandle = 15,  // Java7+
        MethodType = 16,    // Java7+
        // ... and 17 also
        InvokeDynamic = 18, // Java8+

        /**
         * Number of tags, do not add new tags (except for Invalid_NotATag) after it.
         */
        Num,

        Invalid_NotATag = 255
    };

    // For debugging purposes, to fill holes in the jump table
    constexpr u1 UnusedConstantPoolInfoTags[] = { 2, 13, 14, 17 };


    class CConstantInfo
    {
    protected:
        /**
         * Constructor is protected: only callable from subclasses, no CConstantInfo instances for you.
         *
         * @param InConstantPoolInfoTag Tag to identify CConstantInfo instances.
         */
        FORCEINLINE explicit CConstantInfo(const EConstantPoolInfoTag InConstantPoolInfoTag)
            : ConstantPoolInfoTag(InConstantPoolInfoTag)
        {
        }

    public:
        CConstantInfo() = delete;
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

        static std::shared_ptr<CConstantInfo> NewConstantInfo(const EConstantPoolInfoTag ConstantPoolInfoTag);

        static constexpr const char* ConstantPoolInfoTagToString(const EConstantPoolInfoTag ConstantPoolInfoTag)
        {
            switch (ConstantPoolInfoTag)
            {
                case EConstantPoolInfoTag::Utf8:                return "Utf8";
                case EConstantPoolInfoTag::Integer:             return "Integer";
                case EConstantPoolInfoTag::Float:               return "Float";
                case EConstantPoolInfoTag::Long:                return "Long";
                case EConstantPoolInfoTag::Double:              return "Double";
                case EConstantPoolInfoTag::Class:               return "Class";
                case EConstantPoolInfoTag::String:              return "String";
                case EConstantPoolInfoTag::FieldRef:            return "FieldRef";
                case EConstantPoolInfoTag::MethodRef:           return "MethodRef";
                case EConstantPoolInfoTag::InterfaceMethodRef:  return "InterfaceMethodRef";
                case EConstantPoolInfoTag::NameAndType:         return "NameAndType";
                case EConstantPoolInfoTag::MethodHandle:        return "MethodHandle";
                case EConstantPoolInfoTag::MethodType:          return "MethodType";
                case EConstantPoolInfoTag::InvokeDynamic:       return "InvokeDynamic";

                default: return "Unknown Tag";
            }
        }

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
