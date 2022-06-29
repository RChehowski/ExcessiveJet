//
// Created by rcheh on 6/28/2022.
//

#pragma once

#include "Util/Types.h"

#include <atomic>

namespace JavaWorld
{
    enum EMarkWordFlags : u1
    {
        None    = 0b00000000,
        Marked  = 0b00000001
    };

    struct CMarkWord
    {
        s4 IdentityHashCode;

        u2 MonitorIndex;
        u1 MonitorIndexPage;

        EMarkWordFlags Flags;

        FORCEINLINE CMarkWord()
        {
            IdentityHashCode = IdentityHashCodeCounter.fetch_add(1, std::memory_order_relaxed);

            MonitorIndex = static_cast<u2>(0);
            MonitorIndexPage = static_cast<u1>(0);

            Flags = EMarkWordFlags::None;
        }

    private:
        inline static std::atomic<s4> IdentityHashCodeCounter { 0 };
    };

    static_assert(sizeof(CMarkWord) == 8);

    class CObjectBase
    {
    public:
        FORCEINLINE void SetClassHandle(const u4 InClassIndex)
        {
            ClassHandle = InClassIndex;
        }

        [[nodiscard]] FORCEINLINE u4 GetClassHandle() const
        {
            return ClassHandle;
        }

    private:
        CMarkWord MarkWord {};
        u4 ClassHandle = static_cast<u4>(0);
    };

    /**
     * Allocate a java object, calling c++ constructors.
     * Does NOT call java constructor (invokespecial init)
     */
    template <typename T>
    FORCEINLINE T* NewObject(const u4 ClassHandle)
    {
        static_assert(std::is_base_of_v<CObjectBase, T>);

        T* Object = new T {};
        static_cast<CObjectBase*>(Object)->SetClassHandle(ClassHandle);

        return Object;
    }
}