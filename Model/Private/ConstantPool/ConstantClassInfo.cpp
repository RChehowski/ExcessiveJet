
#include "ConstantPool/ConstantClassInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantClassInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantClassInfo {" << std::endl;
        oss << "           NameIndex: " << NameIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantClassInfo& Instance)
    {
        Reader >> Instance.NameIndex;
    }
}