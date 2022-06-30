//
// Created by ASUS on 27/12/2020.
//

#include "Model/ConstantPool.h"
#include "Model/ClassReader.h"

#include "Model/AttributeType.h"
#include "Model/ConstantPool/ConstantUtf8Info.h"
#include "Model/ConstantPool/ConstantLongInfo.h"
#include "Model/ConstantPool/ConstantDoubleInfo.h"


namespace Compiler
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

        void DeserializeFrom(CClassReader& Reader) override
        {
        }

        static std::shared_ptr<CConstantInfo> GetPhantomConstantInfo()
        {
            static std::shared_ptr<CConstantInfo> PhantomConstantInfo = std::make_shared<CPhantomConstantInfo>();
            return PhantomConstantInfo;
        }
    };
#pragma endregion


    const CAttributeType* CConstantPool::GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool) const
    {
        return CAttributeTypes::GetAttributeNameByName(Get<CConstantUtf8Info>((usz)IndexInConstantPool)->GetStringUtf8());
    }

    std::shared_ptr<CConstantInfo> CConstantPool::operator[] (const usz IndexInConstantPool) const
    {
        ASSERT_MSG((IndexInConstantPool >= 1) && (IndexInConstantPool <= ConstantInfos.size()),
                   "Requested index: %llu", (unsigned long long)IndexInConstantPool
        );
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

            /**
             * @spec:
             * Additionally, two types of constants (longs and doubles) take up two consecutive slots in the table,
             * although the second such slot is a phantom index that is never directly used.
             */
            const bool bNeedsPhantomConstantInfo = ConstantInfo->IsA<CConstantDoubleInfo>() || ConstantInfo->IsA<CConstantLongInfo>();
            if (bNeedsPhantomConstantInfo)
            {
                ConstantPoolIndex++;

                Instance.ConstantInfos.push_back(CPhantomConstantInfo::GetPhantomConstantInfo());
            }
        }
    }
}
