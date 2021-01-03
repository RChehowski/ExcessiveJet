
#include "ConstantPool/ConstantFloatInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantFloatInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantFloatInfo {" << std::endl;
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantFloatInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> Bytes;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantFloatInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}