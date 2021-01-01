//
// Created by ASUS on 01/01/2021.
//

#include "Attributes.h"

namespace Parser
{
    constexpr size_t CAttributeNames::GetNumAttributeNames()
    {
        return (size_t)(sizeof(G_AttributeNamesArray) / sizeof(void*));
    }

    const CAttributeName* CAttributeNames::GetAttributeNameByName(const Util::StringUtf8& String)
    {
        auto It = G_AttributeNamesMap.find(String);
        return (It != G_AttributeNamesMap.cend()) ? It->second : nullptr;
    }


    AttributeNamesMap GetAttributeNamesMap() noexcept
    {
        AttributeNamesMap Map;
        Map.reserve(CAttributeNames::GetNumAttributeNames());

        for (const CAttributeName* AttributeName : G_AttributeNamesArray)
        {
            Map.insert({ std::move(Util::StringUtf8(AttributeName->GetName())), AttributeName });
        }

        return std::move(Map);
    }

    const AttributeNamesMap G_AttributeNamesMap = GetAttributeNamesMap();
}