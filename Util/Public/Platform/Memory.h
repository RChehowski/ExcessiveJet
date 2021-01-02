//
// Created by ASUS on 30/12/2020.
//

#ifndef CPP20_MEMORY_H
#define CPP20_MEMORY_H

#include "Platform/Misc.h"

namespace Util
{
    class Memory
    {
        static void Memcpy(void* const Dst, const void* const Src, const usz NumBytes);

        static s4 Memcmp(const void* const A, const void* const B, const usz NumBytes);

    public:
        template<class T>
        static T* MallocT(usz Size, usz Alignment = 1)
        {
            return reinterpret_cast<T*>(Malloc(Size * sizeof(T), Alignment));
        }

        static void* Malloc(usz Size, usz Alignment = 1);

        static void Free(const void* Ptr);


        template<typename TDst, typename TSrc>
        static void Memcpy(TDst* const Dst, const TSrc* const Src, const usz NumBytes)
        {
            Memcpy(
                reinterpret_cast<void*>(Dst),
                reinterpret_cast<const void*>(Src),
                NumBytes
            );
        }

        template<typename TA, typename TB>
        static s4 Memcmp(const TA* const A, const TB* const B, const usz NumBytes)
        {
            return Memcmp(
                reinterpret_cast<const void*>(A),
                reinterpret_cast<const void*>(B),
                NumBytes
            );
        }
    };
}


#endif //CPP20_MEMORY_H
