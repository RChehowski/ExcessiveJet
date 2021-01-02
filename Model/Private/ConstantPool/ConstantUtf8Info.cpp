
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
        oss << "               Bytes: " << Bytes << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantUtf8Info& Instance)
    {
        Reader >> Instance.Length;

        Instance.Bytes = Memory::MallocT<u1>(Instance.Length);
        Reader.ReadBytes((void*)Instance.Bytes, (usz)Instance.Length);
    }
}