
#include "ConstantPool/ConstantInterfaceMethodRefInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantInterfaceMethodRefInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantInterfaceMethodRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantInterfaceMethodRefInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantInterfaceMethodRefInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}