
#include "ConstantPool/ConstantIntegerInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantIntegerInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantIntegerInfo {" << std::endl;
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantIntegerInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> Bytes;
    }

    void operator>>(CClassReader& Reader, CConstantIntegerInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}