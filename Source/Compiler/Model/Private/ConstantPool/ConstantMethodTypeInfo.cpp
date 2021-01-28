
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Parse
{
    std::string CConstantMethodTypeInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodTypeInfo {" << std::endl;
        oss << "     DescriptorIndex: " << DescriptorIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
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