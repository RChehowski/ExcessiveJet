//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Types.h"
#include "ExcessiveAssert.h"
#include "StringUtf8.h"

class ConstantPool;

namespace Compiler
{
    class CAttributeType
    {
        friend class CAttributeTypes;

    private:
        constexpr CAttributeType(const char* const InName, const u2 InAddedInVersion, const u2 InAddedInMinorVersion)
            : Name(InName)
            , AddedInVersion(InAddedInVersion)
            , AddedInMinorVersion(InAddedInMinorVersion)
        {
        }

    public:
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
        const char* Name;

        const u2 AddedInVersion;
        const u2 AddedInMinorVersion;
    };

    #define DEFINE_ATTRIBUTE_NAME(Name, AddedInVersion, AddedInMinorVersion) static constexpr CAttributeType Name =\
        CAttributeType(LITERAL_TO_STRING(Name), AddedInVersion, AddedInMinorVersion)

    class CAttributeTypes
    {
    public:
        DEFINE_ATTRIBUTE_NAME(ConstantValue,                          45, 3);
        DEFINE_ATTRIBUTE_NAME(Code,                                   45, 3);
        DEFINE_ATTRIBUTE_NAME(StackMapTable,                          50, 0);
        DEFINE_ATTRIBUTE_NAME(Exceptions,                             45, 3);
        DEFINE_ATTRIBUTE_NAME(InnerClasses,                           45, 3);
        DEFINE_ATTRIBUTE_NAME(EnclosingMethod,                        49, 0);
        DEFINE_ATTRIBUTE_NAME(Synthetic,                              45, 3);
        DEFINE_ATTRIBUTE_NAME(Signature,                              49, 0);
        DEFINE_ATTRIBUTE_NAME(SourceFile,                             45, 3);
        DEFINE_ATTRIBUTE_NAME(SourceDebugExtension,                   49, 0);
        DEFINE_ATTRIBUTE_NAME(LineNumberTable,                        45, 3);
        DEFINE_ATTRIBUTE_NAME(LocalVariableTable,                     45, 3);
        DEFINE_ATTRIBUTE_NAME(LocalVariableTypeTable,                 49, 0);
        DEFINE_ATTRIBUTE_NAME(Deprecated,                             45, 3);
        DEFINE_ATTRIBUTE_NAME(RuntimeVisibleAnnotations,              49, 0);
        DEFINE_ATTRIBUTE_NAME(RuntimeInvisibleAnnotations,            49, 0);
        DEFINE_ATTRIBUTE_NAME(RuntimeVisibleParameterAnnotations,     49, 0);
        DEFINE_ATTRIBUTE_NAME(RuntimeInvisibleParameterAnnotations,   49, 0);
        DEFINE_ATTRIBUTE_NAME(AnnotationDefault,                      49, 0);
        DEFINE_ATTRIBUTE_NAME(BootstrapMethods,                       51, 0);

        static constexpr usz GetNumAttributeNames();

        static const CAttributeType* GetAttributeNameByName(const Util::IStringUtf8& String);
    };
}
