
#include "ConstantPool/ConstantClassInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantClassInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantClassInfo {" << std::endl;
        oss << "           NameIndex: " << NameIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantClassInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> NameIndex;
    }

    void operator>>(CClassReader& Reader, CConstantClassInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}