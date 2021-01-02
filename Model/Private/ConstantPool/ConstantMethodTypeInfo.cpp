
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantMethodTypeInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodTypeInfo {" << std::endl;
        oss << "     DescriptorIndex: " << DescriptorIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantMethodTypeInfo& Instance)
    {
        Reader >> Instance.DescriptorIndex;
    }
}