
#include "ConstantPool/ConstantInterfaceMethodRefInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantInterfaceMethodRefInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantInterfaceMethodRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantInterfaceMethodRefInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(CClassReader& Reader, CConstantInterfaceMethodRefInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}