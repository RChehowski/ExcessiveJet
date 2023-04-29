#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantStringInfo : public CConstantInfo
    {
    public:
        CConstantStringInfo() : CConstantInfo(CConstantStringInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

        [[nodiscard]]
        FORCEINLINE u2 GetStringIndex() const
        {
             return StringIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::String;

    private:
        u2 StringIndex = (u2)0;
    };
}