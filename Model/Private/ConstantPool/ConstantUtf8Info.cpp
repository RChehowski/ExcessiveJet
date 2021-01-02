
#include "ConstantPool/ConstantUtf8Info.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantUtf8Info::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantUtf8Info {" << std::endl;
        oss << "              Length: " << Length << std::endl;
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantUtf8Info& Instance)
    {
        Reader >> Instance.Length;
        Reader >> Instance.Bytes;
    }
}