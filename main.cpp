
#include "ClassReader.h"

#include "FieldInfo.h"
#include "ClassInfo.h"

using Util::CByteOrders;
using Parse::CClassInfo;
using Parse::CClassReader;


int main()
{
    CClassReader MemoryReader(L"C:\\Users\\ASUS\\Desktop\\rt\\java\\lang\\Number.class");

    CClassInfo ClassInfo;
    MemoryReader >> ClassInfo;

    ClassInfo.Debug_PrintClass();
}
