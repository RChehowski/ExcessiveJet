//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_MEMORYFILE_H
#define CPP20_MEMORYFILE_H

#include "Types.h"
#include "Assert.h"
#include "ByteOrder.h"

#include <string>

namespace Util
{
    enum class EMemoryFileOrigin : u1
    {
        // Beginning of file
        Set,

        // Current position of the file pointer
        Cur,

        // End of file *
        End
    };

    class CMemoryReader
    {
        FORCEINLINE void RangeCheck(usz AddOffset) const
        {
            const ssz NewPosition = (ssz)(Position + AddOffset);
            ASSERT(NewPosition < FileSize);
        }

    public:
        explicit CMemoryReader(const WideString& InFileName);

        ~CMemoryReader();

        [[nodiscard]]
        FORCEINLINE bool IsValid() const
        {
            return (FileBytes != nullptr);
        }

        [[nodiscard]]
        FORCEINLINE const CByteOrder* GetByteOrder() const
        {
            return ByteOrder;
        }

        FORCEINLINE void SetByteOrder(const CByteOrder* InByteOrder)
        {
            ByteOrder = InByteOrder;
        }

        void ReadBytes(void* Memory, usz Size);

        template<typename T>
        FORCEINLINE T Read()
        {
            static_assert(
                std::is_same_v<T, u1> ||
                std::is_same_v<T, u2> ||
                std::is_same_v<T, u4> ||
                std::is_same_v<T, u8>,
            "Size of T must be 1, 2, 4, or 8 bytes");

            T ReadValue;
            ReadBytes((void*)&ReadValue, sizeof(T));

            if (!ByteOrder->IsNative())
            {
                CMathUtils::TwiddleBytes((u1*)&ReadValue, sizeof(T));
            }

            return ReadValue;
        }

        void Seek(ssz Offset, EMemoryFileOrigin Origin);

        [[nodiscard]]
        FORCEINLINE size_t Tell() const
        {
            return Position;
        }

        [[nodiscard]]
        FORCEINLINE size_t GetFileSize() const
        {
            return FileSize;
        }

        friend void operator>> (Util::CMemoryReader& Reader, u1& Instance);
        friend void operator>> (Util::CMemoryReader& Reader, u2& Instance);
        friend void operator>> (Util::CMemoryReader& Reader, u4& Instance);
        friend void operator>> (Util::CMemoryReader& Reader, u8& Instance);

    private:
        std::wstring FileName;

        usz FileSize = (usz)0;
        uint8_t* FileBytes = nullptr;

        usz Position = (usz)0;

        const CByteOrder* ByteOrder = CByteOrders::NativeEndian();
    };
}


#endif //CPP20_MEMORYFILE_H
