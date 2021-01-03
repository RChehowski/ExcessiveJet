
#include "ConstantPool/ConstantStringInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantStringInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantStringInfo {" << std::endl;
        oss << "         StringIndex: " << StringIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantStringInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> StringIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantStringInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}