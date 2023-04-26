//
// Created by rcheh on 6/28/2022.
//

#pragma once

#include "Util/Types.h"
#include "Oop.h"

#include <atomic>

namespace JavaWorld
{
    enum class EMarkWordFlags : u4
    {
        None            = 0,

        /** Marked by the GC. Meaning, it's certainly not garbage */
        Marked          = 1 << 0,

        /** Being visited by the GC wavefront, added to mitigate circular reference detection */
        BeingVisited    = 1 << 1
    };

    /** Extended by java.lang.Object this is hard-coded by the AOT compiler rules */
    class CObjectBase
    {
    public:
        [[nodiscard]] FORCEINLINE oop GetClassHandle() const
        {
            return Class;
        }

    private:
        EMarkWordFlags MarkWordFlags = EMarkWordFlags::None;
        oop Class;
        s4 IdentityHashCode;
    };

    /**
     * Allocate a java object, calling c++ constructors.
     * Does NOT call java constructor (invokespecial init)
     */
    template <typename T>
    FORCEINLINE T* NewObject(const oop ClassHandle, const EMarkWordFlags InMarkWordFlags)
    {
        static_assert(std::is_base_of_v<CObjectBase, T>);

        T* Object = new T {};
        static_cast<CObjectBase*>(Object)->Class = ClassHandle;

        return Object;
    }
}