#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantDoubleInfo : public CConstantInfo
    {
    public:
        CConstantDoubleInfo() : CConstantInfo(CConstantDoubleInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

        [[nodiscard]]
        FORCEINLINE u4 GetHighBytes() const
        {
             return HighBytes;
        }

        [[nodiscard]]
        FORCEINLINE u4 GetLowBytes() const
        {
             return LowBytes;
        }

        [[nodiscard]]
        FORCEINLINE double GetDouble() const
        {
            const u8 AsUnsigned = (static_cast<u8>(HighBytes) << 32) | LowBytes;
            return *reinterpret_cast<const double*>(&AsUnsigned);
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantDoubleInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Double;

    private:
        u4 HighBytes = (u4)0;
        u4 LowBytes = (u4)0;
    };
}