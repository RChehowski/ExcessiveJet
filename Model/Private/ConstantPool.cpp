//
// Created by ASUS on 27/12/2020.
//

#include "MemoryFile.h"
#include "ConstantPool.h"

#include "AttributeType.h"

#include "ConstantPool/ConstantUtf8Info.h"

namespace Parse
{
    CConstantPool::~CConstantPool()
    {
        for (CConstantInfo* ConstantInfo : ConstantInfos)
        {
            delete ConstantInfo;
        }
        ConstantInfos.clear();
    }

    void CConstantPool::ForEach(const CBiConsumer& BiConsumer)
    {
        for (usz Index = 0; Index < (usz)ConstantInfos.size(); ++Index)
        {
            CConstantInfo* const ConstantInfo = ConstantInfos[Index];
            const usz IndexInConstantPool = Index + 1;

            BiConsumer(IndexInConstantPool, ConstantInfo);
        }
    }

    void CConstantPool::ForEach(const CBiConsumer& BiConsumer, EConstantPoolInfoTag ConstantPoolInfoTag)
    {
        for (usz Index = 0; Index < (usz)ConstantInfos.size(); ++Index)
        {
            CConstantInfo* const ConstantInfo = ConstantInfos[Index];
            const usz IndexInConstantPool = Index + 1;

            if (ConstantInfo->GetConstantPoolInfoTag() == ConstantPoolInfoTag)
            {
                BiConsumer(IndexInConstantPool, ConstantInfo);
            }
        }
    }

    const CAttributeType* CConstantPool::GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool)
    {
        CConstantUtf8Info* const ConstantUtf8Info = Get<CConstantUtf8Info>((usz)IndexInConstantPool);
        return CAttributeTypes::GetAttributeNameByName(ConstantUtf8Info->GetStringUtf8());
    }


    CConstantInfo* CConstantPool::operator[] (const usz IndexInConstantPool)
    {
        ASSERT((IndexInConstantPool >= 1) && (IndexInConstantPool <= ConstantInfos.size()));
        return ConstantInfos[IndexInConstantPool - 1];
    }


    void operator>>(Util::CMemoryReader& Reader, CConstantPool& Instance)
    {
        u2 ConstantPoolCount = (u2)0;
        Reader >> ConstantPoolCount;

        Instance.ConstantInfos.clear();
        Instance.ConstantInfos.reserve((size_t)ConstantPoolCount);

        for (u2 ConstantPoolIndex = 1; ConstantPoolIndex < ConstantPoolCount; ++ConstantPoolIndex)
        {
            u1 TagByte = (u1)0;
            Reader >> TagByte;

            CConstantInfo* const ConstantInfo =
                    CConstantInfo::NewConstantInfo(CConstantInfo::GetConstantPoolInfoTagByByte(TagByte));
            Reader >> *ConstantInfo;

            Instance.ConstantInfos.push_back(ConstantInfo);
        }
    }
}
