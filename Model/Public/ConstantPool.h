//
// Created by ASUS on 27/12/2020.
//

#pragma once

#include "Types.h"
#include "Assert.h"
#include "ConstantPool/ConstantInfo.h"

#include <vector>
#include <functional>

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantInfo;
    class CAttributeType;

    class CConstantPool
    {
        using CBiConsumer = std::function<void(
            usz,            // Index in ConstantInfos
            CConstantInfo*  // CConstantInfo
        )>;

    public:
        ~CConstantPool();

        void ForEach(const CBiConsumer& BiConsumer);

        void ForEach(const CBiConsumer& BiConsumer, EConstantPoolInfoTag ConstantPoolInfoTag);

        const CAttributeType* GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool);


        CConstantInfo* operator[] (usz IndexInConstantPool);

        template<class T>
        FORCEINLINE T* Get(usz IndexInConstantPool)
        {
            CConstantInfo* const ConstantInfo = (*this)[IndexInConstantPool];
            return CConstantInfo::CastConstantInfo<T>(ConstantInfo);
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantPool& Instance);

    private:
        std::vector<CConstantInfo*> ConstantInfos;
    };
}
