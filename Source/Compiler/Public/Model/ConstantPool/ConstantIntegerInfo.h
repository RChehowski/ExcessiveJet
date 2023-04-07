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
        FORCEINLINE u4 GetBytes() const
        {
             return Bytes;
        }

        [[nodiscard]]
        FORCEINLINE s4 GetInteger() const
        {
            return *reinterpret_cast<const s4*>(&Bytes);
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantIntegerInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Integer;

    private:
        u4 Bytes = (u4)0;
    };
}