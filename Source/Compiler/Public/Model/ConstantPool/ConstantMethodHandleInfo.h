#pragma once

#include "Model/ConstantPool/ConstantInfo.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantMethodHandleInfo : public CConstantInfo
    {
    public:
        CConstantMethodHandleInfo() : CConstantInfo(CConstantMethodHandleInfo::StaticTag) {}

        [[nodiscard]]
        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u1 GetReferenceKind() const
        {
             return ReferenceKind;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetReferenceIndex() const
        {
             return ReferenceIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        friend void operator>>(CClassReader& Reader, CConstantMethodHandleInfo& Instance);

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::MethodHandle;

    private:
        u1 ReferenceKind = (u1)0;
        u2 ReferenceIndex = (u2)0;
    };
}