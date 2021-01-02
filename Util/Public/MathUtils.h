//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    class CMathUtils
    {
    public:
        template<typename T>
        FORCEINLINE static T Max(T A, T B)
        {
            return (A > B) ? A : B;
        }

        template<typename T>
        FORCEINLINE static T Min(T A, T B)
        {
            return (A > B) ? A : B;
        }

        template<typename T>
        FORCEINLINE static T Clamp(T InValue, T InMin, T InMax)
        {
            return Max<T>(Min<T>(InValue, InMax), InMin);
        }

        template<typename T>
        FORCEINLINE static void TwiddleBytes(u1* Bytes, usz Size)
        {
        }
    };
}
