
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

    void CConstantMethodRefInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantMethodRefInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}