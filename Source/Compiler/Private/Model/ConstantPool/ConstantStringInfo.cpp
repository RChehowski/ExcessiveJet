
#include "Model/ConstantPool/ConstantStringInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantStringInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantStringInfo {" << std::endl;
        oss << "         StringIndex: " << StringIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantStringInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> StringIndex;
    }

    void operator>>(CClassReader& Reader, CConstantStringInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::string CConstantStringInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        const Compiler::CConstantUtf8Info& ConstantUtf8Info =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(GetStringIndex());

        return '\"' + ConstantUtf8Info.ToResolvedString(ConstantPool) + '\"';
    }

}