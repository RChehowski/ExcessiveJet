//
// Created by ASUS on 29/12/2020.
//

#include "Platform/Memory.h"
#include "Platform/FileUtils.h"

namespace Util
{
    u1* FileUtils::ReadFile(const WideString& FileName, usz* OutNumBytes)
    {
        FILE* File = nullptr;
        _wfopen_s(&File, FileName.c_str(), L"rb");

        if (File != nullptr)
        {
            fseek(File, 0, SEEK_END);
            const usz FileSize = (usz)_ftelli64(File);
            fseek(File, 0, SEEK_SET);

            u1* const Data = (u1*)Memory::Malloc(FileSize);
            fread(Data, FileSize, 1, File);
            fclose(File);

            if (OutNumBytes)
            {
                *OutNumBytes = FileSize;
            }

            return Data;
        }
        else
        {
            if (OutNumBytes)
            {
                *OutNumBytes = 0;
            }

            return false;
        }
    }
}