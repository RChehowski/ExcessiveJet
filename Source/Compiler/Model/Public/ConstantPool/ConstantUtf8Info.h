#pragma once

#include "ConstantPool/ConstantInfo.h"
#include "StringUtf8.h"

namespace Parse
{
    class CClassReader;
    
    class CConstantUtf8Info : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE const Util::CStringUtf8& GetStringUtf8() const
        {
             return StringUtf8;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantUtf8Info& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Utf8;

    private:
        Util::CStringUtf8 StringUtf8;
    };
}