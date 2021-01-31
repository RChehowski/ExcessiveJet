#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Parse
{
    class CClassReader;
    
    class CConstantMethodTypeInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

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