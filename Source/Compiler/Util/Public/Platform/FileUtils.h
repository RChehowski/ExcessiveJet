//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_FILEUTILS_H
#define CPP20_FILEUTILS_H

#include <Types.h>

namespace Util
{
    class FileUtils
    {
    public:
        static u1* ReadFile(const WideString& FileName, usz* OutNumBytes);
    };
}

#endif //CPP20_FILEUTILS_H
