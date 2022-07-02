#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantInvokeDynamicInfo : public CConstantInfo
    {
    public:
        CConstantInvokeDynamicInfo() : CConstantInfo(CConstantInvokeDynamicInfo::StaticTag) {}

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