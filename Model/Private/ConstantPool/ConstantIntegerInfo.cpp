
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

    void CConstantIntegerInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> Bytes;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantIntegerInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}