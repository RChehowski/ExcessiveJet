
#include "ConstantPool/ConstantLongInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantLongInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantLongInfo {" << std::endl;
        oss << "           HighBytes: " << HighBytes << std::endl;
        oss << "            LowBytes: " << LowBytes << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantLongInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> HighBytes;
        Reader >> LowBytes;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantLongInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}