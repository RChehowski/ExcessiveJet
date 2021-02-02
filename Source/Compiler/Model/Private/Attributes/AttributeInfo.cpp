//
// Created by ASUS on 04/01/2021.
//

#include <ConstantPool/ConstantUtf8Info.h>
#include "Attributes/CodeAttributeInfo.h"
#include "ClassReader.h"
#include "ConstantPool.h"

#include "StringUtf8.h"

#include "Attributes/DeprecatedAttribute.h"
#include "Attributes/CodeAttributeInfo.h"
#include "Attributes/LineNumberTableAttributeInfo.h"
#include "Attributes/LocalVariableTableAttributeInfo.h"
#include "Attributes/ExceptionsAttributeInfo.h"
#include "Attributes/LocalVariableTypeTableAttributeInfo.h"


using Util::CLiteralStringUtf8;


#define DEFINE_ATTRIBUTE_INFO_SPAWNER(AttributeName) {\
    CLiteralStringUtf8(LITERAL_TO_STRING(AttributeName)), \
    []() { return std::make_shared<C##AttributeName##AttributeInfo>(); }                                          \
}

namespace Parse
{
    using CSerializedArrayOfAttributes = Util::TStandardSerializedArray<CSharedAttributeInfo>;

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


    CSharedAttributeInfo NewAttributeInfo(const Util::CStringUtf8& AttributeNameString)
    {
        static const CAttributeInfoSpawners G_AttributeInfoSpawners {
            DEFINE_ATTRIBUTE_INFO_SPAWNER(Deprecated),
            DEFINE_ATTRIBUTE_INFO_SPAWNER(Code),
            DEFINE_ATTRIBUTE_INFO_SPAWNER(LineNumberTable),
            DEFINE_ATTRIBUTE_INFO_SPAWNER(LocalVariableTable),
            DEFINE_ATTRIBUTE_INFO_SPAWNER(Exceptions),
            DEFINE_ATTRIBUTE_INFO_SPAWNER(LocalVariableTypeTable),
            // TODO: Support all of them!
        };

        CAttributeInfoSpawners::const_iterator It = G_AttributeInfoSpawners.find(AttributeNameString);

        ASSERT_MSG(It != G_AttributeInfoSpawners.cend(),
           "Attribute name \"%s\" is not present in the map", ((std::string)AttributeNameString).c_str());

        const CAttributeInfoSpawner& AttributeInfoSpawner = It->second;
        return AttributeInfoSpawner();
    }

    CClassReader& operator>>(CClassReader& Reader, CSerializedArrayOfAttributes& Instance)
    {
        CSerializedArrayOfAttributes::NumItemsType NumItems = 0;
        Reader >> NumItems;
        Instance.Clear(NumItems);

        for (usz i = 0; i < (usz)NumItems; ++i)
        {
            u2 AttributeNameIndex = (u2)0;
            Reader >> AttributeNameIndex;

            u4 AttributeLength = (u4)0;
            Reader >> AttributeLength;

            std::shared_ptr<CConstantUtf8Info> AttributeName =
                Reader.GetConstantPool()->Get<CConstantUtf8Info>(AttributeNameIndex);

            const Util::CStringUtf8& AttributeNameString = AttributeName->GetStringUtf8();

            CSharedAttributeInfo AttributeInfo = NewAttributeInfo(AttributeNameString);
            ASSERT(AttributeInfo != nullptr);

            {
                CScopeAttributeInfoDeserializeTracker ScopeTracker(AttributeLength, Reader);
                AttributeInfo->DeserializeFrom(Reader);
            }

            Instance.Items.push_back(std::move(AttributeInfo));
        }

        return Reader;
    }
}