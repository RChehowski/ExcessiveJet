
#include "ConstantPool/ConstantMethodHandleInfo.h"
#include "ClassReader.h"

#include <sstream>

namespace Compiler
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

    void CConstantMethodHandleInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ReferenceKind;
        Reader >> ReferenceIndex;
    }

    void operator>>(CClassReader& Reader, CConstantMethodHandleInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }

}