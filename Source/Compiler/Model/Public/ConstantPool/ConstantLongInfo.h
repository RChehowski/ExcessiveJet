#pragma once

#include "ConstantPool/ConstantInfo.h"
#include "ClassReader.h"

class CClassReader;

namespace Parse
{
    class CConstantLongInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

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

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantLongInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Long;

    private:
        u4 HighBytes = (u4)0;
        u4 LowBytes = (u4)0;
    };
}