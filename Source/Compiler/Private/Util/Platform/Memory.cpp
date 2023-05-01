//
// Created by ASUS on 30/12/2020.
//

#include "Util/Platform/Memory.h"
#include "Util/MathUtils.h"

#include "rpmalloc/rpmalloc.h"

#include <cstdlib>
#include <cstring>

#if PLATFORM_WINDOWS
	#include <malloc.h>
#endif


#define WITH_RPMALLOC (0)

namespace Util
{
    namespace Private
    {
#if WITH_RPMALLOC
        struct CRpMallocThreadLocalInitializer
        {
            FORCEINLINE CRpMallocThreadLocalInitializer()
            {
                rpmalloc_thread_initialize();
            }

            FORCEINLINE ~CRpMallocThreadLocalInitializer()
            {
                rpmalloc_thread_finalize(1);
            }
        };
#endif // WITH_RPMALLOC
    }

    void CMemory::Memcpy(void* const Dst, const void* const Src, const usz NumBytes)
    {
        memcpy(Dst, Src, NumBytes);
    }

    s4 CMemory::Memcmp(const void* const A, const void* const B, const usz NumBytes)
    {
        return (s4)memcmp(A, B, NumBytes);
    }

    void* CMemory::MallocImpl(usz Size, usz Alignment)
    {
#if WITH_RPMALLOC
        static thread_local Private::CRpMallocThreadLocalInitializer Initializer{};

        return rpaligned_alloc(Alignment, Size);
#else
    #if PLATFORM_WINDOWS
        return _aligned_malloc(static_cast<size_t>(Size), static_cast<size_t>(Alignment));
    #elif PLATFORM_UNIX
        void* addr;
        posix_memalign(&addr, Alignment, Size);
        return addr;
    #else
        #error Unsupported platform
    #endif
#endif // WITH_RPMALLOC
    }

    void CMemory::Free(const void *const Ptr)
    {
#if WITH_RPMALLOC
        rpfree(const_cast<void*>(Ptr));
#else
    #if PLATFORM_WINDOWS
        // Whatever was allocated with _aligned_malloc must be freed with _aligned_free
        _aligned_free(const_cast<void*>(Ptr));
    #else
        free(const_cast<void*>(Ptr));
    #endif
#endif // WITH_RPMALLOC
    }

    void CMemory::Memset(void* const Ptr, const usz Size, const int Value)
    {
        const u1 ByteValue = static_cast<u1>(Value);

        u1* const BeginPtr = reinterpret_cast<u1*>(Ptr);
        u1* const EndPtr = BeginPtr + Size;

        u1* const BulkBeginPtr = CMathUtils::Align(BeginPtr, sizeof(u8));

        // Head
        for (u1* Cursor = BeginPtr; Cursor < BulkBeginPtr; ++Cursor)
        {
            *Cursor = ByteValue;
        }

        // Body
        // Looks like the easiest and the most readable way to make a 8 byte value from 8 identical bytes
        union
        {
            const u1 ArrayValue[8];
            const u8 BulkValue;
        } U { ByteValue, ByteValue, ByteValue, ByteValue, ByteValue, ByteValue, ByteValue, ByteValue };

        u1* const BulkEndPtr = CMathUtils::AlignDown(EndPtr, sizeof(u8));
        for
        (
            u8* Cursor = reinterpret_cast<u8*>(BulkBeginPtr), *End = reinterpret_cast<u8*>(BulkEndPtr);
            Cursor < End;
            ++Cursor
        )
        {
            *Cursor = U.BulkValue;
        }

        // Tail
        for (u1* Cursor = BulkEndPtr; Cursor < EndPtr; ++Cursor)
        {
            *Cursor = ByteValue;
        }
    }

