//
// Created by ASUS on 10/01/2021.
//

#pragma once

#include "Types.h"
#include "Assert.h"
#include "ByteOrder.h"
#include "MathUtils.h"

#include <string>

namespace Util
{
    class CStringUtf8;

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
        void RangeCheck(usz AddOffset) const;

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

        const void* ReadBytes(void* Memory, usz Size);

        template<typename T>
        FORCEINLINE T Read()
        {
            static_assert(
                    std::is_same_v<T, u1> ||
                    std::is_same_v<T, u2> ||
                    std::is_same_v<T, u4> ||
                    std::is_same_v<T, u8>, "Only u1, u2, u4 and u8 are supported");

            T ReadValue;
            ReadBytes((void*)&ReadValue, sizeof(T));

            if (!ByteOrder->IsNative())
            {
                CMathUtils::ToggleEndian(&ReadValue);
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
        friend void operator>> (Util::CMemoryReader& Reader, Util::CStringUtf8& StringUtf8);

    private:
        std::wstring FileName;

        usz FileSize = (usz)0;
        uint8_t* FileBytes = nullptr;

        usz Position = (usz)0;

        const CByteOrder* ByteOrder = CByteOrders::NativeEndian();
    };
}