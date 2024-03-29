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
	CConstantInfo* CConstantPool::operator[] (const usz IndexInConstantPool) const
	{
		ASSERT_MSG((IndexInConstantPool >= 1) && (IndexInConstantPool <= ConstantInfos.size()),
		           "Requested index: %llu", (unsigned long long)IndexInConstantPool
		);

		return ConstantInfos[IndexInConstantPool - 1];
	}

	CConstantPool::~CConstantPool()
	{
		for (CConstantInfo* ConstantInfo : ConstantInfos)
		{
			// Delete everything except phantom infos because they're a singleton
			if (!ConstantInfo->IsA<CPhantomConstantInfo>())
			{
				delete ConstantInfo;
			}
		}
	}

    void operator>>(CClassReader& Reader, CConstantPool& Instance)
    {
        u2 ConstantPoolCount = (u2)0;
        Reader >> ConstantPoolCount;

	    std::vector<CConstantInfo*>& ConstantInfos = Instance.ConstantInfos;

        ConstantInfos.clear();
        ConstantInfos.reserve(static_cast<size_t>(ConstantPoolCount));

        for (u2 ConstantPoolIndex = 1; ConstantPoolIndex < ConstantPoolCount; ++ConstantPoolIndex)
        {
            u1 TagByte = static_cast<u1>(0);
            Reader >> TagByte;

	        const EConstantPoolInfoTag ConstantPoolInfoTag = static_cast<EConstantPoolInfoTag>(TagByte);

            CConstantInfo* const ConstantInfo = CConstantInfo::NewConstantInfo(ConstantPoolInfoTag);
            Reader >> *ConstantInfo;

            ConstantInfos.push_back(ConstantInfo);

            /**
             * @spec:
             * Additionally, two types of constants (longs and doubles) take up two consecutive slots in the table,
             * although the second such slot is a phantom index that is never directly used.
             */
            if (ConstantInfo->IsFollowedByPhantomInfo())
            {
                ++ConstantPoolIndex;

                ConstantInfos.push_back(CPhantomConstantInfo::GetInstance());
            }
        }
    }
}
