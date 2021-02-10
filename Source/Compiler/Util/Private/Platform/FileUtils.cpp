//
// Created by ASUS on 29/12/2020.
//

#include "Platform/FileUtils.h"

namespace Util
{
    CAllocation FileUtils::ReadFile(const std::string& FileName)
    {
        FILE* File = fopen(FileName.c_str(), "rb");

        if (File != nullptr)
        {
            fseek(File, 0, SEEK_END);
            const usz FileSize = (usz)ftell(File);
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