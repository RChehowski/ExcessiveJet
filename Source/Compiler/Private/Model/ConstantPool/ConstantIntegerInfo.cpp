
#include "Model/ConstantPool/ConstantIntegerInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantIntegerInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantIntegerInfo {" << std::endl;
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantIntegerInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> Bytes;
    }

    void operator>>(CClassReader& Reader, CConstantIntegerInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::string CConstantIntegerInfo::ToResolvedString(const CConstantPool& ConstantPool) const
    {
        return std::to_string(GetInteger());
    }

}