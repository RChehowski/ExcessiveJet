//
// Created by ASUS on 30/12/2020.
//

#include "Util/Platform/Memory.h"
#include "Util/MathUtils.h"

#include "rpmalloc/rpmalloc.h"

#include <cstdlib>
#include <cstring>

namespace Util
{
    namespace Private
    {
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
        static thread_local Private::CRpMallocThreadLocalInitializer Initializer{};

        return rpaligned_alloc(Alignment, Size);
    }

    void CMemory::Free(const void *const Ptr)
    {
        rpfree(const_cast<void*>(Ptr));
    }

    void CMemory::MemZero(void* Ptr, usz Size)
    {
        memset(Ptr, 0, Size);
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

#pragma section(".CRT$XLAB", long, read)

//extern void rpmalloc_set_main_thread(void);

static void __stdcall thread_init(void *mod, unsigned long reason, void *reserved)
{
    rpmalloc_initialize();
    //rpmalloc_set_main_thread();
}

__declspec(allocate(".CRT$XLAB")) void (__stdcall *_thread_init)(void *, unsigned long, void *) = thread_init;


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
