//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "ClassVersion.h"
#include "SerializedArray.h"

#include <vector>

namespace Compiler
{
    class CClassReader;
    class CConstantPool;

    class CAttributeInfoType
    {
    public:
        constexpr CAttributeInfoType(const char* InName, const CClassVersion& InClassVersion)
            : Name(InName)
            , ClassVersion(InClassVersion)
        {
        }

        FORCEINLINE bool operator== (const CAttributeInfoType& AttributeInfoType) const
        {
            // Names are constant so pointer comparison is enough
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

    #define IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(TYPE) \
        static constexpr CAttributeInfoType StaticType = CAttributeInfoTypes::TYPE; \
                                                                                    \
        [[nodiscard]]                                                               \
        CAttributeInfoType GetAttributeInfoType() const override                    \
        {                                                                           \
            return StaticType;                                                      \
        }


    class CAttributeInfoTypes
    {
    public:
        ADD_ATTRIBUTE_INFO_TYPE(ConstantValue,                          45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(Code,                                   45, 3);
      //ADD_ATTRIBUTE_INFO_TYPE(StackMapTable,                          50, 0);
        ADD_ATTRIBUTE_INFO_TYPE(Exceptions,                             45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(InnerClasses,                           45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(EnclosingMethod,                        49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(Synthetic,                              45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(Signature,                              49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(SourceFile,                             45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(SourceDebugExtension,                   49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(LineNumberTable,                        45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(LocalVariableTable,                     45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(LocalVariableTypeTable,                 49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(Deprecated,                             45, 3);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeVisibleAnnotations,              49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeInvisibleAnnotations,            49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeVisibleParameterAnnotations,     49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(RuntimeInvisibleParameterAnnotations,   49, 0);
        ADD_ATTRIBUTE_INFO_TYPE(AnnotationDefault,                      49, 0);
      //ADD_ATTRIBUTE_INFO_TYPE(BootstrapMethods,                       51, 0);
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

    class CAttributeInfo;
    using CSharedAttributeInfo = std::shared_ptr<CAttributeInfo>;

    class CAttributeInfo
    {
    public:
        virtual ~CAttributeInfo() = default;

        virtual void DeserializeFrom(CClassReader& Reader) = 0;

        [[nodiscard]]
        virtual CAttributeInfoType GetAttributeInfoType() const = 0;

        template <class T>
        static std::shared_ptr<T> GetAttributeOfType(const Util::TStandardSerializedArray<CSharedAttributeInfo>& InAttributes)
        {
            static_assert(std::is_base_of_v<CAttributeInfo, T>, "T must be a subclass of CAttributeInfo");

            for (const CSharedAttributeInfo& SharedAttributeInfo : InAttributes)
            {
                const CAttributeInfoType AttributeInfoType = SharedAttributeInfo->GetAttributeInfoType();

                if (T::StaticType == AttributeInfoType)
                {
                    return std::static_pointer_cast<T>(SharedAttributeInfo);
                }
            }

            return std::shared_ptr<T>(nullptr);
        }

        template <class T>
        static std::vector<std::shared_ptr<T>> GetAttributesOfType(const Util::TStandardSerializedArray<CSharedAttributeInfo>& InAttributes)
        {
            static_assert(std::is_base_of_v<CAttributeInfo, T>, "T must be a subclass of CAttributeInfo");

            std::vector<std::shared_ptr<T>> Result;

            for (const CSharedAttributeInfo& SharedAttributeInfo : InAttributes)
            {
                const CAttributeInfoType AttributeInfoType = SharedAttributeInfo->GetAttributeInfoType();

                if (T::StaticType == AttributeInfoType)
                {
                    Result.push_back(SharedAttributeInfo);
                }
            }

            return Result;
        }
    };

    CClassReader& operator>>(CClassReader& Reader, Util::TStandardSerializedArray<CSharedAttributeInfo>& Instance);
}