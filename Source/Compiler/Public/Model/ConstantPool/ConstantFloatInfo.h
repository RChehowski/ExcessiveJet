#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantFloatInfo : public CConstantInfo
    {
    public:
        CConstantFloatInfo() : CConstantInfo(CConstantFloatInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u4 GetBytes() const
        {
             return Bytes;
        }

        [[nodiscard]]
        FORCEINLINE float GetFloat() const
        {
            return *reinterpret_cast<const float*>(&Bytes);
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantFloatInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Float;

    private:
        u4 Bytes = (u4)0;
    };
}