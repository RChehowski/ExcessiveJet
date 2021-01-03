
#include "ConstantPool/ConstantMethodHandleInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantMethodHandleInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantMethodHandleInfo {" << std::endl;
        oss << "       ReferenceKind: " << ReferenceKind << std::endl;
        oss << "      ReferenceIndex: " << ReferenceIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantMethodHandleInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> ReferenceKind;
        Reader >> ReferenceIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantMethodHandleInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}