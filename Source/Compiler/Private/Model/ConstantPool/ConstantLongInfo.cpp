
#include "Model/ConstantPool/ConstantLongInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantLongInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantLongInfo {" << std::endl;
        oss << "           HighBytes: " << HighBytes << std::endl;
        oss << "            LowBytes: " << LowBytes << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantLongInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> HighBytes;
        Reader >> LowBytes;
    }

    void operator>>(CClassReader& Reader, CConstantLongInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}