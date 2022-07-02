
#include "Model/ConstantPool/ConstantDoubleInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantDoubleInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantDoubleInfo {" << std::endl;
        oss << "           HighBytes: " << HighBytes << std::endl;
        oss << "            LowBytes: " << LowBytes << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantDoubleInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> HighBytes;
        Reader >> LowBytes;
    }

    void operator>>(CClassReader& Reader, CConstantDoubleInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}