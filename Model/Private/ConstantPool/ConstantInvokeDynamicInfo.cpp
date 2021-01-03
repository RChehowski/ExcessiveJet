
#include "ConstantPool/ConstantInvokeDynamicInfo.h"
#include "MemoryFile.h"

#include <sstream>

namespace Parse
{
    std::string CConstantInvokeDynamicInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantInvokeDynamicInfo {" << std::endl;
        oss << "BootstrapMethodAttrIndex: " << BootstrapMethodAttrIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantInvokeDynamicInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> BootstrapMethodAttrIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(Util::CMemoryReader& Reader, CConstantInvokeDynamicInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}