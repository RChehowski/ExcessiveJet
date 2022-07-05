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
        void LazyMallocInit()
        {
            static std::atomic_bool bInitialized = false;
            bool bInitialized_Expected = false;
            if (bInitialized.compare_exchange_strong(bInitialized_Expected, true))
            {
                rpmalloc_initialize();
            }

            static thread_local bool bThreadInitialized = false;
            if (bThreadInitialized)
            {
                rpmalloc_thread_initialize();
            }
        }
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
        Private::LazyMallocInit();

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
}


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
