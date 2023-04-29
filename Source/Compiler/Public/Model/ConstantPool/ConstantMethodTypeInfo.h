#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantMethodTypeInfo : public CConstantInfo
    {
    public:
        CConstantMethodTypeInfo() : CConstantInfo(CConstantMethodTypeInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
             return DescriptorIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::MethodType;

    private:
        u2 DescriptorIndex = (u2)0;
    };
}