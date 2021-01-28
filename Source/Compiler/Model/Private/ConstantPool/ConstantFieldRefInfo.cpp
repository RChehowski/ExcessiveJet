
#include "ConstantPool/ConstantFieldRefInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Parse
{
    std::string CConstantFieldRefInfo::ToString() const
    {
        std::ostringstream oss;
        oss << "ConstantFieldRefInfo {" << std::endl;
        oss << "          ClassIndex: " << ClassIndex << std::endl;
        oss << "    NameAndTypeIndex: " << NameAndTypeIndex << std::endl;
        oss << "}" << std::endl;
        return std::move(oss.str());
    }

    void CConstantFieldRefInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> NameAndTypeIndex;
    }

    void operator>>(CClassReader& Reader, CConstantFieldRefInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}