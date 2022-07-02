
#include "Model/ConstantPool/ConstantFloatInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantFloatInfo::ToString() const
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

}