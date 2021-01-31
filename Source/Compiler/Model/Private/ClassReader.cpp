
#include "Assert.h"
#include "ByteOrder.h"
#include "ClassReader.h"
#include "ConstantPool.h"

using Util::CByteOrders;

namespace Parse
{
    CClassReader::CClassReader(const Util::WideString& InFileName) : Super (InFileName)
    {
        SetByteOrder(CByteOrders::GetBigEndian());
    }

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
