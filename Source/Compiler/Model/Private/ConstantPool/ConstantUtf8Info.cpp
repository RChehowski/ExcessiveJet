
#include "ConstantPool/ConstantUtf8Info.h"
#include "ClassReader.h"
#include "Platform/Memory.h"

#include <sstream>

using Util::Memory;

namespace Parse
{
    std::string CConstantUtf8Info::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantUtf8Info {" << std::endl;
        oss << "          CStringUtf8: " << (std::string)StringUtf8 << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantUtf8Info::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> StringUtf8;
    }

    void operator>>(CClassReader& Reader, CConstantUtf8Info& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}