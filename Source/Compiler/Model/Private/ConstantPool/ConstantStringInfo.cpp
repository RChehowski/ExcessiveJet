
#include "ConstantPool/ConstantStringInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantStringInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantStringInfo {" << std::endl;
        oss << "         StringIndex: " << StringIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantStringInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> StringIndex;
    }

    void operator>>(CClassReader& Reader, CConstantStringInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}