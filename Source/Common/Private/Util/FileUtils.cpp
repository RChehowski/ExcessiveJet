//
// Created by ASUS on 29/12/2020.
//

#include "Util/FileUtils.h"

namespace Util
{
    CAllocation CFileUtils::ReadFile(const std::string& FileName, bool& bFileOpened)
    {
        FILE* File = nullptr;

#if PLATFORM_WINDOWS
        fopen_s(&File, FileName.c_str(), "rb");
#else
        File = fopen(FileName.c_str(), "rb");
#endif

        bFileOpened = (File != nullptr);

        if (bFileOpened)
        {
            fseek(File, 0, SEEK_END);
            const usz FileSize = (usz)ftell(File);
            fseek(File, 0, SEEK_SET);

            CAllocation Allocation(FileSize);

            fread((void*)Allocation, FileSize, 1, File);
            fclose(File);

            return Allocation;
        }
        else
        {
            return CAllocation::EmptyAllocation();
        }
    }
}