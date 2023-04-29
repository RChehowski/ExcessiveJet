#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantIntegerInfo : public CConstantInfo
    {
    public:
        CConstantIntegerInfo() : CConstantInfo(CConstantIntegerInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

        [[nodiscard]]
        FORCEINLINE s4 GetInteger() const
        {
            return Value;
        }

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Integer;

    private:
        s4 Value = static_cast<s4>(0);
    };
}