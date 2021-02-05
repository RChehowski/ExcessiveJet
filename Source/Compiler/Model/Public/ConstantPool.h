//
// Created by ASUS on 27/12/2020.
//

#pragma once

#include "Types.h"
#include "Assert.h"
#include "ConstantPool/ConstantInfo.h"

#include <vector>
#include <functional>


namespace Parse
{
    class CClassReader;
    class CConstantInfo;
    class CAttributeType;

    class CConstantPool
    {
        using CBiConsumer = std::function<void(
            usz,            // Index in ConstantInfos
            CConstantInfo*  // CConstantInfo
        )>;

    public:
        const CAttributeType* GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool);

        std::shared_ptr<CConstantInfo> operator[] (usz IndexInConstantPool);

        template<class T>
        FORCEINLINE std::shared_ptr<T> Get(usz IndexInConstantPool)
        {
            return CConstantInfo::CastConstantInfo<T>((*this)[IndexInConstantPool]);
        }

        friend void operator>>(CClassReader& Reader, CConstantPool& Instance);

    private:
        std::vector<std::shared_ptr<CConstantInfo>> ConstantInfos;
    };
}
