//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_FILEUTILS_H
#define CPP20_FILEUTILS_H

#include "Util/Types.h"
#include "Util/Allocation.h"

namespace Util
{
    class CFileUtils
    {
    public:
        static CAllocation ReadFile(const std::string& FileName, usz& OutFileSizePtr);
    };
}

#endif //CPP20_FILEUTILS_H
