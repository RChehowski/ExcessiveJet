#pragma once

#include "Model/ConstantPool/ConstantInfo.h"
#include "Util/StringUtf8.h"

namespace Compiler
{
    class CClassReader;
    
    class CConstantUtf8Info : public CConstantInfo
    {
    public:
        FORCEINLINE CConstantUtf8Info() : CConstantInfo(CConstantUtf8Info::StaticTag) {}

        FORCEINLINE explicit CConstantUtf8Info(Util::IStringUtf8 InStringUtf8) : CConstantUtf8Info()
        {
            StringUtf8 = std::move(InStringUtf8);
        }

        [[nodiscard]]
        std::string ToLowLevelString() const override;

        [[nodiscard]]
        std::string ToResolvedString(const CConstantPool& ConstantPool) const override;

        [[nodiscard]]
        FORCEINLINE const Util::IStringUtf8& GetStringUtf8() const
        {
             return StringUtf8;
        }

        void DeserializeFrom(CClassReader& Reader) override;

    public:
        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::Utf8;

    private:
        Util::IStringUtf8 StringUtf8 = Util::CLiteralStringUtf8("");
    };
}