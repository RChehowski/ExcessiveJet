
#include "Model/ConstantPool/ConstantFloatInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantFloatInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantFloatInfo {" << std::endl;
        oss << "               Value: " << Value << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantFloatInfo::DeserializeFrom(CClassReader& Reader)
    {
        u4 Bytes;
        Reader >> Bytes;

        Value = *reinterpret_cast<const float*>(&Bytes);
    }

    std::string CConstantFloatInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return std::to_string(GetFloat());
    }

}