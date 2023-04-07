
#include "Model/ConstantPool/ConstantFieldRefInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantFieldRefInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantFieldRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantFieldRefInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(CClassReader& Reader, CConstantFieldRefInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::string CConstantFieldRefInfo::ToResolvedString(const CConstantPool& ConstantPool) const
    {
        const Compiler::CConstantClassInfo& ClassInfo =
                ConstantPool.GetChecked<Compiler::CConstantClassInfo>(GetClassIndex());


        const Compiler::CConstantNameAndTypeInfo& NameAndType =
                ConstantPool.GetChecked<Compiler::CConstantNameAndTypeInfo>(GetNameAndTypeIndex());

        const Compiler::CConstantUtf8Info& FieldName =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(NameAndType.GetNameIndex());

        std::ostringstream oss;
        oss << NameAndType.ToResolvedString(ConstantPool) + " from " + ClassInfo.ToResolvedString(ConstantPool);

        return oss.str();
    }

}