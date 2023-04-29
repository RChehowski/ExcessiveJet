
#include "Model/ConstantPool/ConstantDoubleInfo.h"
#include "Model/ClassReader.h"

#include <sstream>

namespace Compiler
{
    std::string CConstantDoubleInfo::ToLowLevelString() const
    {
        std::ostringstream oss;
        oss << "ConstantDoubleInfo {" << std::endl;
        oss << "               Value: " << Value << std::endl;
        oss << "}" << std::endl;
        return oss.str();
    }

    void CConstantDoubleInfo::DeserializeFrom(CClassReader& Reader)
    {
        u4 HighBytes;
        Reader >> HighBytes;

        u4 LowBytes;
        Reader >> LowBytes;

        constexpr u8 HiBytesMask = 0xFFFFFFFF00000000ULL;
        constexpr u8 LoBytesMask = 0x00000000FFFFFFFFULL;

        // Glue both halves together
        const u8 AsUnsigned = ((static_cast<u8>(HighBytes) << 32) & HiBytesMask) | (static_cast<u8>(LowBytes) & LoBytesMask);

        // Finally reinterpret bits (not static_cast the value!) to a double
        Value = *reinterpret_cast<const double*>(&AsUnsigned);
    }

    std::string CConstantDoubleInfo::ToResolvedString(const CConstantPool &ConstantPool) const
    {
        return std::to_string(GetDouble());
    }

}