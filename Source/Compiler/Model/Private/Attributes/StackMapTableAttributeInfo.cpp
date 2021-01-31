//
// Created by ASUS on 10/01/2021.
//

#include "Attributes/StackMapTableAttributeInfo.h"

#include <unordered_map>
#include <functional>

#define ADD_CONSTANT_INFO(Name)\
    {EVariableInfoTag::Name, [](EVariableInfoTag Tag){return std::make_shared<C##Name##VariableInfo>(Tag);}}

namespace Parse
{
    using CVarialbeInfoSpawnFunction = std::function<std::shared_ptr<CVariableInfo>(EVariableInfoTag)>;
    using CTagToVarialbeInfoSpawnFunction = std::unordered_map<EVariableInfoTag, CVarialbeInfoSpawnFunction>;

    const CTagToVarialbeInfoSpawnFunction G_TagToVarialbeInfoSpawnFunction {
        ADD_CONSTANT_INFO(Top),
        ADD_CONSTANT_INFO(Integer),
        ADD_CONSTANT_INFO(Float),
        ADD_CONSTANT_INFO(Double),
        ADD_CONSTANT_INFO(Long),
        ADD_CONSTANT_INFO(Null),
        ADD_CONSTANT_INFO(UninitializedThis),
        ADD_CONSTANT_INFO(Object),
        ADD_CONSTANT_INFO(Uninitialized),
    };

    void operator>>(CClassReader& Reader, CVariableInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}
