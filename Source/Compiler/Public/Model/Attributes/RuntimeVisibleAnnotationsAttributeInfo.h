//
// Created by ASUS on 18/01/2021.
//

#pragma once

#include "Model/Attributes/AttributeInfo.h"
#include "Util/SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Compiler
{
    enum class EElementValueTag : u1
    {
        // Primitive types
        Byte            = (u1)'B',
        Char            = (u1)'C',
        Double          = (u1)'D',
        Float           = (u1)'F',
        Int             = (u1)'I',
        Long            = (u1)'J',
        Short           = (u1)'S',
        Bool            = (u1)'Z',

        // Reference types
        String          = (u1)'s',
        EnumConstant    = (u1)'e',
        Class           = (u1)'c',
        AnnotationType  = (u1)'@',
        Array           = (u1)'[',
    };

    class CElementValue;

    void operator>> (CClassReader& ClassReader,
                     Util::TStandardSerializedArray<std::shared_ptr<CElementValue>> ElementValues);

    class CElementValuePair
    {
    public:
        CElementValuePair() = default;
        ~CElementValuePair() = default;

        friend void operator>> (CClassReader& ClassReader, CElementValuePair& Instance);

    private:
        u2 ElementNameIndex = (u2)0;
        std::shared_ptr<CElementValue> Value;
    };

    class CAnnotation
    {
    public:
        CAnnotation() = default;
        ~CAnnotation() = default;

        friend void operator>> (CClassReader& ClassReader, CAnnotation& Instance);

    private:
        u2 TypeIndex = (u2)0;
        Util::TStandardSerializedArray<CElementValuePair> ElementValuePairs;
    };


    class CElementValue
    {
    public:
        explicit CElementValue() = default;
        virtual ~CElementValue() = default;

        virtual void DeserializeFrom(CClassReader &Reader) = 0;

        friend void operator>> (CClassReader& ClassReader, CElementValue& Instance)
        {
            Instance.DeserializeFrom(ClassReader);
        }
    };

    class CConstValueIndexElementValue : public CElementValue
    {
    public:
        using CElementValue::CElementValue;

        void DeserializeFrom(CClassReader &Reader) override
        {
            Reader >> ConstValueIndex;
        }

    private:
        u2 ConstValueIndex  = (u2)0;
    };

    class CEnumConstValueElementValue : public CElementValue
    {
    public:
        using CElementValue::CElementValue;

        void DeserializeFrom(CClassReader &Reader) override
        {
            Reader >> TypeNameIndex;
            Reader >> ConstNameIndex;
        }

    private:
        u2 TypeNameIndex    = (u2)0;
        u2 ConstNameIndex   = (u2)0;
    };

    class CClassInfoIndexElementValue : public CElementValue
    {
    public:
        using CElementValue::CElementValue;

        void DeserializeFrom(CClassReader &Reader) override
        {
            Reader >> ClassInfoIndex;
        }

    private:
        u2 ClassInfoIndex   = (u2)0;
    };

    class CAnnotationValueElementValue : public CElementValue
    {
    public:
        using CElementValue::CElementValue;

        void DeserializeFrom(CClassReader &Reader) override
        {
            Reader >> AnnotationValue;
        }

    private:
        CAnnotation AnnotationValue = {};
    };

    class CArrayValueElementValue : public CElementValue
    {
    public:
        using CElementValue::CElementValue;

        void DeserializeFrom(CClassReader &Reader) override
        {
            Reader >> ArrayValue;
        }

    private:
        TStandardSerializedArray<std::shared_ptr<CElementValue>> ArrayValue;
    };



    class CRuntimeVisibleAnnotationsAttributeInfo : public CAttributeInfo
    {
    public:
        ~CRuntimeVisibleAnnotationsAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(RuntimeVisibleAnnotations);

    private:
        Util::TStandardSerializedArray<CAnnotation> Annotations;
    };
}
