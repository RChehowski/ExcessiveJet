#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantClassInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetNameIndex() const
        {
             return NameIndex;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

        friend void operator>>(Util::CMemoryReader& Reader, CConstantClassInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Class;

    private:
        u2 NameIndex = (u2)0;
    };
}