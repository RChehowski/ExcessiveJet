#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantFloatInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u4 GetBytes() const
        {
             return Bytes;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override
        {
            Reader >> *this;
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantFloatInfo& Instance);

    private:
        u4 Bytes = (u4)0;
    };
}