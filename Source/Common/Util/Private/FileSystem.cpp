//
// Created by ASUS on 15/02/2021.
//

#include "FileSystem.h"
#include "ExcessiveAssert.h"

#include <optional>
#include <filesystem>

#include "FileUtils.h"

#include "minizcpp/zip_file.hpp"


namespace stdfs = std::filesystem;

namespace Util
{
    constexpr const usz ZIP_ALLOCATION_FOR_DECOMPRESSION_SIZE = 64 * 1024;

#pragma region Normal File Entry
    class CNormalFileEntry : public CFileEntry
    {
        friend bool WalkDir(const std::string& FilePath, const std::function<void(const CFileEntry&)>& Consumer);

        explicit CNormalFileEntry(std::string InName) : Name(std::move(InName))
        {
        }

    public:
        [[nodiscard]]
        const std::string& GetName() const override
        {
            return Name;
        }

        [[nodiscard]]
        usz GetSize() const override
        {
            if (!OptionalSize.has_value())
                OptionalSize = static_cast<usz>(stdfs::file_size(Name));

            return OptionalSize.value();
        }

        [[nodiscard]]
        Util::CAllocation GetData() const override
        {
            usz LocalSize = 0;
            Util::CAllocation Allocation = CFileUtils::ReadFile(Name, &LocalSize);

            if (!OptionalSize.has_value())
                OptionalSize = LocalSize;

            return std::move(Allocation);
        }

        [[nodiscard]]
        bool IsDirectory() const override
        {
            if (!OptionalIsDirectory.has_value())
                OptionalIsDirectory = stdfs::is_directory(Name);

            return OptionalIsDirectory.value();
        }

    private:
        std::string Name;

        mutable std::optional<usz> OptionalSize = {};
        mutable std::optional<usz> OptionalIsDirectory = {};
    };

    bool WalkDir(const std::string& FilePath, const std::function<void(const CFileEntry&)>& Consumer)
    {
        for (const stdfs::directory_entry& DirectoryEntry: stdfs::recursive_directory_iterator(FilePath))
        {
            std::string NormalizedStringPath = DirectoryEntry.path().generic_string();

            Consumer(CNormalFileEntry(NormalizedStringPath));
        }

        return true;
    }
#pragma endregion

#pragma region Zip File Entry
    class CZipFileEntry : public CFileEntry
    {
        friend bool WalkZip(const std::string&, const std::function<void(const CFileEntry&)>&);

        CZipFileEntry(
            std::string InName,
            bool bInDirectory,
            usz InSize,
            mz_zip_archive &InZipArchive,
            mz_uint InZipFileIndex,
            Util::CAllocation &InAllocationForDecompression
        )
            : Name(std::move(InName))
            , bDirectory(bInDirectory)
            , Size(InSize)
            , ZipArchive(InZipArchive)
            , ZipFileIndex(InZipFileIndex)
            , AllocationForDecompression(InAllocationForDecompression)
        {
        }

    public:
        CZipFileEntry() = delete;

        CZipFileEntry(const CZipFileEntry&) = delete;
        CZipFileEntry(CZipFileEntry&&) = delete;

        CZipFileEntry& operator=(const CZipFileEntry&) = delete;
        CZipFileEntry&& operator=(CZipFileEntry&&) = delete;

        [[nodiscard]]
        const std::string& GetName() const override
        {
            return Name;
        }

        [[nodiscard]]
        usz GetSize() const override
        {
            return Size;
        }

        [[nodiscard]]
        Util::CAllocation GetData() const override
        {
            Util::CAllocation Allocation(Size);

            if (!AllocationForDecompression.IsPresent())
            {
                AllocationForDecompression.Allocate(ZIP_ALLOCATION_FOR_DECOMPRESSION_SIZE);
            }

            if (MZ_TRUE == mz_zip_reader_extract_to_mem_no_alloc(
                &ZipArchive,
                ZipFileIndex,
                (void*)Allocation, Allocation.GetSize(),
                0, // flags
                (void*)AllocationForDecompression, AllocationForDecompression.GetSize()
            ))
            {
                return Allocation;
            }

            return Util::CAllocation::EmptyAllocation();
        }

        [[nodiscard]]
        bool IsDirectory() const override
        {
            return bDirectory;
        }

    private:
        std::string Name;
        bool bDirectory;
        usz Size;

        mz_zip_archive& ZipArchive;
        mz_uint ZipFileIndex;

        // Should be safe until CZipFileEntry is within Walk's scope
        Util::CAllocation& AllocationForDecompression;
    };

    bool WalkZip(const std::string& FilePath, const std::function<void(const CFileEntry&)>& Consumer)
    {
        mz_zip_archive ZipArchive;
        memset(&ZipArchive, 0, sizeof(ZipArchive));

        if (MZ_FALSE == mz_zip_reader_init_file(&ZipArchive, FilePath.c_str(), 0))
        {
            // Unable to open file
            return true;
        }

        const mz_uint ZipReaderNumFiles = mz_zip_reader_get_num_files(&ZipArchive);

        mz_zip_archive_file_stat ZipArchiveFileStat;

        Util::CAllocation AllocationForDecompression; // don't allocate anything now

        for (mz_uint ZipFileIndex = 0; ZipFileIndex < ZipReaderNumFiles; ZipFileIndex++)
        {
            const bool bGotStat = MZ_TRUE == mz_zip_reader_file_stat(&ZipArchive, ZipFileIndex, &ZipArchiveFileStat);
            ASSERT(bGotStat);

            // Retrieved info
            const bool bDirectory = mz_zip_reader_is_file_a_directory(&ZipArchive, ZipFileIndex);

            CZipFileEntry ZipFileEntry(
                    ZipArchiveFileStat.m_filename,
                    bDirectory,
                    ZipArchiveFileStat.m_uncomp_size,
                    ZipArchive,
                    ZipFileIndex,
                    AllocationForDecompression
            );

            Consumer(ZipFileEntry);
        }

        return MZ_TRUE == mz_zip_writer_end(&ZipArchive);
    }
#pragma endregion


    bool CFileSystem::Walk(const std::string& Path, const std::function<void(const CFileEntry&)>& Consumer)
    {
        if (stdfs::is_directory(Path))
        {
            return WalkDir(Path, Consumer);
        }
        else
        {
            return WalkZip(Path, Consumer);
        }
    }
}