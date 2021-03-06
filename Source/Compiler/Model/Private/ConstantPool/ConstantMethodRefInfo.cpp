
#include "ConstantPool/ConstantMethodRefInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantMethodRefInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
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

}