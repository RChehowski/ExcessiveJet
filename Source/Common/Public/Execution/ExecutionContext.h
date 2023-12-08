#pragma once

#include <Util/Allocation.h>
#include "Execution/ThreadStack.h"
#include "Execution/LocalVariables.h"

#include <variant>

namespace VM
{
    enum class EFastException : u1
    {
        // java.lang.ArithmeticException("/ by zero");
        ArithmeticException_DivisionByZero,

        // java.lang.NullPointerException("null");
        NullPointerException,
    };

    struct CExecutionContext
    {
        CExecutionContext(CThreadStack& InThreadStack, CLocalVariables& InLocalVariables)
            : ThreadStack(InThreadStack)
            , LocalVariables(InLocalVariables)
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

        template<typename T>
        [[nodiscard]] FORCEINLINE T GetConditionResult() const
        {
            static_assert(std::is_same_v<T, bool> || std::is_same_v<T, u2>);
            return static_cast<T>(ConditionResult);
        }

        template<typename T>
        FORCEINLINE void SetConditionResult(const T InConditionResult)
        {
            static_assert(std::is_same_v<T, bool> || std::is_same_v<T, u2>);
            ConditionResult = static_cast<u2>(InConditionResult);
        }

        /**
         * Quickly throw pre-defined exception
         *
         * @param FastException Exception type
         */
        void ThrowException(const EFastException FastException)
        {

        }

    private:
        CThreadStack& ThreadStack;
        CLocalVariables& LocalVariables;

        // May be either a boolean for if() or a unsigned short (u2) offset for switch()
        u2 ConditionResult = static_cast<u2>(0);
    };
}