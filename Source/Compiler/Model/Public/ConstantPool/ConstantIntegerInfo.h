#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Parse
{
    class CClassReader;
    
    class CConstantIntegerInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u4 GetBytes() const
        {
             return Bytes;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantIntegerInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Integer;

    private:
        u4 Bytes = (u4)0;
    };
}