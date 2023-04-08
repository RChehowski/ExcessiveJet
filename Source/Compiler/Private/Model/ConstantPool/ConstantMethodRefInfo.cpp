
#include "Model/ConstantPool/ConstantMethodRefInfo.h"
#include "Model/ClassReader.h"
#include "Model/Debug/DebugMisc.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantMethodRefInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantMethodRefInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(CClassReader& Reader, CConstantMethodRefInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    std::string CConstantMethodRefInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return ToResolvedString(ConstantPool, GetClassIndex(), GetNameAndTypeIndex());
    }

    std::string CConstantMethodRefInfo::ToResolvedString(const CConstantPool &ConstantPool, u2 ClassIndex, u2 NameAndTypeIndex)
    {
        const Compiler::CConstantClassInfo& ClassInfo =
                ConstantPool.GetChecked<Compiler::CConstantClassInfo>(ClassIndex);


        const Compiler::CConstantNameAndTypeInfo& NameAndType =
                ConstantPool.GetChecked<Compiler::CConstantNameAndTypeInfo>(NameAndTypeIndex);

        const Compiler::CConstantUtf8Info& MethodName =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(NameAndType.GetNameIndex());

        const Compiler::CConstantUtf8Info& MethodSignature =
                ConstantPool.GetChecked<Compiler::CConstantUtf8Info>(NameAndType.GetDescriptorIndex());


        const std::string RawSignature = (std::string)MethodSignature.GetStringUtf8();

        const std::string ReturnType = Debug::DecodeMethodReturnType(RawSignature);
        const std::string Signature = Debug::DecodeMethodArgumentTypesJoined(RawSignature);

        std::ostringstream oss;
        oss << ReturnType << ' ' << MethodName.GetStringUtf8() << '(' << Signature << ") from " << ClassInfo.ToResolvedString(ConstantPool);

        return oss.str();
    }

}