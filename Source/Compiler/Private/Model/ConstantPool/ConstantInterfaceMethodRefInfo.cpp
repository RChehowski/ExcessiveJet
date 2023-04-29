
#include "Model/ConstantPool/ConstantInterfaceMethodRefInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantInterfaceMethodRefInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantInterfaceMethodRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantInterfaceMethodRefInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    std::string CConstantInterfaceMethodRefInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return CConstantMethodRefInfo::ToResolvedString(ConstantPool, GetClassIndex(), GetNameAndTypeIndex());
    }

}