//
// Created by ASUS on 27/12/2020.
//

#pragma once

#include "Util/Types.h"
#include "Util/ExcessiveAssert.h"

// Include all constant info subclasses to avoid including them explicitly
#include "ConstantPool/ConstantInfos.h"

#include <vector>
#include <functional>


namespace Compiler
{
    class CClassReader;
    class CConstantInfo;
    class CAttributeType;

    class CConstantPool
    {
    public:
        [[nodiscard]]
        const CAttributeType* GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool) const;

        std::shared_ptr<CConstantInfo> operator[] (usz IndexInConstantPool) const;

        template<class T>
        FORCEINLINE std::shared_ptr<T> Get(usz IndexInConstantPool) const
        {
            return CConstantInfo::CastConstantInfo<T>((*this)[IndexInConstantPool]);
        }

        template<
            typename TConstantInfo,
            std::enable_if_t<std::is_base_of<CConstantInfo, TConstantInfo>::value, bool> = true
        >
        FORCEINLINE void ForEachOfType(const std::function<void(const TConstantInfo&)>& Consumer) const
        {
            for (const std::shared_ptr<CConstantInfo>& ConstantInfo : ConstantInfos)
            {
                if (ConstantInfo->IsA<TConstantInfo>())
                {
                    const std::shared_ptr<TConstantInfo> CastConstantInfo =
                            CConstantInfo::CastConstantInfo<TConstantInfo>(ConstantInfo);

                    Consumer(*CastConstantInfo);
                }
            }
        }

        template<
            typename TConstantInfo,
            std::enable_if_t<std::is_base_of<CConstantInfo, TConstantInfo>::value, bool> = true
        >
        FORCEINLINE std::vector<std::shared_ptr<TConstantInfo>> GetEachOfType() const
        {
            std::vector<std::shared_ptr<TConstantInfo>> Result;
            for (const std::shared_ptr<CConstantInfo>& ConstantInfo : ConstantInfos)
            {
                if (ConstantInfo->IsA<TConstantInfo>())
                {
                    std::shared_ptr<TConstantInfo> CastConstantInfo =
                        CConstantInfo::CastConstantInfo<TConstantInfo>(ConstantInfo);

                    Result.push_back(std::move(CastConstantInfo));
                }
            }

            return Result;
        }

        friend void operator>>(CClassReader& Reader, CConstantPool& Instance);

    private:
        std::vector<std::shared_ptr<CConstantInfo>> ConstantInfos;
    };
}
