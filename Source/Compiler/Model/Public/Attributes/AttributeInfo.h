//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Types.h"
#include "ClassVersion.h"
#include "SerializedArray.h"

namespace Parse
{
    class CClassReader;
    class CConstantPool;

    class CAttributeInfoType
    {
    public:
        constexpr CAttributeInfoType(const char* InName, const CClassVersion InClassVersion)
            : Name(InName)
            , ClassVersion(InClassVersion)
        {
        }

        FORCEINLINE bool operator== (const CAttributeInfoType& AttributeInfoType) const
        {
            return Name == AttributeInfoType.Name;
        }

    private:
        const char* Name;
        const CClassVersion ClassVersion;
    };

    #define ADD_ATTRIBUTE_INFO_TYPE(NAME, MAJ_VERSION, MIN_VERSION) \
        static constexpr CAttributeInfoType NAME {                  \
            LITERAL_TO_STRING(NAME),                                \
            {                                                       \
                MAJ_VERSION,                                        \
                MIN_VERSION                                         \
            }                                                       \
        }                                                           \

    class CAttributeInfoTypes
    {
    public:
        ADD_ATTRIBUTE_INFO_TYPE(ConstantValue,                          45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(Code,                                   45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(StackMapTable,                          50, 0);
        ADD_ATTRIBUTE_INFO_TYPE(Exceptions,                             45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(InnerClasses,                           45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(EnclosingMethod,                        49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(Synthetic,                              45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(Signature,                              49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(SourceFile,                             45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(SourceDebugExtension,                   49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(LineNumberTable,                        45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(LocalVariableTabl,                      45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(LocalVariableTypeTable,                 49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(Deprecated,                             45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeVisibleAnnotations,              49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeInvisibleAnnotations,            49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeVisibleParameterAnnotations,     49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeInvisibleParameterAnnotations,   49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(AnnotationDefault,                      49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(BootstrapMethods,                       51, 0);
    };

    class CAttributeInfoHeader
    {
    public:
        CAttributeInfoHeader() = default;
        ~CAttributeInfoHeader() = default;

        friend Util::CMemoryReader& operator>> (Util::CMemoryReader& Reader, CAttributeInfoHeader& Instance);

        [[nodiscard]]
        FORCEINLINE u2 GetAttributeNameIndex() const
        {
            return AttributeNameIndex;
        }

        [[nodiscard]]
        FORCEINLINE u4 GetAttributeLength() const
        {
            return AttributeLength;
        }

    private:
        u2 AttributeNameIndex   = (u2)0;
        u4 AttributeLength      = (u4)0;
    };

    class CAttributeInfo
    {
    public:
        virtual ~CAttributeInfo() = default;

        virtual void DeserializeFrom(CClassReader& Reader) = 0;
    };

    using CSharedAttributeInfo = std::shared_ptr<CAttributeInfo>;

    CClassReader& operator>>(CClassReader& Reader, Util::TStandardSerializedArray<CSharedAttributeInfo>& Instance);
}