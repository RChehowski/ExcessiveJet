//
// Created by ASUS on 01/01/2021.
//

#include "Attributes.h"

#include <unordered_map>
#include <Attributes/LocalVariableTableAttributeInfo.h>

namespace Parser
{
    constexpr const CAttributeName* G_AttributeNamesArray[] = {
        &CAttributeNames::ConstantValue,
        &CAttributeNames::Code,
        &CAttributeNames::StackMapTable,
        &CAttributeNames::Exceptions,
        &CAttributeNames::InnerClasses,
        &CAttributeNames::EnclosingMethod,
        &CAttributeNames::Synthetic,
        &CAttributeNames::Signature,
        &CAttributeNames::SourceFile,
        &CAttributeNames::SourceDebugExtension,
        &CAttributeNames::LineNumberTable,
        &CAttributeNames::LocalVariableTable,
        &CAttributeNames::LocalVariableTypeTable,
        &CAttributeNames::Deprecated,
        &CAttributeNames::RuntimeVisibleAnnotations,
        &CAttributeNames::RuntimeInvisibleAnnotations,
        &CAttributeNames::RuntimeVisibleParameterAnnotations,
        &CAttributeNames::RuntimeInvisibleParameterAnnotations,
        &CAttributeNames::AnnotationDefault,
        &CAttributeNames::BootstrapMethods,
    };

    typedef std::unordered_map<Util::StringUtf8, const CAttributeName*> AttributeNamesMap;
    extern const AttributeNamesMap G_AttributeNamesMap;

    constexpr usz CAttributeNames::GetNumAttributeNames()
    {
        return (usz)(sizeof(G_AttributeNamesArray) / sizeof(void*));
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
            Map.insert({
                std::move(Util::StringUtf8(AttributeName->GetName())),
                AttributeName
            });
        }

        return std::move(Map);
    }

    const AttributeNamesMap G_AttributeNamesMap = GetAttributeNamesMap();



    typedef CAttributeInfo* (*FAttributeInfoNewInstanceFunction)(u2, u4);


//    CAttributeInfo* CAttributes::ReadAttributeInfo(ClassFileBlob& Blob, const ConstantPool& ConstantPool)
//    {
//        u2 AttributeNameIndex = (u2)0;
//        Blob >> AttributeNameIndex;
//
//        u4 AttributeLength = (u4)0;
//        Blob >> AttributeLength;
//
//        ConstantPool.Get<const CONSTANT_Utf8_info>(AttributeNameIndex);
//
//        FAttributeInfoNewInstanceFunction AttributeInfoNewInstanceFunction =
//                &CLocalVariableTableAttributeInfo::NewInstance;
//
//        return nullptr;
//    }
}