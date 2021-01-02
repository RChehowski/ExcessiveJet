
#include "ConstantPool/ConstantIntegerInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantIntegerInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantIntegerInfo {" << std::endl;
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantIntegerInfo& Instance)
    {
        Reader >> Instance.Bytes;
    }
}