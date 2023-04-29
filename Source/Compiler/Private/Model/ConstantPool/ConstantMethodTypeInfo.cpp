
#include "Model/ConstantPool/ConstantMethodTypeInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantMethodTypeInfo::ToLowLevelString() const
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

    std::string CConstantMethodTypeInfo::ToResolvedString(const CConstantPool& ConstantPool) const
    {
        const Compiler::CConstantUtf8Info& Name =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(GetDescriptorIndex());

        return Name.ToResolvedString(ConstantPool);
    }

}