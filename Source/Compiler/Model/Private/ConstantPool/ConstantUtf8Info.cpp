
#include "ConstantPool/ConstantUtf8Info.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantUtf8Info::ToString() const
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

    void operator>>(CClassReader& Reader, CConstantUtf8Info& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

    void operator<<(std::ostream& Os, const CConstantUtf8Info& Instance)
    {

    }
}