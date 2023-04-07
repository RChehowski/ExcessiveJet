
#include "Model/ConstantPool/ConstantLongInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantLongInfo::ToLowLevelString() const
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

    std::string CConstantLongInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return std::to_string(GetLong());
    }

}