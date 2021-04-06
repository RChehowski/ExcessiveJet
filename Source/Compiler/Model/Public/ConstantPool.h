//
// Created by ASUS on 27/12/2020.
//

#pragma once

#include "Types.h"
#include "ExcessiveAssert.h"
#include "ConstantPool/ConstantInfo.h"

#include <vector>
#include <functional>


namespace Compiler
{
    class CClassReader;
    class CConstantInfo;
    class CAttributeType;

    class CConstantPool
    {
//        using CBiConsumer = std::function<void(
//            usz,            // Index in ConstantInfos
//            CConstantInfo*  // CConstantInfo
//        )>;

    public:
        [[nodiscard]]
        const CAttributeType* GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool) const;

        std::shared_ptr<CConstantInfo> operator[] (usz IndexInConstantPool) const;

        template<class T>
        FORCEINLINE std::shared_ptr<T> Get(usz IndexInConstantPool) const
        {
            return CConstantInfo::CastConstantInfo<T>((*this)[IndexInConstantPool]);
        }

        friend void operator>>(CClassReader& Reader, CConstantPool& Instance);

    private:
        std::vector<std::shared_ptr<CConstantInfo>> ConstantInfos;
    };
}
