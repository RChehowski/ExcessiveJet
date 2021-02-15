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
    public:
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

        [[nodiscard]]
        FORCEINLINE const std::string& GetName() const
        {
            return Name;
        }

        [[nodiscard]]
        FORCEINLINE usz GetSize() const
        {
            return Size;
        }

        [[nodiscard]]
        Util::CAllocation GetData() const
        {
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

        // Should be valid until CZipFileEntry is inside Walk's scope
        Util::CAllocation& AllocationForDecompression;
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

        Util::CAllocation AllocationForDecompression;

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
                }
            }
        }

        return MZ_TRUE == mz_zip_writer_end(&ZipArchive);
    }
}
