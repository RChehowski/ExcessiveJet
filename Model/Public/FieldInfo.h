//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CFieldInfo
    {
    public:
        [[nodiscard]]
        FORCEINLINE u2 GetAccessFlags() const
        {
            return AccessFlags;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameIndex() const
        {
            return NameIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
            return DescriptorIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetAttributesCount() const
        {
            return AttributesCount;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader);

        friend void operator>>(Util::CMemoryReader& Reader, CFieldInfo& Instance);

    private:
        u2 AccessFlags = (u2)0;
        u2 NameIndex = (u2)0;
        u2 DescriptorIndex = (u2)0;
        u2 AttributesCount = (u2)0;
    };
}
