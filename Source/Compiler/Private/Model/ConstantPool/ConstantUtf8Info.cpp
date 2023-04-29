
#include "Model/ConstantPool/ConstantUtf8Info.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantUtf8Info::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantUtf8Info {" << std::endl;
        oss << "          StringUtf8: " << StringUtf8 << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantUtf8Info::DeserializeFrom(CClassReader& Reader)
    {
        Util::CStringUtf8 LocalStringUtf8;
        Reader >> LocalStringUtf8;

        StringUtf8 = std::move(LocalStringUtf8);
    }

    std::string CConstantUtf8Info::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return static_cast<std::string>(GetStringUtf8());
    }
}