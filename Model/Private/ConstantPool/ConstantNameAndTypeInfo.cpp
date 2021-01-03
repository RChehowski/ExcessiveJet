
#include "ConstantPool/ConstantNameAndTypeInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantNameAndTypeInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantNameAndTypeInfo {" << std::endl;
        oss << "           NameIndex: " << NameIndex << std::endl;
        oss << "     DescriptorIndex: " << DescriptorIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantNameAndTypeInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> NameIndex;
        Reader >> DescriptorIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantNameAndTypeInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}