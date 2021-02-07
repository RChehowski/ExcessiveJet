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

    class CElementValuePair;

    class CAnnotation
    {
    public:
        CAnnotation() : TypeIndex((u2)-1) {}
        ~CAnnotation() = default;

        friend void operator>> (CClassReader& ClassReader, CAnnotation& Instance);

    private:
        u2 TypeIndex;
        Util::TStandardSerializedArray<std::shared_ptr<CElementValuePair>> ElementValuePairs;
    };


    class CElementValuePair
    {
    public:
        CElementValuePair() = default;
        virtual ~CElementValuePair() = default;

        virtual void DeserializeFrom(CClassReader &Reader)
        {
            // Overriden in subclasses
            Reader >> ElementNameIndex;
        }

        friend void operator>> (CClassReader& ClassReader, CElementValuePair& Instance)
        {
            Instance.DeserializeFrom(ClassReader);
        }

        static std::shared_ptr<CElementValuePair> NewElementValue(EElementValueTag ElementValueTag);

    private:
        u2 ElementNameIndex = (u2)0;
    };


    class CConstValueIndexElementValuePair : public CElementValuePair
    {
    public:
        using CElementValuePair::CElementValuePair;

        void DeserializeFrom(CClassReader &Reader) override
        {
            CElementValuePair::DeserializeFrom(Reader);
            Reader >> ConstValueIndex;
        }

    private:
        u2 ConstValueIndex  = (u2)0;
    };

    class CEnumConstValueElementValuePair : public CElementValuePair
    {
    public:
        using CElementValuePair::CElementValuePair;

        void DeserializeFrom(CClassReader &Reader) override
        {
            CElementValuePair::DeserializeFrom(Reader);

            Reader >> TypeNameIndex;
            Reader >> ConstNameIndex;
        }

    private:
        u2 TypeNameIndex    = (u2)0;
        u2 ConstNameIndex   = (u2)0;
    };

    class CClassInfoIndexElementValuePair : public CElementValuePair
    {
    public:
        using CElementValuePair::CElementValuePair;

        void DeserializeFrom(CClassReader &Reader) override
        {
            CElementValuePair::DeserializeFrom(Reader);

            Reader >> ClassInfoIndex;
        }

    private:
        u2 ClassInfoIndex   = (u2)0;
    };

    class CAnnotationValueElementValuePair : public CElementValuePair
    {
    public:
        using CElementValuePair::CElementValuePair;

        void DeserializeFrom(CClassReader &Reader) override
        {
            CElementValuePair::DeserializeFrom(Reader);
            Reader >> AnnotationValue;
        }

    private:
        CAnnotation AnnotationValue = {};
    };

    class CArrayValueElementValuePair : public CElementValuePair
    {
    public:
        using CElementValuePair::CElementValuePair;

        void DeserializeFrom(CClassReader &Reader) override
        {
            CElementValuePair::DeserializeFrom(Reader);
            // TODO: Implement it
//            Reader >> ArrayValue;
        }

    private:
        TStandardSerializedArray<std::shared_ptr<CElementValuePair>> ArrayValue;
    };

    class CRuntimeVisibleAnnotationsAttributeInfo : public CAttributeInfo
    {
    public:
        ~CRuntimeVisibleAnnotationsAttributeInfo() override;

        void DeserializeFrom(CClassReader &Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(RuntimeVisibleAnnotations);

    private:
        Util::TStandardSerializedArray<CAnnotation> Annotations;
    };
}
