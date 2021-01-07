//
// Created by ASUS on 04/01/2021.
//

#include "MemoryFile.h"
#include "Attributes/AttributeInfo.h"


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
        usz BytesRead = Reader.Tell() - DeserializeBegin;
        ASSERT(BytesRead == AttributeInfo.GetAttributeLength());
    }
    #pragma endregion
}