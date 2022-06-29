//
// Created by ASUS on 15/02/2021.
//

#pragma once

#include <string>
#include <functional>

#include "Util/Types.h"
#include "Allocation.h"


namespace Util
{
    class CFileEntry
    {
    protected:
        CFileEntry() = default;

    public:
        virtual ~CFileEntry() = default;

    public:
        [[nodiscard]]
        virtual const std::string &GetName() const = 0;

        [[nodiscard]]
        virtual usz GetSize() const = 0;

        [[nodiscard]]
        virtual Util::CAllocation GetData() const = 0;

        [[nodiscard]]
        virtual bool IsDirectory() const = 0;
    };

    class CFileSystem
    {
    public:
        static bool Walk(const std::string &Path, const std::function<void(const CFileEntry &)> &Consumer);
    };
}
