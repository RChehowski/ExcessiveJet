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
        static FileInputStream ReadFile(const SystemPath& Path);
    };
}

#endif //CPP20_FILEUTILS_H
