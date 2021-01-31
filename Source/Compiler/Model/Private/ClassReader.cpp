
#include "Assert.h"
#include "ClassReader.h"
#include "ConstantPool.h"

namespace Parse
{
    std::shared_ptr<CConstantPool> CClassReader::GetConstantPool() const
    {
        ASSERT(ConstantPool != nullptr);
        return ConstantPool;
    }

    void CClassReader::SetConstantPool(const std::shared_ptr<CConstantPool>& InConstantPool)
    {
        ASSERT(ConstantPool == nullptr);
        ConstantPool = InConstantPool;
    }
}
