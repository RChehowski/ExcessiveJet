#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantUtf8Info : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetLength() const
        {
             return Length;
        }

        [[nodiscard]]
        FORCEINLINE u1* GetBytes() const
        {
             return Bytes;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

        friend void operator>>(Util::CMemoryReader& Reader, CConstantUtf8Info& Instance);

    private:
        u2 Length = (u2)0;
        u1* Bytes = (u1*)0;
    };
}