
#include "Model/ConstantPool/ConstantClassInfo.h"
#include "Model/ClassReader.h"
#include "Model/Debug/DebugMisc.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantClassInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantClassInfo {" << std::endl;
        oss << "           NameIndex: " << NameIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantClassInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> NameIndex;
    }

    void operator>>(CClassReader& Reader, CConstantClassInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::string CConstantClassInfo::ToResolvedString(const CConstantPool& ConstantPool) const
    {
        const Compiler::CConstantUtf8Info& ClassName =
            ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(GetNameIndex());

        const std::string RawName = ClassName.ToResolvedString(ConstantPool);

	    return Debug::DecodeType(RawName);
    }

}