
#include "ConstantPool/ConstantNameAndTypeInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantNameAndTypeInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantNameAndTypeInfo {" << std::endl;
        oss << "           NameIndex: " << NameIndex << std::endl;
        oss << "     DescriptorIndex: " << DescriptorIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantNameAndTypeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> NameIndex;
        Reader >> DescriptorIndex;
    }

    void operator>>(CClassReader& Reader, CConstantNameAndTypeInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}