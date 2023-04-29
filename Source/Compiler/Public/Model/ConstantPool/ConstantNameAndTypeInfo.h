#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantNameAndTypeInfo : public CConstantInfo
    {
    public:
        CConstantNameAndTypeInfo() : CConstantInfo(CConstantNameAndTypeInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

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

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::NameAndType;

    private:
        u2 NameIndex = (u2)0;
        u2 DescriptorIndex = (u2)0;
    };
}