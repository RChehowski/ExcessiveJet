
#include "ConstantPool/ConstantMethodRefInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantMethodRefInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantMethodRefInfo& Instance)
    {
        Reader >> Instance.ClassIndex;
        Reader >> Instance.NameAndTypeIndex;
    }
}