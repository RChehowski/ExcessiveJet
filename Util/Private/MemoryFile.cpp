//
// Created by ASUS on 29/12/2020.
//


#include <Platform/FileUtils.h>
#include "MemoryFile.h"

namespace Util
{
    MemoryFile::MemoryFile(const WideString& InFileName) : FileName(InFileName)
    {
        this->FileBytes = FileUtils::ReadFile(FileName, &(this->FileSize));
    }
}