
#include "ConstantPool/ConstantDoubleInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantDoubleInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantDoubleInfo {" << std::endl;
        oss << "           HighBytes: " << HighBytes << std::endl;
        oss << "            LowBytes: " << LowBytes << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantDoubleInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> HighBytes;
        Reader >> LowBytes;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantDoubleInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}