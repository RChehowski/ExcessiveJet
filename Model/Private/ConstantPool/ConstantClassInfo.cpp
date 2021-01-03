
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

    void CConstantClassInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> NameIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantClassInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}