//
// Created by Nikita Miroshnichenko on 10.02.2021.
//

#pragma once

#include <string>
#include <functional>
#include <optional>
#include <filesystem>

#include "Types.h"
#include "Allocation.h"
#include "minizcpp/zip_file.hpp"

namespace Filesystem
{
    class CZipFileHandle
    {
        friend class CZipFileSystem;

    public:
        CZipFileHandle() = delete;

        const std::filesystem::path ArchivePath;
        const std::string FileName;
        const std::size_t FileSize;

    private:
        CZipFileHandle(const std::string& InArchivePath, const std::string& InFileName, std::size_t InFileSize) : ArchivePath(InArchivePath), FileName(InFileName), FileSize(InFileSize)
        {
        }
    };

    class CZipFileEntry
    {
        friend class CZipFileSystem;

    public:
        CZipFileEntry() = delete;
        virtual ~CZipFileEntry()
        {
            delete ZipFileHandle;
        }

        FORCEINLINE const std::string& GetFileName() const
        {
            return FileName;
        }

        FORCEINLINE const Util::CAllocation& GetAllocation() const
        {
            if (!OptionalAllocation.has_value())
            {
                Util::CAllocation* Allocation = new Util::CAllocation(ZipFileHandle->FileSize);

                miniz_cpp::zip_file ZipFile = miniz_cpp::zip_file(ZipFileHandle->ArchivePath);
                std::ostream& Stream = ZipFile.open(ZipFileHandle->FileName);

                unsigned char* Data = Allocation->Get<unsigned char>();
                auto StreamBuffer = Stream.rdbuf();
                for (int i = 0; i < Allocation->GetSize(); i++)
                {
                    Data[i] = StreamBuffer->sgetc();
                }

                ZipFile.reset();
                Stream.flush();

                return *Allocation;
            }

            return *OptionalAllocation;
        }

    private:
        CZipFileEntry(const std::string& InFileName, CZipFileHandle* InZipFileHandle) : FileName(InFileName), ZipFileHandle(InZipFileHandle)
        {
        }

        std::string FileName;
        mutable std::optional<Util::CAllocation> OptionalAllocation;

        CZipFileHandle* ZipFileHandle = { nullptr };
    };

    class CZipFileSystem
    {
    public:
        FORCEINLINE void Walk(const std::string& PathToArchive, std::function<void(const CZipFileEntry&)> Consumer)
        {
            miniz_cpp::zip_file ZipFile = miniz_cpp::zip_file(PathToArchive);
            for (const auto& ZipInfo : ZipFile.infolist())
            {
                CZipFileHandle* ZipFileHandle = new CZipFileHandle(PathToArchive, ZipInfo.filename, ZipInfo.file_size);
                Consumer(CZipFileEntry(ZipInfo.filename, ZipFileHandle));
            }

            ZipFile.reset();
        }
    };
}
