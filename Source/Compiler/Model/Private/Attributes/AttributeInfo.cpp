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
        CScopeAttributeInfoDeserializeTracker(CAttributeInfo &InAttributeInfo, CClassReader &InReader);
        ~CScopeAttributeInfoDeserializeTracker();

    private:
        const CAttributeInfo& AttributeInfo;
        const CClassReader& Reader;

        const usz DeserializeBegin;
    };

    CScopeAttributeInfoDeserializeTracker::CScopeAttributeInfoDeserializeTracker(
            CAttributeInfo &InAttributeInfo,
            CClassReader &InReader
    )
    : AttributeInfo(InAttributeInfo)
    , Reader(InReader)
    , DeserializeBegin(Reader.Tell())
    {
    }

    CScopeAttributeInfoDeserializeTracker::~CScopeAttributeInfoDeserializeTracker()
    {
//        const usz BytesRead = Reader.Tell() - DeserializeBegin;
//        ASSERT(BytesRead == AttributeInfo.GetAttributeLength());
    }
    #pragma endregion


    CClassReader& operator>>(CClassReader& Reader, CAttributeInfo& Instance)
    {
        CScopeAttributeInfoDeserializeTracker ScopeAttributeInfoDeserializeTracker(Instance, Reader);
        Instance.DeserializeFrom(Reader);

        return Reader;
    }


    using CAttributeInfoSpawner = std::function<CSharedAttributeInfo()>;
    using CAttributeInfoSpawners = std::unordered_map<Util::IStringUtf8, CAttributeInfoSpawner>;


    CAttributeInfoSpawners G_AttributeInfoSpawners {
        DEFINE_ATTRIBUTE_INFO_SPAWNER(Deprecated),
        DEFINE_ATTRIBUTE_INFO_SPAWNER(Code),
        DEFINE_ATTRIBUTE_INFO_SPAWNER(LineNumberTable),
        DEFINE_ATTRIBUTE_INFO_SPAWNER(LocalVariableTable),
        DEFINE_ATTRIBUTE_INFO_SPAWNER(Exceptions),
        DEFINE_ATTRIBUTE_INFO_SPAWNER(LocalVariableTypeTable),
        // TODO: Support all of them!
//        DEFINE_ATTRIBUTE_INFO_SPAWNER(RuntimeVisibleAnnotations),
    };

    CSharedAttributeInfo NewAttributeInfo(const Util::CStringUtf8& AttributeNameString)
    {
        auto It = G_AttributeInfoSpawners.find(AttributeNameString);

        ASSERT_MSG(It != G_AttributeInfoSpawners.end(),
               "Attribute name \"%s\" is not present in the map", ((std::string)AttributeNameString).c_str());

        return It->second();
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

            AttributeInfo->DeserializeFrom(Reader);

            Instance.Items.push_back(std::shared_ptr<CAttributeInfo>(AttributeInfo));
        }

        return Reader;
    }
}