
#include "ClassReader.h"
#include "ClassInfo.h"

using Util::CByteOrders;
using Parse::CClassInfo;
using Parse::CClassReader;


int main()
{
    CClassReader MemoryReader(L"C:\\Users\\ASUS\\Desktop\\rt\\java\\lang\\Object.class");

    CClassInfo ClassInfo;
    MemoryReader >> ClassInfo;

    ClassInfo.Debug_PrintClass();
}
