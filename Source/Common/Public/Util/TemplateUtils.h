//
// Created by raman.chakhouski on 4/14/2023.
//

#pragma once

#include "Util/Platform/Memory.h"
#include <tuple>

namespace Util
{
    template<typename... TArgs>
    usz ConsumeToRawMemory(u1* const Memory, TArgs&&... Args)
    {
        usz Offset = 0;

        std::apply
        (
            [&Offset, Memory](const TArgs&... TupleArgs)
            {
                auto ElementConsumer = [&Offset, Memory](auto&& TupleArg)
                {
                    using TArg = std::remove_reference_t<decltype(TupleArg)>;
                    constexpr usz ElementSize = sizeof(TArg);

                    if constexpr (std::is_move_assignable_v<TArg&&>)
                    {
                        *reinterpret_cast<TArg*>(Memory + Offset) = std::forward<TArg>(TupleArg);
                    }
                    else if constexpr (std::is_pod_v<TArg>)
                    {
                        CMemory::Memcpy(Memory + Offset, &TupleArg, ElementSize);
                    }

                    Offset += ElementSize;
                };
                (ElementConsumer(TupleArgs), ...);
            },
            std::forward_as_tuple(Args...)
        );

        return Offset;
    }
}
