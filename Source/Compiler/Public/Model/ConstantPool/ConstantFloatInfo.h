#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantFloatInfo : public CConstantInfo
    {
    public:
        CConstantFloatInfo() : CConstantInfo(CConstantFloatInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

        [[nodiscard]]
        FORCEINLINE float GetFloat() const
        {
            return Value;
        }

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Float;

    private:
        float Value = 0.0f;
    };
}