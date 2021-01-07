//
// Created by ASUS on 29/12/2020.
//

#include "Platform/FileUtils.h"
#include "MemoryFile.h"

using Util::Memory;

namespace Util
{
    CMemoryReader::CMemoryReader(const SystemPath& Path) : FilePath(Path), FileName(Path.filename())
    {
        FileStream = FileUtils::ReadFile(Path);
        ASSERT(FileStream.is_open());
    }

    CMemoryReader::~CMemoryReader()
    {
        if (FileStream.is_open())
        {
            FileStream.close();
        }
    }

    void CMemoryReader::ReadBytes(void* Memory, usz Size)
    {
        FileStream.read(static_cast<char*>(Memory), Size);
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
                OriginatedOffset = (ssz)FileStream.tellg();
                break;
            }
            case EMemoryFileOrigin::End:
            {
                OriginatedOffset = (ssz)GetFileSize();
                break;
            }
            default:
            {
                OriginatedOffset = (ssz)-1;
                break;
            }
        }

        const ssz NewPosition= OriginatedOffset + Offset;
        ASSERT((NewPosition >= 0) && ((usz)NewPosition < GetFileSize()));
        FileStream.seekg(NewPosition);
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
}