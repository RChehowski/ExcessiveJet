
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
        oss << "          StringUtf8: " << (std::string)StringUtf8 << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantUtf8Info::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        u2 Length = (u2)0;
        Reader >> Length;

        u1* Bytes = Memory::MallocT<u1>(Length);
        Reader.ReadBytes(Bytes, (usz)Length);

        StringUtf8 = Util::StringUtf8(Bytes, (usz)Length);

        // TODO: Optimize me
        Memory::Free(Bytes);
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantUtf8Info& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}