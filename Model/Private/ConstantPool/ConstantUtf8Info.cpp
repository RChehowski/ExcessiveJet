
#include "ConstantPool/ConstantUtf8Info.h"
#include "MemoryFile.h"
#include "Platform/Memory.h"

#include <sstream>

using Util::Memory;

namespace Parse
{
    std::string CConstantUtf8Info::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantUtf8Info {" << std::endl;
        oss << "              Length: " << Length << std::endl;
        oss << "               Bytes: ";
        oss.write((const char*)Bytes, (std::streamsize)Length);
        oss << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantUtf8Info::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> Length;

        Bytes = Memory::MallocT<u1>(Length);
        Reader.ReadBytes(Bytes, (usz)Length);
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantUtf8Info& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}