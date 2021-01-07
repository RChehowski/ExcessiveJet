//
// Created by ASUS on 29/12/2020.
//

#include <locale>
#include <codecvt>
#include <filesystem>
#include <fstream>
#include "Platform/Memory.h"
#include "Platform/FileUtils.h"

namespace Util
{
    FileInputStream FileUtils::ReadFile(const SystemPath& Path)
    {
        FileInputStream fs;
        if (std::filesystem::exists(Path) && !std::filesystem::is_directory(Path))
        {
            std::filesystem::path real_path = Path;
            if (std::filesystem::is_symlink(Path))
            {
                real_path = std::filesystem::read_symlink(Path);
            }

            fs.open(real_path, std::fstream::in | std::fstream::binary);
        }
        else
        {
            if(fs.is_open())
            {
                fs.close();
            }
        }

        return fs;
    }
}