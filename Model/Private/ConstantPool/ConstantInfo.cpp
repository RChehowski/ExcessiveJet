//
// Created by ASUS on 02/01/2021.
//

#include "ConstantPool/ConstantInfo.h"

namespace Parse
{
    void operator>>(Util::CMemoryReader &Reader, CConstantInfo &Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}