
#include "Model/ConstantPool/ConstantIntegerInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantIntegerInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantIntegerInfo {" << std::endl;
        oss << "               Value: " << Value << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantIntegerInfo::DeserializeFrom(CClassReader& Reader)
    {
        u4 Bytes;
        Reader >> Bytes;

        Value = *reinterpret_cast<const s4*>(&Bytes);
    }

    std::string CConstantIntegerInfo::ToResolvedString(const CConstantPool& ConstantPool) const
    {
        return std::to_string(GetInteger());
    }

}