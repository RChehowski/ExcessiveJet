#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Parse
{
    class CClassReader;
    
    class CConstantClassInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetNameIndex() const
        {
             return NameIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantClassInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Class;

    private:
        u2 NameIndex = (u2)0;
    };
}