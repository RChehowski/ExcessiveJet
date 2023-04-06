#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantLongInfo : public CConstantInfo
    {
    public:
        CConstantLongInfo() : CConstantInfo(CConstantLongInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToString() const override;

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
        FORCEINLINE s8 GetLong() const
        {
            const u8 AsUnsigned = (static_cast<u8>(HighBytes) << 32) | LowBytes;
            return *reinterpret_cast<const s8*>(&AsUnsigned);
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantLongInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Long;

    private:
        u4 HighBytes = (u4)0;
        u4 LowBytes = (u4)0;
    };
}