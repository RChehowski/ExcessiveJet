//
// Created by ASUS on 04/01/2021.
//

#include "Attributes/AttributeInfo.h"

#include "MemoryFile.h"

namespace Parse
{
    #pragma region CScopeAttributeInfoDeserializeTracker
    CScopeAttributeInfoDeserializeTracker::CScopeAttributeInfoDeserializeTracker(
            CAttributeInfo &InAttributeInfo,
            Util::CMemoryReader &InReader
    ) : AttributeInfo(InAttributeInfo), Reader(InReader), DeserializeBegin(Reader.Tell())
    {
    }

    CScopeAttributeInfoDeserializeTracker::~CScopeAttributeInfoDeserializeTracker()
    {
        const usz BytesRead = Reader.Tell() - DeserializeBegin;
        ASSERT(BytesRead == AttributeInfo.GetAttributeLength());
    }
    #pragma endregion
}