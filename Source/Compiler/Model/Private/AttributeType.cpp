//
// Created by ASUS on 01/01/2021.
//

#include "AttributeType.h"

#include <unordered_map>

namespace Compiler
{
    constexpr const CAttributeType* G_AttributeNamesArray[]
    {
        &CAttributeTypes::ConstantValue,
        &CAttributeTypes::Code,
        &CAttributeTypes::StackMapTable,
        &CAttributeTypes::Exceptions,
        &CAttributeTypes::InnerClasses,
        &CAttributeTypes::EnclosingMethod,
        &CAttributeTypes::Synthetic,
        &CAttributeTypes::Signature,
        &CAttributeTypes::SourceFile,
        &CAttributeTypes::SourceDebugExtension,

        &CAttributeTypes::LineNumberTable,
        &CAttributeTypes::LocalVariableTable,
        &CAttributeTypes::LocalVariableTypeTable,
        &CAttributeTypes::Deprecated,
        &CAttributeTypes::RuntimeVisibleAnnotations,
        &CAttributeTypes::RuntimeInvisibleAnnotations,
        &CAttributeTypes::RuntimeVisibleParameterAnnotations,
        &CAttributeTypes::RuntimeInvisibleParameterAnnotations,
        &CAttributeTypes::AnnotationDefault,
        &CAttributeTypes::BootstrapMethods,
    };

    typedef std::unordered_map<Util::IStringUtf8, const CAttributeType*> AttributeNamesMap;
    extern const AttributeNamesMap G_AttributeNamesMap;

    constexpr usz CAttributeTypes::GetNumAttributeNames()
    {
        return (usz)(sizeof(G_AttributeNamesArray) / sizeof(void*));
    }

    const CAttributeType* CAttributeTypes::GetAttributeNameByName(const Util::IStringUtf8& String)
    {
        const auto It = G_AttributeNamesMap.find(String);
        return (It != G_AttributeNamesMap.cend()) ? It->second : nullptr;
    }


    AttributeNamesMap GetAttributeNamesMap() noexcept
    {
        AttributeNamesMap Map;
        Map.reserve(CAttributeTypes::GetNumAttributeNames());

        for (const CAttributeType* AttributeName : G_AttributeNamesArray)
        {
            Map.insert({
                std::move(Util::CStringUtf8(AttributeName->GetName())),
                AttributeName
            });
        }

        return std::move(Map);
    }

    const AttributeNamesMap G_AttributeNamesMap = GetAttributeNamesMap();
}