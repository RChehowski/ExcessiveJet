//
// Created by Nikita Miroshnichenko on 10.02.2021.
//

#pragma once

#include <memory>
#include <string>
#include <functional>
#include <optional>
#include <filesystem>
#include <utility>

#include "Util/Types.h"
#include "Util/Allocation.h"


namespace miniz_cpp
{
    class zip_file;
}

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

        FORCEINLINE miniz_cpp::zip_file& GetZipFile()
        {
            return ZipFilePtr;
        }

    private:
        miniz_cpp::zip_file& ZipFilePtr;

    private:
        CZipFileHandle(const std::string& InArchivePath, std::string InFileName, std::size_t InFileSize, miniz_cpp::zip_file& InZipFilePtr)
            : ArchivePath(InArchivePath)
            , FileName(std::move(InFileName))
            , FileSize(InFileSize)
            , ZipFilePtr(InZipFilePtr)
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

        Util::CAllocation GetAllocation() const;

    private:
        CZipFileEntry(const std::string& InFileName, CZipFileHandle* InZipFileHandle) : FileName(InFileName), ZipFileHandle(InZipFileHandle)
        {
        }

        std::string FileName;
        CZipFileHandle* ZipFileHandle = { nullptr };
    };

    class CZipFileSystem
    {
    public:
        static void Walk(const std::string& PathToArchive, std::function<void(const CZipFileEntry&)> Consumer);
    };
}
