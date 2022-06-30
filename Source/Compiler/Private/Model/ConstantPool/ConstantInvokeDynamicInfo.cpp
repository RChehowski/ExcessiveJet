
#include "Model/ConstantPool/ConstantInvokeDynamicInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantInvokeDynamicInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantInvokeDynamicInfo {" << std::endl;
        oss << "BootstrapMethodAttrIndex: " << BootstrapMethodAttrIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantInvokeDynamicInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> BootstrapMethodAttrIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(CClassReader& Reader, CConstantInvokeDynamicInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}