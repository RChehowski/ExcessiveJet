
#include "ClassReader.h"
#include "ClassInfo.h"

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

    TraverseDirectory("C:\\Users\\ASUS\\Desktop\\rt", [&](const std::string FileName)
    {
        if (FileName.find(ClassFileExtension, FileName.size() - ClassFileExtension.size()) != std::string::npos)
        {
            std::cout << "Parsing class from file: " << FileName << std::endl;

            CClassReader MemoryReader(FileName);

            CClassInfo ClassInfo;
            MemoryReader >> ClassInfo;

            ++NumParsedClasses;

//            ClassInfo.Debug_PrintClass();
        }
    });

    std::cout << ">> Number of parsed classes: " << NumParsedClasses << std::endl;
}
