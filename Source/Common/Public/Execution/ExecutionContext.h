#pragma once

#include <Util/Allocation.h>
#include "Execution/ThreadStack.h"
#include "Execution/LocalVariables.h"

namespace VM
{
    struct CExecutionContext
    {
        CExecutionContext(CThreadStack& InThreadStack, CLocalVariables& InLocalVariables, Util::CAllocation& InConstantParameters)
            : ThreadStack(InThreadStack)
            , LocalVariables(InLocalVariables)
            , ConstantParameters(InConstantParameters)
        {
        }

        [[nodiscard]] FORCEINLINE CThreadStack& GetThreadStack() const
        {
            return ThreadStack;
        }

        [[nodiscard]] FORCEINLINE CLocalVariables& GetLocalVariables() const
        {
            return LocalVariables;
        }

        [[nodiscard]] FORCEINLINE Util::CAllocation& GetConstantParameters() const
        {
            return ConstantParameters;
        }

    private:
        CThreadStack& ThreadStack;
        CLocalVariables& LocalVariables;
        Util::CAllocation& ConstantParameters;
    };
}