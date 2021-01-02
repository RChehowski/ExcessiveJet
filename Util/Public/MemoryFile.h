//
// Created by ASUS on 29/12/2020.
//

#ifndef CPP20_MEMORYFILE_H
#define CPP20_MEMORYFILE_H

#include <string>

#include "Types.h"
#include "Assert.h"

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

    class CByteOrder
    {
        friend class CMemoryFileEndian;

    public:
        constexpr explicit CByteOrder(const char* InName) : Name(InName)
        {
        }

        constexpr bool IsNative() const;

    private:
        const char* Name;
    };

    class CByteOrders
    {
    private:
        static constexpr const CByteOrder _BigEndian = CByteOrder("Big Endian");
        static constexpr const CByteOrder _LittleEndian = CByteOrder("Little Endian");

    public:
        static constexpr const CByteOrder* BigEndian()
        {
            return &_BigEndian;
        }

        static constexpr const CByteOrder* LittleEndian()
        {
            return &_LittleEndian;
        }

        static constexpr const CByteOrder* NativeEndian()
        {
            return IsLittleEndian() ? LittleEndian() : BigEndian();
        }
    };

    constexpr bool CByteOrder::IsNative() const
    {
        return this == CByteOrders::NativeEndian();
    }



    class CMemoryFile
    {
        FORCEINLINE void RangeCheck(usz AddOffset) const
        {
            const ssz NewPosition= Position + AddOffset;
            ASSERT(NewPosition < FileSize);
        }

    public:
        explicit CMemoryFile(const WideString& InFileName);

        ~CMemoryFile();

        [[nodiscard]]
        FORCEINLINE bool IsValid() const
        {
            return (FileBytes != nullptr);
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

            const bool bEndianChangeRequired = true;

            //
            if constexpr (sizeof(T) == 1)
            {
                // No conversion required for just one byte
                return ReadValue;
            }
            else if constexpr (sizeof(T) == 2)
            {
                if (ByteOrder->IsNative())
                {
                    union {
                        u2 Value;
                        u1 Bytes[sizeof(Value)];
                    } Converter{};

                    // Get bytes
                    Converter.Value = *((u2*)&ReadValue);

                    return (T)Converter.Value;
                }
                else
                {
                    return ReadValue;
                }
            }
            else if constexpr (sizeof(T) == 4)
            {
                union
                {
                    u4 Value;
                    u1 Bytes[sizeof(Value)];
                } Converter {};
            }
            else if constexpr (sizeof(T) == 8)
            {
                union
                {
                    u4 Value;
                    u1 Bytes[sizeof(Value)];
                } Converter {};
            }
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

    private:
        std::wstring FileName;

        usz Position = (usz)0;
        usz FileSize = (usz)0;

        const CByteOrder* ByteOrder = CByteOrders::NativeEndian();

        uint8_t* FileBytes = nullptr;
    };
}


#endif //CPP20_MEMORYFILE_H
