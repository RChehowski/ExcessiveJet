//
// Created by ASUS on 29/12/2020.
//

#include "Platform/FileUtils.h"

namespace Util
{
    CAllocation FileUtils::ReadFile(const WideString& FileName)
    {
        FILE* File = nullptr;
        _wfopen_s(&File, FileName.c_str(), L"rb");

        if (File != nullptr)
        {
            fseek(File, 0, SEEK_END);
            const usz FileSize = (usz)_ftelli64(File);
            fseek(File, 0, SEEK_SET);

            CAllocation Allocation(FileSize);

            fread(Allocation.Get<void*>(), FileSize, 1, File);
            fclose(File);

            return std::move(Allocation);
        }
        else
        {
            return CAllocation::EmptyAllocation();
        }
    }
}