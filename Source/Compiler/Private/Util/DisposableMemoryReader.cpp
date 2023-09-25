//
// Created by ASUS on 29/12/2020.
//

#include "Util/DisposableMemoryReader.h"
#include "Util/FileUtils.h"
#include "Util/StringUtf8.h"


namespace Util
{
    void CMemoryReader::RangeCheck(usz AddOffset) const
    {
        const ssz NewPosition = (ssz)(Position + AddOffset);

        ASSERT_MSG((NewPosition >= 0) && ((usz)NewPosition <= (usz)GetSizeInMemory()),
               "NewPosition: %llu, SizeInMemory: %llu", (u8)NewPosition, (u8)GetSizeInMemory());
    }

    CMemoryReader::CMemoryReader(const std::string& InFileName, const CByteOrder& InByteOrder)
        : FileName(InFileName)
        , ByteOrder(InByteOrder)
    {
        bool bFileOpened;
        Allocation = CFileUtils::ReadFile(FileName, bFileOpened);
    }

    CMemoryReader::CMemoryReader(CAllocation&& InAllocation, const CByteOrder& InByteOrder)
        : Allocation(std::move(InAllocation))
        , ByteOrder(InByteOrder)
    {
    }


    CMemoryReader::~CMemoryReader() = default;

    const void* CMemoryReader::ReadBytes(void* Memory, usz Size)
    {
        RangeCheck(Size);

        const u1* const Ptr = Allocation.Get<const u1>() + Position;
        if (Memory)
        {
            CMemory::Memcpy(Memory, Ptr, Size);
        }

        Position += Size;

        return reinterpret_cast<const void*>(Ptr);
    }

    void CMemoryReader::Seek(ssz Offset, EMemoryFileOrigin Origin)
    {
        ssz OriginatedOffset;
        switch (Origin)
        {
            default:
            case EMemoryFileOrigin::Cur:
            {
                OriginatedOffset = CMathUtils::IntegerCast<ssz>(Position);
                break;
            }
            case EMemoryFileOrigin::Set:
            {
                OriginatedOffset = 0;
                break;
            }
            case EMemoryFileOrigin::End:
            {
                OriginatedOffset = CMathUtils::IntegerCast<ssz>(GetSizeInMemory());
                break;
            }
        }

        const ssz NewPosition= OriginatedOffset + Offset;
        ASSERT((NewPosition >= 0) && ((usz)NewPosition < GetSizeInMemory()));
        Position = NewPosition;
    }

    void operator>> (Util::CMemoryReader& Reader, u1& Instance)
    {
        Instance = Reader.Read<u1>();
    }

    void operator>> (Util::CMemoryReader& Reader, u2& Instance)
    {
        Instance = Reader.Read<u2>();
    }

    void operator>> (Util::CMemoryReader& Reader, u4& Instance)
    {
        Instance = Reader.Read<u4>();
    }

    void operator>> (Util::CMemoryReader& Reader, u8& Instance)
    {
        Instance = Reader.Read<u8>();
    }

    void operator>> (Util::CMemoryReader& Reader, Util::CStringUtf8& StringUtf8)
    {
        u2 RawLength;
        Reader >> RawLength;

        const usz Length = static_cast<usz>(RawLength);

        const void* const Content = Reader.ReadBytes(nullptr, Length);
        Util::CStringUtf8 DeserializedStringUtf8(reinterpret_cast<const u1*>(Content), Length);

        StringUtf8 = std::move(DeserializedStringUtf8);
    }
}