//
// Created by ASUS on 27/12/2020.
//

#include "ConstantPool.h"
#include "ClassReader.h"

#include "AttributeType.h"
#include "ConstantPool/ConstantUtf8Info.h"
#include "ConstantPool/ConstantLongInfo.h"
#include "ConstantPool/ConstantDoubleInfo.h"


namespace Parse
{
#pragma region CPhantomConstantInfo
    /**
     * Phantom constant info is used as the following dummy info for Long and Double constants.
     */
    class CPhantomConstantInfo final : public CConstantInfo
    {
    public:
        CPhantomConstantInfo() : CConstantInfo(EConstantPoolInfoTag::Invalid_NotATag)
        {
        }

        ~CPhantomConstantInfo() override = default;

        [[nodiscard]]
        std::string ToString() const override
        {
            return "CPhantomConstantInfo";
        }

        virtual void DeserializeFrom(CClassReader& Reader) override
        {
        }
    };

    std::shared_ptr<CConstantInfo> G_PhantomConstantInfo = std::make_shared<CPhantomConstantInfo>();
#pragma endregion


    const CAttributeType* CConstantPool::GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool)
    {
        return CAttributeTypes::GetAttributeNameByName(Get<CConstantUtf8Info>((usz)IndexInConstantPool)->GetStringUtf8());
    }

    std::shared_ptr<CConstantInfo> CConstantPool::operator[] (const usz IndexInConstantPool) const
    {
        ASSERT((IndexInConstantPool >= 1) && (IndexInConstantPool <= ConstantInfos.size()));
        return ConstantInfos[IndexInConstantPool - 1];
    }

    void operator>>(CClassReader& Reader, CConstantPool& Instance)
    {
        u2 ConstantPoolCount = (u2)0;
        Reader >> ConstantPoolCount;

        Instance.ConstantInfos.clear();
        Instance.ConstantInfos.reserve((size_t)ConstantPoolCount);

        for (u2 ConstantPoolIndex = 1; ConstantPoolIndex < ConstantPoolCount; ++ConstantPoolIndex)
        {
            u1 TagByte = (u1)0;
            Reader >> TagByte;

            std::shared_ptr<CConstantInfo> ConstantInfo = CConstantInfo::NewConstantInfo((EConstantPoolInfoTag)TagByte);
            Reader >> ConstantInfo;

            Instance.ConstantInfos.push_back(ConstantInfo);

            if (ConstantInfo->IsA<CConstantDoubleInfo>() || ConstantInfo->IsA<CConstantLongInfo>())
            {
                // @spec:
                //  Additionally, two types of constants (longs and doubles) take up two consecutive slots in the table,
                //  although the second such slot is a phantom index that is never directly used.
                ConstantPoolIndex++;

                Instance.ConstantInfos.push_back(G_PhantomConstantInfo);
            }
        }
    }
}
