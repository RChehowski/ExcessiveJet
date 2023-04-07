
#include "Model/ConstantPool/ConstantFloatInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantFloatInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantFloatInfo {" << std::endl;
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantFloatInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> Bytes;
    }

    void operator>>(CClassReader& Reader, CConstantFloatInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::string CConstantFloatInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return std::to_string(GetFloat());
    }

}