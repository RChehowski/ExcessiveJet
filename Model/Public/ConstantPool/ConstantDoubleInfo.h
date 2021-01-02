#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantDoubleInfo : public CConstantInfo
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

        void DeserializeFrom(Util::CMemoryReader& Reader) override
        {
            Reader >> *this;
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantDoubleInfo& Instance);

    private:
        u4 HighBytes = (u4)0;
        u4 LowBytes = (u4)0;
    };
}