    std::optional<CMemoryStatistics> CMemory::GetStatistics()
    {
#if ENABLE_STATISTICS
        rpmalloc_global_statistics_t RawStatistics;
        rpmalloc_global_statistics(&RawStatistics);

        CMemoryStatistics MemoryStatistics {};
        MemoryStatistics.Mapped         = static_cast<usz>(RawStatistics.mapped);
        MemoryStatistics.MappedPeak     = static_cast<usz>(RawStatistics.mapped_peak);
        MemoryStatistics.Cached         = static_cast<usz>(RawStatistics.cached);
        MemoryStatistics.HugeAlloc      = static_cast<usz>(RawStatistics.huge_alloc);
        MemoryStatistics.HugeAllocPeak  = static_cast<usz>(RawStatistics.huge_alloc_peak);
        MemoryStatistics.MappedTotal    = static_cast<usz>(RawStatistics.mapped_total);
        MemoryStatistics.UnmappedTotal  = static_cast<usz>(RawStatistics.unmapped_total);

        return { MemoryStatistics };
#endif // ENABLE_STATISTICS

        return {};
    }
}

#if 0
#pragma section(".CRT$XLAB", long, read)
static void __stdcall thread_init(void *mod, unsigned long reason, void *reserved)
{
    rpmalloc_initialize();
}
__declspec(allocate(".CRT$XLAB")) void (__stdcall *_thread_init)(void *, unsigned long, void *) = thread_init;
#endif

using Util::CMemory;

#ifdef __CRTDECL
    #define EXJ_CRTDECL __CRTDECL
#else
    #define EXJ_CRTDECL
#endif

extern void EXJ_CRTDECL operator delete(void* p) noexcept
{
    CMemory::Free(p);
}

extern void EXJ_CRTDECL operator delete[](void* p) noexcept
{
    CMemory::Free(p);
}

extern void* EXJ_CRTDECL operator new(std::size_t size) noexcept(false)
{
    return CMemory::Malloc<void>(size);
}

extern void* EXJ_CRTDECL operator new[](std::size_t size) noexcept(false)
{
    return CMemory::Malloc<void>(size);
}

extern void* EXJ_CRTDECL operator new(std::size_t size, const std::nothrow_t& tag) noexcept
{
    (void)sizeof(tag);
    return CMemory::Malloc<void>(size);
}

extern void* EXJ_CRTDECL operator new[](std::size_t size, const std::nothrow_t& tag) noexcept
{
    (void)sizeof(tag);
    return CMemory::Malloc<void>(size);
}

#if (__cplusplus >= 201402L || _MSC_VER >= 1916)
    extern void EXJ_CRTDECL operator delete(void* p, std::size_t size) noexcept
    {
        (void)sizeof(size);
        CMemory::Free(p);
    }

    extern void EXJ_CRTDECL operator delete[](void* p, std::size_t size) noexcept
    {
        (void)sizeof(size);
        CMemory::Free(p);
    }
#endif


#if (__cplusplus > 201402L || defined(__cpp_aligned_new))
    extern void EXJ_CRTDECL operator delete(void* p, std::align_val_t align) noexcept
    {
        (void)sizeof(align);
        CMemory::Free(p);
    }

    extern void EXJ_CRTDECL operator delete[](void* p, std::align_val_t align) noexcept
    {
        (void)sizeof(align);
        CMemory::Free(p);
    }

    extern void EXJ_CRTDECL operator delete(void* p, std::size_t size, std::align_val_t align) noexcept
    {
        (void)sizeof(size);
        (void)sizeof(align);
        CMemory::Free(p);
    }

    extern void EXJ_CRTDECL operator delete[](void* p, std::size_t size, std::align_val_t align) noexcept
    {
        (void)sizeof(size);
        (void)sizeof(align);
        CMemory::Free(p);
    }

    extern void* EXJ_CRTDECL operator new(std::size_t size, std::align_val_t align) noexcept(false)
    {
        return CMemory::Malloc<void>(static_cast<size_t>(align), size);
    }

    extern void* EXJ_CRTDECL operator new[](std::size_t size, std::align_val_t align) noexcept(false)
    {
        return CMemory::Malloc<void>(static_cast<size_t>(align), size);
    }

    extern void* EXJ_CRTDECL operator new(std::size_t size, std::align_val_t align, const std::nothrow_t& tag) noexcept
    {
        (void)sizeof(tag);
        return CMemory::Malloc<void>(static_cast<size_t>(align), size);
    }

    extern void* EXJ_CRTDECL operator new[](std::size_t size, std::align_val_t align, const std::nothrow_t& tag) noexcept
    {
        (void)sizeof(tag);
        return CMemory::Malloc<void>(static_cast<size_t>(align), size);
    }
#endif

#undef EXJ_CRTDECL
