//
// Created by ASUS on 01/01/2021.
//

#ifndef CPP20_ATTRIBUTES_H
#define CPP20_ATTRIBUTES_H

#include "Types.h"
#include "Assert.h"
#include "Platform/Memory.h"
#include "StringUtf8.h"

#include <optional>
#include <unordered_map>

namespace Parser
{
    class CAttributeName
    {
        friend class CAttributeNames;

    private:
        constexpr CAttributeName(const u1 InId, const char* const InName, const u2 InAddedInVersion, const u2 InAddedInMinorVersion)
            : Id(InId)
            , Name(InName)
            , AddedInVersion(InAddedInVersion)
            , AddedInMinorVersion(InAddedInMinorVersion)
        {
        }

    public:
        [[nodiscard]]
        FORCEINLINE u1 GetId() const
        {
            return Id;
        }

        [[nodiscard]]
        FORCEINLINE const char* GetName() const
        {
            return Name;
        }

    private:
        u1 Id;
        const char* Name;

        const u2 AddedInVersion;
        const u2 AddedInMinorVersion;
    };

    #define DEFINE_ATTRIBUTE_NAME(Id, Name, AddedInVersion, AddedInMinorVersion) static constexpr CAttributeName Name =\
        CAttributeName((u1)Id, LITERAL_TO_STRING(Name), AddedInVersion, AddedInMinorVersion)

    class CAttributeNames
    {
    public:
        DEFINE_ATTRIBUTE_NAME(0,    ConstantValue, 45, 3);
        DEFINE_ATTRIBUTE_NAME(1,    Code, 45, 3);
        DEFINE_ATTRIBUTE_NAME(2,    StackMapTable, 50, 0);
        DEFINE_ATTRIBUTE_NAME(3,    Exceptions, 45, 3);
        DEFINE_ATTRIBUTE_NAME(4,    InnerClasses, 45, 3);
        DEFINE_ATTRIBUTE_NAME(5,    EnclosingMethod, 49, 0);
        DEFINE_ATTRIBUTE_NAME(6,    Synthetic, 45, 3);
        DEFINE_ATTRIBUTE_NAME(7,    Signature, 49, 0);
        DEFINE_ATTRIBUTE_NAME(8,    SourceFile, 45, 3);
        DEFINE_ATTRIBUTE_NAME(9,    SourceDebugExtension, 49, 0);
        DEFINE_ATTRIBUTE_NAME(10,   LineNumberTable, 45, 3);
        DEFINE_ATTRIBUTE_NAME(11,   LocalVariableTable, 45, 3);
        DEFINE_ATTRIBUTE_NAME(12,   LocalVariableTypeTable, 49, 0);
        DEFINE_ATTRIBUTE_NAME(13,   Deprecated, 45, 3);
        DEFINE_ATTRIBUTE_NAME(14,   RuntimeVisibleAnnotations, 49, 0);
        DEFINE_ATTRIBUTE_NAME(15,   RuntimeInvisibleAnnotations, 49, 0);
        DEFINE_ATTRIBUTE_NAME(16,   RuntimeVisibleParameterAnnotations, 49, 0);
        DEFINE_ATTRIBUTE_NAME(17,   RuntimeInvisibleParameterAnnotations, 49, 0);
        DEFINE_ATTRIBUTE_NAME(18,   AnnotationDefault, 49, 0);
        DEFINE_ATTRIBUTE_NAME(19,   BootstrapMethods, 51, 0);

        static constexpr size_t GetNumAttributeNames();

        const CAttributeName* GetAttributeNameByName(const Util::StringUtf8& String);
    };

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

}








class Attributes
{

};


#endif //CPP20_ATTRIBUTES_H
