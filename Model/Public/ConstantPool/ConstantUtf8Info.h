#pragma once

#include "StringUtf8.h"
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
        FORCEINLINE const Util::CStringUtf8& GetStringUtf8() const
        {
            return StringUtf8;
        }

//        [[nodiscard]]
//        FORCEINLINE u2 GetNumBytes() const
//        {
//             return NumBytes;
//        }
//
//        [[nodiscard]]
//        FORCEINLINE u1* GetBytes() const
//        {
//             return Bytes;
//        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

        friend void operator>>(Util::CMemoryReader& Reader, CConstantUtf8Info& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Utf8;

    private:
//        u2 NumBytes = (u2)0;
//        u1* Bytes = (u1*)0;

        Util::CStringUtf8 StringUtf8;
    };
}