//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Types.h"
#include "Assert.h"
#include "Platform/Memory.h"
#include "StringUtf8.h"

class CAttributeInfo;
class ClassFileBlob;
class ConstantPool;

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
        FORCEINLINE constexpr u1 GetId() const
        {
            return Id;
        }

        [[nodiscard]]
        FORCEINLINE constexpr const char* GetName() const
        {
            return Name;
        }

        [[nodiscard]]
        FORCEINLINE constexpr u2 GetAddedInVersion() const
        {
            return AddedInVersion;
        }

        [[nodiscard]]
        FORCEINLINE constexpr u2 GetAddedInMinorVersion() const
        {
            return AddedInMinorVersion;
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
        DEFINE_ATTRIBUTE_NAME(0,    ConstantValue,                          45, 3);
        DEFINE_ATTRIBUTE_NAME(1,    Code,                                   45, 3);
        DEFINE_ATTRIBUTE_NAME(2,    StackMapTable,                          50, 0);
        DEFINE_ATTRIBUTE_NAME(3,    Exceptions,                             45, 3);
        DEFINE_ATTRIBUTE_NAME(4,    InnerClasses,                           45, 3);
        DEFINE_ATTRIBUTE_NAME(5,    EnclosingMethod,                        49, 0);
        DEFINE_ATTRIBUTE_NAME(6,    Synthetic,                              45, 3);
        DEFINE_ATTRIBUTE_NAME(7,    Signature,                              49, 0);
        DEFINE_ATTRIBUTE_NAME(8,    SourceFile,                             45, 3);
        DEFINE_ATTRIBUTE_NAME(9,    SourceDebugExtension,                   49, 0);
        DEFINE_ATTRIBUTE_NAME(10,   LineNumberTable,                        45, 3);
        DEFINE_ATTRIBUTE_NAME(11,   LocalVariableTable,                     45, 3);
        DEFINE_ATTRIBUTE_NAME(12,   LocalVariableTypeTable,                 49, 0);
        DEFINE_ATTRIBUTE_NAME(13,   Deprecated,                             45, 3);
        DEFINE_ATTRIBUTE_NAME(14,   RuntimeVisibleAnnotations,              49, 0);
        DEFINE_ATTRIBUTE_NAME(15,   RuntimeInvisibleAnnotations,            49, 0);
        DEFINE_ATTRIBUTE_NAME(16,   RuntimeVisibleParameterAnnotations,     49, 0);
        DEFINE_ATTRIBUTE_NAME(17,   RuntimeInvisibleParameterAnnotations,   49, 0);
        DEFINE_ATTRIBUTE_NAME(18,   AnnotationDefault,                      49, 0);
        DEFINE_ATTRIBUTE_NAME(19,   BootstrapMethods,                       51, 0);

        static constexpr usz GetNumAttributeNames();

        static const CAttributeName* GetAttributeNameByName(const Util::StringUtf8& String);
    };

    class CAttributes
    {
    public:
        static CAttributeInfo* ReadAttributeInfo(ClassFileBlob& Blob, const ConstantPool& ConstantPool);
    };
}
