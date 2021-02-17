//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_FILEUTILS_H
#define CPP20_FILEUTILS_H

#include "Types.h"
#include "Allocation.h"

namespace Util
{
    class CFileUtils
    {
    public:
        static CAllocation ReadFile(const std::string& FileName, usz* OutFileSizePtr = nullptr);
    };
}

#endif //CPP20_FILEUTILS_H
