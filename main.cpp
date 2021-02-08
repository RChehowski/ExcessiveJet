
#include "ClassReader.h"
#include "ClassInfo.h"
#include "MethodInfo.h"

using Util::CByteOrders;
using Compiler::CClassInfo;
using Compiler::CClassReader;


#include <string>
#include <iostream>
#include <filesystem>

void TraverseDirectory(const std::string& Root, std::function<void(const std::string&)> Consumer)
{
    for (const auto & entry : std::filesystem::directory_iterator(Root))
    {
        if (std::filesystem::is_directory(entry.path()))
        {
            // Recurse
            TraverseDirectory(entry.path().string(), Consumer);
        }
        else if (std::filesystem::is_regular_file(entry.path()))
        {
            Consumer(entry.path().string());
        }
    }
}

int main()
{
    std::string ClassFileExtension = ".class";

    usz NumParsedClasses = 0;
    usz NumNativeMethods = 0;

    TraverseDirectory("C:\\Users\\ASUS\\Desktop\\rt\\java\\awt", [&](const std::string FileName)
    {
        if (FileName.find(ClassFileExtension, FileName.size() - ClassFileExtension.size()) != std::string::npos)
        {
            std::cout << "Parsing class from file: " << FileName << std::endl;

            CClassReader MemoryReader(FileName);

            CClassInfo ClassInfo;
            MemoryReader >> ClassInfo;

            for (const auto& Item : ClassInfo.GetMethods())
            {
                if (Item.GetAccessFlags() & Compiler::EMethodAccessFlags::ACC_NATIVE)
                {
                    ++NumNativeMethods;
                }
            }

            ++NumParsedClasses;
        }
    });

    std::cout << ">> Number of parsed classes: " << NumParsedClasses << std::endl;
    std::cout << ">> Number of native methods: " << NumNativeMethods << std::endl;
}
