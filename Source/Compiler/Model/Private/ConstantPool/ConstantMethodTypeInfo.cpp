
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantMethodTypeInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodTypeInfo {" << std::endl;
        oss << "     DescriptorIndex: " << DescriptorIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantMethodTypeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> DescriptorIndex;
    }

    void operator>>(CClassReader& Reader, CConstantMethodTypeInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}