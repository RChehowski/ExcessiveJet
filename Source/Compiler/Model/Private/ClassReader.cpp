
#include "Assert.h"
#include "ClassReader.h"
#include "ConstantPool.h"

namespace Parse
{
    CConstantPool* CClassReader::GetConstantPool() const
    {
        ASSERT(ConstantPool != nullptr);
        return ConstantPool;
    }

    void CClassReader::SetConstantPool(CConstantPool *const InConstantPool)
    {
        ASSERT(ConstantPool == nullptr);
        ConstantPool = InConstantPool;
    }
}
