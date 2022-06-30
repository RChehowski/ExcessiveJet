//
// Created by ASUS on 18/01/2021.
//

#include "Model/Attributes/RuntimeVisibleAnnotationsAttributeInfo.h"

namespace Compiler
{
    FORCEINLINE std::shared_ptr<CElementValue> NewElementValue(EElementValueTag ElementValueTag)
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
                return std::make_shared<CConstValueIndexElementValue>();
            case EElementValueTag::EnumConstant:
                return std::make_shared<CEnumConstValueElementValue>();
            case EElementValueTag::Class:
                return std::make_shared<CClassInfoIndexElementValue>();
            case EElementValueTag::AnnotationType:
                return std::make_shared<CAnnotationValueElementValue>();
            case EElementValueTag::Array:
                return std::make_shared<CArrayValueElementValue>();

            default:
                ASSERT_MSG(false, "Unknown EElementValueTag: %d", (int)ElementValueTag);
                return std::shared_ptr<CElementValue>(nullptr);
        }
    }

    FORCEINLINE std::shared_ptr<CElementValue> ReadElementValue(CClassReader& ClassReader)
    {
        EElementValueTag Tag;
        ClassReader >> *((u1*)&Tag);

        std::shared_ptr<CElementValue> ElementValue = NewElementValue(Tag);
        ElementValue->DeserializeFrom(ClassReader);

        return std::move(ElementValue);
    }

    void operator>> (CClassReader& ClassReader,
                     Util::TStandardSerializedArray<std::shared_ptr<CElementValue>> ElementValues)
    {
        Util::TStandardSerializedArray<std::shared_ptr<CElementValue>>::NumItemsType NumItems = 0;
        ClassReader >> NumItems;

        for (int Index = 0; Index < NumItems; ++Index)
        {
            std::shared_ptr<CElementValue> ElementValue = ReadElementValue(ClassReader);

            ElementValues.Items.push_back(std::move(ElementValue));
        }
    }

    void operator>> (CClassReader& ClassReader, CAnnotation& Instance)
    {
        ClassReader >> Instance.TypeIndex;
        ClassReader >> Instance.ElementValuePairs;
    }

    void operator>> (CClassReader& ClassReader, CElementValuePair& Instance)
    {
        ClassReader >> Instance.ElementNameIndex;
        Instance.Value = ReadElementValue(ClassReader);
    }


    void CRuntimeVisibleAnnotationsAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> Annotations;
    }
}
