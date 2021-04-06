#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantInterfaceMethodRefInfo : public CConstantInfo
    {
    public:
        CConstantInterfaceMethodRefInfo() : CConstantInfo(CConstantInterfaceMethodRefInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetClassIndex() const
        {
             return ClassIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameAndTypeIndex() const
        {
             return NameAndTypeIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantInterfaceMethodRefInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::InterfaceMethodRef;

    private:
        u2 ClassIndex = (u2)0;
        u2 NameAndTypeIndex = (u2)0;
    };
}