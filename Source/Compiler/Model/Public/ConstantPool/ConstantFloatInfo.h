#pragma once

#include "ConstantPool/ConstantInfo.h"
#include "ClassReader.h"

class CClassReader;

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

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantFloatInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Float;

    private:
        u4 Bytes = (u4)0;
    };
}