//
// Created by rcheh on 4/11/2023.
//

#include "Util/ZipFilesystem.h"
#include "minizcpp/zip_file.hpp"


namespace Filesystem
{
    Util::CAllocation CZipFileEntry::GetAllocation() const
    {
        Util::CAllocation Allocation(ZipFileHandle->FileSize);

        miniz_cpp::zip_file &ZipFile = ZipFileHandle->GetZipFile();
        std::ostream &Stream = ZipFile.open(ZipFileHandle->FileName);

        u1 *Data = Allocation.Get<u1>();

        std::streambuf *StreamBuffer = Stream.rdbuf();
        for (usz i = 0; i < Allocation.GetSize(); i++)
        {
            Data[i] = StreamBuffer->sbumpc();
        }

        Stream.flush();

        return Allocation;
    }

    void Filesystem::CZipFileSystem::Walk(const std::string &PathToArchive, std::function<void(const CZipFileEntry &)> Consumer)
    {
        miniz_cpp::zip_file ZipFile(PathToArchive);
        for (const auto& ZipInfo : ZipFile.infolist())
        {
            CZipFileHandle* const ZipFileHandle = new CZipFileHandle(PathToArchive, ZipInfo.filename, ZipInfo.file_size, ZipFile);
            Consumer(CZipFileEntry(ZipInfo.filename, ZipFileHandle));
        }
    }
}