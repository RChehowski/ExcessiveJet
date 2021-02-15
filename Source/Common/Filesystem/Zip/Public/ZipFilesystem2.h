//
// Created by ASUS on 15/02/2021.
//

#pragma once

#include <memory>
#include <string>
#include <functional>

#include "Types.h"
#include "Allocation.h"
#include "minizcpp/zip_file.hpp"

namespace Util
{

    class CZipFileEntry
    {
        friend bool Walk(const std::string&, const std::function<void(const CZipFileEntry&)>&);

        CZipFileEntry(
            std::string InName,
            usz InSize,
            mz_zip_archive &InZipArchive,
            mz_uint InZipFileIndex,
            Util::CAllocation &InAllocationForDecompression
        )
            : Name(std::move(InName))
            , Size(InSize)
            , ZipArchive(InZipArchive)
            , ZipFileIndex(InZipFileIndex)
            , AllocationForDecompression(InAllocationForDecompression)
        {}

        FORCEINLINE void AssertIsUsable() const
        {
            ASSERT_MSG(bUsable, "Should not be used outsize of Walk()'s lambda consumer");
        }

    public:
        CZipFileEntry() = delete;

        CZipFileEntry(const CZipFileEntry&) = delete;
        CZipFileEntry(CZipFileEntry&&) = delete;

        CZipFileEntry& operator=(const CZipFileEntry&) = delete;
        CZipFileEntry&& operator=(CZipFileEntry&&) = delete;

        [[nodiscard]]
        FORCEINLINE const std::string& GetName() const
        {
            AssertIsUsable();
            return Name;
        }

        [[nodiscard]]
        FORCEINLINE usz GetSize() const
        {
            AssertIsUsable();
            return Size;
        }

        [[nodiscard]]
        Util::CAllocation GetData() const
        {
            AssertIsUsable();

            Util::CAllocation Allocation(Size);

            if (!AllocationForDecompression.IsPresent())
            {
                AllocationForDecompression.Allocate(64 * 1024);
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

    private:
        std::string Name;
        usz Size;

        mz_zip_archive& ZipArchive;
        mz_uint ZipFileIndex;

        // Should be safe until CZipFileEntry is within Walk's scope
        Util::CAllocation& AllocationForDecompression;

        bool bUsable = true;
    };

    /**
     * Experimental
     */
    bool Walk(const std::string& FilePath, const std::function<void(const CZipFileEntry&)>& Consumer)
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
            if (MZ_TRUE == mz_zip_reader_file_stat(&ZipArchive, ZipFileIndex, &ZipArchiveFileStat))
            {
                // Retrieved info
                if (mz_zip_reader_is_file_a_directory(&ZipArchive, ZipFileIndex))
                {
                    // Directory, do nothing?
                }
                else
                {
                    CZipFileEntry ZipFileEntry(
                        ZipArchiveFileStat.m_filename,
                        ZipArchiveFileStat.m_uncomp_size,
                        ZipArchive,
                        ZipFileIndex,
                        AllocationForDecompression
                    );

                    Consumer(ZipFileEntry);

                    ZipFileEntry.bUsable = false;
                }
            }
        }

        return MZ_TRUE == mz_zip_writer_end(&ZipArchive);
    }
}
