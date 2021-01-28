
#include "ConstantPool/ConstantFloatInfo.h"
#include "ClassReader.h"

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

    void CConstantFloatInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> Bytes;
    }

    void operator>>(CClassReader& Reader, CConstantFloatInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}