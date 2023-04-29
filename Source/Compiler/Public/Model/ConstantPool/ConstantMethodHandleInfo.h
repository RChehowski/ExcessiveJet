#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantMethodHandleInfo : public CConstantInfo
    {
    public:
        CConstantMethodHandleInfo() : CConstantInfo(CConstantMethodHandleInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override
        {
            ASSERT_MSG(false, "Not implemented");
            return "";
        }

        [[nodiscard]]
        FORCEINLINE u1 GetReferenceKind() const
        {
             return ReferenceKind;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetReferenceIndex() const
        {
             return ReferenceIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::MethodHandle;

    private:
        u1 ReferenceKind = (u1)0;
        u2 ReferenceIndex = (u2)0;
    };
}