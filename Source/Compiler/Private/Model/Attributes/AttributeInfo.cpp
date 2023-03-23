//
// Created by ASUS on 04/01/2021.
//

#include <unordered_map>

#include "Util/StringUtf8.h"
#include "Model/ClassReader.h"
#include "Model/ConstantPool.h"
#include "Model/ConstantPool/ConstantUtf8Info.h"

#include "Model/Attributes/CodeAttributeInfo.h"
#include "Model/Attributes/DeprecatedAttribute.h"
#include "Model/Attributes/SignatureAttributeInfo.h"
#include "Model/Attributes/SyntheticAttributeInfo.h"
#include "Model/Attributes/ExceptionsAttributeInfo.h"
#include "Model/Attributes/SourceFileAttributeInfo.h"
#include "Model/Attributes/InnerClassesAttributeInfo.h"
#include "Model/Attributes/ConstantValueAttributeInfo.h"
#include "Model/Attributes/LineNumberTableAttributeInfo.h"
#include "Model/Attributes/EnclosingMethodAttributeInfo.h"
#include "Model/Attributes/LocalVariableTableAttributeInfo.h"
#include "Model/Attributes/LocalVariableTypeTableAttributeInfo.h"
#include "Model/Attributes/RuntimeVisibleAnnotationsAttributeInfo.h"


using Util::CLiteralStringUtf8;


#define ADD_ATTRIBUTE_INFO_SPAWNER(ATTRIBUTE_NAME)                  \
{                                                                   \
    CLiteralStringUtf8(LITERAL_TO_STRING(ATTRIBUTE_NAME)),          \
    []()                                                            \
    {                                                               \
        return std::make_shared<C##ATTRIBUTE_NAME##AttributeInfo>();\
    }                                                               \
}

namespace Compiler
{
#pragma region CAttributeInfoHeader
    Util::CMemoryReader& operator>> (Util::CMemoryReader& Reader, CAttributeInfoHeader& Instance)
    {
        Reader >> Instance.AttributeNameIndex;
        Reader >> Instance.AttributeLength;

        return Reader;
    }
#pragma endregion


#pragma region CScopeAttributeInfoDeserializeTracker
    class CScopeAttributeInfoDeserializeTracker
    {
    public:
        CScopeAttributeInfoDeserializeTracker(u4 InExpectedLength, CClassReader &InReader)
            : ExpectedLength((usz)InExpectedLength)
            , Reader(InReader)
            , DeserializeBegin(InReader.Tell())
        {
        }

        ~CScopeAttributeInfoDeserializeTracker()
        {
            const usz ActualLength = Reader.Tell() - DeserializeBegin;

            ASSERT_MSG(ExpectedLength == ActualLength,
               "Unexpected attribute length. Expected bytes: %llu, Actual bytes: %llu", (u8)ExpectedLength, (u8)ActualLength);
        }

    private:
        const usz ExpectedLength;
        const CClassReader& Reader;

        const usz DeserializeBegin;
    };
#pragma endregion


    using CAttributeInfoSpawner = std::function<CSharedAttributeInfo()>;
    using CAttributeInfoSpawners = std::unordered_map<Util::IStringUtf8, CAttributeInfoSpawner>;


    CSharedAttributeInfo NewAttributeInfo(const Util::IStringUtf8& AttributeNameString)
    {
        static const CAttributeInfoSpawners G_AttributeInfoSpawners
        {
            ADD_ATTRIBUTE_INFO_SPAWNER(Code),
            ADD_ATTRIBUTE_INFO_SPAWNER(Synthetic),
            ADD_ATTRIBUTE_INFO_SPAWNER(Signature),
            ADD_ATTRIBUTE_INFO_SPAWNER(Exceptions),
            ADD_ATTRIBUTE_INFO_SPAWNER(Deprecated),
            ADD_ATTRIBUTE_INFO_SPAWNER(SourceFile),
            ADD_ATTRIBUTE_INFO_SPAWNER(InnerClasses),
            ADD_ATTRIBUTE_INFO_SPAWNER(ConstantValue),
            ADD_ATTRIBUTE_INFO_SPAWNER(LineNumberTable),
            ADD_ATTRIBUTE_INFO_SPAWNER(EnclosingMethod),
            ADD_ATTRIBUTE_INFO_SPAWNER(LocalVariableTable),
            ADD_ATTRIBUTE_INFO_SPAWNER(LocalVariableTypeTable),
            ADD_ATTRIBUTE_INFO_SPAWNER(RuntimeVisibleAnnotations),
            // TODO: Support all of them!
        };

        const auto It = G_AttributeInfoSpawners.find(AttributeNameString);

        ASSERT_MSG(It != G_AttributeInfoSpawners.cend(),
           "Attribute name \"%s\" is not present in the map", ((std::string)AttributeNameString).c_str());

        const CAttributeInfoSpawner& AttributeInfoSpawner = It->second;
        return AttributeInfoSpawner();
    }

    CClassReader& operator>>(CClassReader& Reader, Util::TStandardSerializedArray<CSharedAttributeInfo>& Instance)
    {
        Util::TStandardSerializedArray<CSharedAttributeInfo>::NumItemsType NumItems = 0;
        Reader >> NumItems;
        Instance.clear();
        Instance.reserve(NumItems);

        for (usz Index = 0; Index < (usz)NumItems; ++Index)
        {
            CAttributeInfoHeader AttributeInfoHeader;
            Reader >> AttributeInfoHeader;

            std::shared_ptr<CConstantUtf8Info> AttributeName =
                Reader.GetConstantPool()->Get<CConstantUtf8Info>(AttributeInfoHeader.GetAttributeNameIndex());
            ASSERT(AttributeName != nullptr);

            CSharedAttributeInfo AttributeInfo = NewAttributeInfo(AttributeName->GetStringUtf8());
            ASSERT(AttributeInfo != nullptr);

            {
                CScopeAttributeInfoDeserializeTracker ScopeTracker(AttributeInfoHeader.GetAttributeLength(), Reader);
                AttributeInfo->DeserializeFrom(Reader);
            }

            Instance.push_back(std::move(AttributeInfo));
        }

        return Reader;
    }
}