//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "Util/ExcessiveAssert.h"
#include "Model/ClassReader.h"

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
         * Number of tags, do not add new tags (except for Phantom) after it.
         */
        Num,

        // Used to pad Double and Long infos
        Phantom
    };

    class CPhantomConstantInfo;

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
        virtual std::string ToLowLevelString() const = 0;

        [[nodiscard]]
        virtual std::string ToResolvedString(const CConstantPool& ConstantPool) const = 0;

        virtual void DeserializeFrom(CClassReader &Reader) = 0;

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
                if constexpr (std::is_same_v<CConstantInfo, T>)
                {
                    // CConstantInfo is always a CConstantInfo. No exceptions!
                    return true;
                }
                else
                {
                    return IsA(T::StaticTag);
                }
            }
            else
            {
                // It's certainly not an instance if it's base class is not a CConstantInfo.
                return false;
            }
        }

        /** Checks if a constant info must be followed with a phantom constant info */
        [[nodiscard]] FORCEINLINE bool IsFollowedByPhantomInfo() const
        {
            // We cannot do IsA<> because we don't yet know about Long and Double subclasses of a CConstantInfo
            switch (GetTag())
            {
                case EConstantPoolInfoTag::Long:
                case EConstantPoolInfoTag::Double:
                    return true;
                default:
                    return false;
            }
        }

        [[nodiscard]]
        FORCEINLINE EConstantPoolInfoTag GetTag() const
        {
            return ConstantPoolInfoTag;
        }

        [[nodiscard]]
        FORCEINLINE const char *GetTagString() const
        {
            return ConstantPoolInfoTagToString(GetTag());
        }

        static CConstantInfo *NewConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag);

        static constexpr const char *ConstantPoolInfoTagToString(const EConstantPoolInfoTag ConstantPoolInfoTag)
        {
            switch (ConstantPoolInfoTag)
            {
                case EConstantPoolInfoTag::Utf8:
                    return "Utf8";
                case EConstantPoolInfoTag::Integer:
                    return "Integer";
                case EConstantPoolInfoTag::Float:
                    return "Float";
                case EConstantPoolInfoTag::Long:
                    return "Long";
                case EConstantPoolInfoTag::Double:
                    return "Double";
                case EConstantPoolInfoTag::Class:
                    return "Class";
                case EConstantPoolInfoTag::String:
                    return "String";
                case EConstantPoolInfoTag::FieldRef:
                    return "FieldRef";
                case EConstantPoolInfoTag::MethodRef:
                    return "MethodRef";
                case EConstantPoolInfoTag::InterfaceMethodRef:
                    return "InterfaceMethodRef";
                case EConstantPoolInfoTag::NameAndType:
                    return "NameAndType";
                case EConstantPoolInfoTag::MethodHandle:
                    return "MethodHandle";
                case EConstantPoolInfoTag::MethodType:
                    return "MethodType";
                case EConstantPoolInfoTag::InvokeDynamic:
                    return "InvokeDynamic";

                default:
                    return "Unknown Tag";
            }
        }

        template<typename T>
        static const T &CastConstantInfo(const CConstantInfo &ConstantInfo)
        {
            static_assert(std::is_base_of_v<CConstantInfo, T>, "T must be a subclass of CConstantInfo");

            ASSERT_MSG
            (
                ConstantInfo.IsA<T>(),
                "Cannot cast \"%s\" to \"%s\". You can only cast from base CConstantInfo to it's subtype.",
                ConstantInfo.GetTagString(),
                ConstantPoolInfoTagToString(T::StaticTag)
            );

            return static_cast<const T&>(ConstantInfo);
        }

        friend void operator>>(CClassReader &Reader, CConstantInfo &Instance);

    private:
        const EConstantPoolInfoTag ConstantPoolInfoTag;
    };

    /**
     * Phantom constant info is used as the following dummy info for Long and Double constants.
     */
    class CPhantomConstantInfo final : public CConstantInfo
    {
        CPhantomConstantInfo() : CConstantInfo(EConstantPoolInfoTag::Phantom)
        {
        }

    public:
        [[nodiscard]]
        std::string ToLowLevelString() const override
        {
            return "CPhantomConstantInfo";
        }

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override
        {
            ASSERT_MSG(false, "Resolution of a phantom constant info indirectly indicates an error")
            return "";
        }

        void DeserializeFrom(CClassReader &Reader) override
        {
            ASSERT_MSG(false, "Phantom const infos should never be read");
        }

        static CConstantInfo* GetInstance();

        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Phantom;
    };
}
