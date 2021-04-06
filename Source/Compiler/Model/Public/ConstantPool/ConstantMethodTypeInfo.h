#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantMethodTypeInfo : public CConstantInfo
    {
    public:
        CConstantMethodTypeInfo() : CConstantInfo(CConstantMethodTypeInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
             return DescriptorIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantMethodTypeInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::MethodType;

    private:
        u2 DescriptorIndex = (u2)0;
    };
}