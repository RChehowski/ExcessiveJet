//
// Created by ASUS on 18/01/2021.
//

#include "Attributes/RuntimeVisibleAnnotationsAttributeInfo.h"

namespace Parse
{
    std::shared_ptr<CElementValuePair> CElementValuePair::NewElementValue(EElementValueTag ElementValueTag)
    {
        switch (ElementValueTag)
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
                return std::make_shared<CConstValueIndexElementValuePair>();
            case EElementValueTag::EnumConstant:
                return std::make_shared<CEnumConstValueElementValuePair>();
            case EElementValueTag::Class:
                return std::make_shared<CClassInfoIndexElementValuePair>();
            case EElementValueTag::AnnotationType:
                return std::make_shared<CAnnotationValueElementValuePair>();
            case EElementValueTag::Array:
                return std::make_shared<CArrayValueElementValuePair>();

            default:
                ASSERT_MSG(false, "Unknown EElementValueTag: %d", (int)ElementValueTag);
                return std::shared_ptr<CElementValuePair>(nullptr);
        }
    }

    void operator>> (CClassReader& ClassReader, CAnnotation& Instance)
    {
        ClassReader >> Instance.TypeIndex;

        // TODO: Define how to read and create ElementValuePairs
        ClassReader >> Instance.ElementValuePairs;
    }


    CRuntimeVisibleAnnotationsAttributeInfo::~CRuntimeVisibleAnnotationsAttributeInfo() = default;

    void CRuntimeVisibleAnnotationsAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> Annotations;
    }
}
