//
// Created by ASUS on 18/01/2021.
//

#pragma once

#include "Attributes/AttributeInfo.h"
#include "SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Parse
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

    class CAnnotation
    {
    public:
        CAnnotation() : TypeIndex((u2)-1) {}
        ~CAnnotation() = default;

        friend void operator>> (CClassReader& ClassReader, CAnnotation& Instance);

    private:
        u2 TypeIndex;

        Util::TStandardSerializedArray<std::shared_ptr<class CElementValuePair>> ElementValuePairs;
    };

    class CElementValue
    {
    public:
        CElementValue() = default;

        friend void operator>> (CClassReader& ClassReader, CElementValue& Instance);

    private:
        u1 Tag;
        union CElementValue$Value
        {
            u2 ConstValueIndex;

            struct {
                u2 TypeNameIndex;
                u2 ConstNameIndex;
            } EnumConstValue;

            u2 ClassInfoIndex;

            CAnnotation AnnotationValue;

            TStandardSerializedArray<CElementValue> ArrayValue;


            CElementValue$Value() : AnnotationValue() {};
            ~CElementValue$Value() {}
        };
        CElementValue$Value Value;
    };

    class CElementValuePair
    {
    public:
        friend void operator>> (CClassReader& ClassReader, CElementValuePair& Instance);

    private:
        u2            ElementNameIndex;

        CElementValue Value;
    };

    class CRuntimeVisibleAnnotationsAttributeInfo : public CAttributeInfo
    {
    public:
        ~CRuntimeVisibleAnnotationsAttributeInfo() override;

        void DeserializeFrom(CClassReader &Reader) override;

    private:
        Util::TStandardSerializedArray<CAnnotation> Annotations;
    };
}
