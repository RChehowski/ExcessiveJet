//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_MEMORYFILE_H
#define CPP20_MEMORYFILE_H

#include <string>

namespace Util
{
    class MemoryFile
    {
    public:
        explicit MemoryFile(const WideString& InFileName);

    private:
        std::wstring FileName;

        size_t FileSize;
        uint8_t* FileBytes;
    };
}


#endif //CPP20_MEMORYFILE_H
