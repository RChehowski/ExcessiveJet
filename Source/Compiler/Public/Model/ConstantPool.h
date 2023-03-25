//
// Created by ASUS on 27/12/2020.
//

#pragma once

#include "Util/Types.h"
#include "Util/ExcessiveAssert.h"

// Include all constant info subclasses to avoid including them explicitly
#include "Model/ConstantPool/ConstantInfos.h"

#include <vector>
#include <functional>


namespace Compiler
{
    class CClassReader;
    class CConstantInfo;
    class CAttributeType;

    class CConstantPool
    {
    	//
	    CConstantInfo* operator[] (usz IndexInConstantPool) const;

    public:
	    virtual ~CConstantPool();

	    [[nodiscard]]
        const CAttributeType* GetAttributeTypeByIndexInConstantPool(u2 IndexInConstantPool) const;

	    template<typename T>
	    FORCEINLINE const T* Get(usz IndexInConstantPool) const
	    {
		    CConstantInfo* const ConstantInfo = (*this)[IndexInConstantPool];

		    // This method is allowed to return nullptr
		    if (ConstantInfo == nullptr)
		    {
		    	return nullptr;
		    }

		    if constexpr (std::is_same_v<T, CConstantInfo>)
		    {
			    return ConstantInfo;
		    }
		    else
		    {
			    return &CConstantInfo::CastConstantInfo<T>(*ConstantInfo);
		    }
	    }

        template<typename T>
        FORCEINLINE const T& GetChecked(usz IndexInConstantPool) const
        {
            const T* Value = Get<T>(IndexInConstantPool);
			ASSERT(Value != nullptr);

			return *Value;
        }

#if UNLOCK_DEBUG_METHODS
        template<
            typename TConstantInfo,
            std::enable_if_t<std::is_base_of<CConstantInfo, TConstantInfo>::value, bool> = true
        >
        FORCEINLINE void DEBUG_ForEachOfType(std::function<void(const TConstantInfo&)>&& Consumer) const
        {
            for (const CConstantInfo* ConstantInfo : ConstantInfos)
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
        FORCEINLINE std::vector<std::shared_ptr<TConstantInfo>> DEBUG_GetEachOfType() const
        {
            std::vector<std::shared_ptr<TConstantInfo>> Result;
            for (const CConstantInfo* ConstantInfo : ConstantInfos)
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
#endif // UNLOCK_DEBUG_METHODS

        friend void operator>>(CClassReader& Reader, CConstantPool& Instance);

    private:
        std::vector<CConstantInfo*> ConstantInfos;
    };
}
