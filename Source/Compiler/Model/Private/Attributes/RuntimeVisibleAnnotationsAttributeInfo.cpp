//
// Created by ASUS on 18/01/2021.
//

#include "Attributes/RuntimeVisibleAnnotationsAttributeInfo.h"

namespace Parse
{
    void operator>> (CClassReader& ClassReader, CElementValue& Instance)
    {
        ClassReader >> Instance.Tag;

        switch ((EElementValueTag)Instance.Tag)
        {
            case EElementValueTag::Byte:
            case EElementValueTag::Char:
            case EElementValueTag::Double:
            case EElementValueTag::Float:
            case EElementValueTag::Int:
            case EElementValueTag::Long:
            case EElementValueTag::Short:
            case EElementValueTag::Bool:
            case EElementValueTag::String:
                ClassReader >> Instance.Value.ConstValueIndex;
                break;
            case EElementValueTag::EnumConstant:
                ClassReader >> Instance.Value.EnumConstValue.TypeNameIndex;
                ClassReader >> Instance.Value.EnumConstValue.ConstNameIndex;
                break;
            case EElementValueTag::Class:
                ClassReader >> Instance.Value.ClassInfoIndex;
                break;
            case EElementValueTag::AnnotationType:
                ClassReader >> Instance.Value.AnnotationValue;
                break;
            case EElementValueTag::Array:
                ClassReader >> Instance.Value.ArrayValue;
                break;
        }
    }

    void operator>> (CClassReader& ClassReader, CElementValuePair& Instance)
    {
        ClassReader >> Instance.ElementNameIndex;
        ClassReader >> Instance.Value;
    }


    void operator>> (CClassReader& ClassReader, CAnnotation& Instance)
    {
        ClassReader >> Instance.TypeIndex;
        ClassReader >> Instance.ElementValuePairs;
    }


    CRuntimeVisibleAnnotationsAttributeInfo::~CRuntimeVisibleAnnotationsAttributeInfo() = default;

    void CRuntimeVisibleAnnotationsAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> Annotations;
    }
}
