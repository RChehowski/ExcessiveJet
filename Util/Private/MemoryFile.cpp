//
// Created by ASUS on 29/12/2020.
//

#include "Platform/Memory.h"
#include "Platform/FileUtils.h"

#include "MathUtils.h"
#include "MemoryFile.h"


using Util::Memory;

namespace Util
{
    CMemoryReader::CMemoryReader(const WideString& InFileName) : FileName(InFileName)
    {
        FileBytes = FileUtils::ReadFile(FileName, &FileSize);
    }

    CMemoryReader::~CMemoryReader()
    {
        Memory::Free((const void*)FileBytes);
    }

    void CMemoryReader::ReadBytes(void* Memory, usz Size)
    {
        RangeCheck(Size);

        Memory::Memcpy(Memory, FileBytes + Position, Size);
        Position += Size;
    }

    void CMemoryReader::Seek(ssz Offset, EMemoryFileOrigin Origin)
    {
        ssz OriginatedOffset;
        switch (Origin)
        {
            case EMemoryFileOrigin::Set:
            {
                OriginatedOffset = 0;
                break;
            }
            case EMemoryFileOrigin::Cur:
            {
                OriginatedOffset = (ssz)Position;
                break;
            }
            case EMemoryFileOrigin::End:
            {
                OriginatedOffset = (ssz)FileSize;
                break;
            }
            default:
            {
                OriginatedOffset = (ssz)-1;
                break;
            }
        }

        const ssz NewPosition= OriginatedOffset + Offset;
        ASSERT((NewPosition >= 0) && (NewPosition < FileSize));
        Position = NewPosition;
    }

    void operator>> (Util::CMemoryReader& Reader, u1& Instance)
    {

    }

    void operator>> (Util::CMemoryReader& Reader, u2& Instance)
    {

    }

    void operator>> (Util::CMemoryReader& Reader, u4& Instance)
    {

    }

    void operator>> (Util::CMemoryReader& Reader, u8& Instance)
    {

    }
}