#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Parse
{
    class CClassReader;
    
    class CConstantInvokeDynamicInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetBootstrapMethodAttrIndex() const
        {
             return BootstrapMethodAttrIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameAndTypeIndex() const
        {
             return NameAndTypeIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantInvokeDynamicInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::InvokeDynamic;

    private:
        u2 BootstrapMethodAttrIndex = (u2)0;
        u2 NameAndTypeIndex = (u2)0;
    };
}