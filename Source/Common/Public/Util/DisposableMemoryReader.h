//
// Created by rcheh on 4/16/2023.
//

#pragma once

#include "Util/Types.h"

namespace Util
{
    /** Disposable memory reader. Does not do any checks. */
    class CDisposableMemoryReader
    {
    public:
        CDisposableMemoryReader() = delete;
        ~CDisposableMemoryReader() = default;

        CDisposableMemoryReader(const CDisposableMemoryReader&) = delete;
        CDisposableMemoryReader(CDisposableMemoryReader&&) = delete;

        //CMemoryReader& operator= CMemoryReader(const CMemoryReader&) = delete;
        //CMemoryReader& operator= CMemoryReader(CMemoryReader&&) = delete;

        template<typename T>
        explicit FORCEINLINE CDisposableMemoryReader(const T* InMemory) : Memory(reinterpret_cast<const u1*>(InMemory)) {}

        template<typename T>
        T ReadNextCopy()
        {
            const T* ValuePtr = reinterpret_cast<const T*>(Memory);
            Memory += sizeof(T);
            return *ValuePtr;
        }

        template<typename T>
        const T& ReadNextRef()
        {
            const T* ValuePtr = reinterpret_cast<const T*>(Memory);
            Memory += sizeof(T);
            return *ValuePtr;
        }

    private:
        const u1* Memory;
    };
}
