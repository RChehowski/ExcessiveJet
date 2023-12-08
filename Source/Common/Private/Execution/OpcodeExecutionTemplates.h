#pragma once

#include "Execution/ThreadStack.h"
#include "Execution/ExecutionContext.h"

namespace Util
{
    enum class ECompareOperation : u1
    {
        // Equals (A==B)
        EQ,
        // Not equals (A!=B)
        NE,

        // Less than (A < B)
        LT,
        // Less or equals than (A <= B)
        LE,

        // Greater than (A > B)
        GT,

        // Greater or equals than (A >= B)
        GE
    };

    template<typename T>
    FORCEINLINE void GenericAdd(VM::CThreadStack& ThreadStack)
    {
        const T Value2 = ThreadStack.Pop<T>();
        const T Value1 = ThreadStack.Pop<T>();

        const T Result = Value1 + Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericSub(VM::CThreadStack& ThreadStack)
    {
        const T Value2 = ThreadStack.Pop<T>();
        const T Value1 = ThreadStack.Pop<T>();

        const T Result = Value1 - Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericMul(VM::CThreadStack& ThreadStack)
    {
        const T Value2 = ThreadStack.Pop<T>();
        const T Value1 = ThreadStack.Pop<T>();

        const T Result = Value1 * Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericDiv(VM::CExecutionContext& Context)
    {
        VM::CThreadStack& ThreadStack = Context.GetThreadStack();

        const T Value2 = ThreadStack.Pop<T>();
        const T Value1 = ThreadStack.Pop<T>();

        if constexpr (std::is_integral_v<T>)
        {
            // only integral division throws an arithmetic exception if divided by zero
            if (Value2 == static_cast<T>(0))
            {
                Context.ThrowException(VM::EFastException::ArithmeticException_DivisionByZero);
                return;
            }
        }

        const T Result = Value1 / Value2;
        ThreadStack.Push<T>(Result);
    }

#pragma region Rem
    template<typename T, typename = std::enable_if<std::is_integral_v<T>>>
    FORCEINLINE void GenericRem(VM::CExecutionContext& Context)
    {
        VM::CThreadStack& ThreadStack = Context.GetThreadStack();

        const T Value2 = ThreadStack.Pop<T>();
        const T Value1 = ThreadStack.Pop<T>();

        // Integral division throws an arithmetic exception if divided by zero
        if (Value2 == static_cast<T>(0))
        {
            Context.ThrowException(VM::EFastException::ArithmeticException_DivisionByZero);
            return;
        }

        const T Result = Value1 % Value2;
        ThreadStack.template Push<T>(Result);
    }

    template <>
    FORCEINLINE void GenericRem<float>(VM::CExecutionContext& Context)
    {
        VM::CThreadStack& ThreadStack = Context.GetThreadStack();

        // TODO: Here and later - fix arg order
        const float Value2 = ThreadStack.Pop<float>();
        const float Value1 = ThreadStack.Pop<float>();

        ThreadStack.template Push<float>(fmodf(Value1, Value2));
    }

    template <>
    FORCEINLINE void GenericRem<double>(VM::CExecutionContext& Context)
    {
        VM::CThreadStack& ThreadStack = Context.GetThreadStack();

        // TODO: Here and later - fix arg order
        const double Value2 = ThreadStack.Pop<double>();
        const double Value1 = ThreadStack.Pop<double>();

        ThreadStack.template Push<double>(fmod(Value1, Value2));
    }
#pragma endregion Rem


    template<typename T>
    FORCEINLINE void GenericNeg(VM::CThreadStack& ThreadStack)
    {
        const T Value = ThreadStack.Pop<T>();
        const T Result = -Value;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericAnd(VM::CThreadStack& ThreadStack)
    {
        static_assert(std::is_integral_v<T>);

        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 & Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericOr(VM::CThreadStack& ThreadStack)
    {
        static_assert(std::is_integral_v<T>);

        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 | Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericXor(VM::CThreadStack& ThreadStack)
    {
        static_assert(std::is_integral_v<T>);

        const T Value1 = ThreadStack.Pop<T>();
        const T Value2 = ThreadStack.Pop<T>();

        const T Result = Value1 ^ Value2;

        ThreadStack.Push<T>(Result);
    }

    template<typename T>
    FORCEINLINE void GenericLoadFromLocalVar(VM::CThreadStack& ThreadStack, const VM::CLocalVariables& LocalVariables, const u1 Index)
    {
        const T Value = LocalVariables.template Get<T>(static_cast<u2>(Index));
        ThreadStack.template Push<T>(Value);
    }

    template<typename T>
    FORCEINLINE void GenericStoreToLocalVar(VM::CThreadStack& ThreadStack, VM::CLocalVariables& LocalVariables, const u1 Index)
    {
        const T Value = ThreadStack.template Pop<T>();
        LocalVariables.template Set<T>(static_cast<u2>(Index), Value);
    }

#pragma region CastOnStack
    template<typename TFrom, typename TTo>
    FORCEINLINE void CastOnStack(VM::CThreadStack& ThreadStack);

    template<> FORCEINLINE void CastOnStack<s4, s8>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s8 Result = static_cast<s8>(Value);
        ThreadStack.Push<s8>(Result);
    }

    template<> FORCEINLINE void CastOnStack<s4, float>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const float Result = static_cast<float>(Value);
        ThreadStack.Push<float>(Result);
    }

    template<> FORCEINLINE void CastOnStack<s4, double>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const double Result = static_cast<double>(Value);
        ThreadStack.Push<double>(Result);
    }

    // Cast to a signed 1byte (java "byte")
    template<> FORCEINLINE void CastOnStack<s4, s1>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s4 Result = CMathUtils::Clamp
                (
                        Value,
                        static_cast<s4>(std::numeric_limits<s1>::min()),
                        static_cast<s4>(std::numeric_limits<s1>::max())
                );
        ThreadStack.Push<s4>(Result);
    }

    // Cast to an unsigned 2char (java "char")
    template<> FORCEINLINE void CastOnStack<s4, u2>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s4 Result = CMathUtils::Clamp
                (
                        Value,
                        static_cast<s4>(std::numeric_limits<u2>::min()),
                        static_cast<s4>(std::numeric_limits<u2>::max())
                );
        ThreadStack.Push<s4>(Result);
    }

    // Cast to a signed 2short (java "short")
    template<> FORCEINLINE void CastOnStack<s4, s2>(VM::CThreadStack& ThreadStack)
    {
        const s4 Value = ThreadStack.Pop<s4>();
        const s4 Result = CMathUtils::Clamp
                (
                        Value,
                        static_cast<s4>(std::numeric_limits<s2>::min()),
                        static_cast<s4>(std::numeric_limits<s2>::max())
                );
        ThreadStack.Push<s4>(Result);
    }

    template<> FORCEINLINE void CastOnStack<s8, s4>(VM::CThreadStack& ThreadStack)
    {
        const s8 Value = ThreadStack.Pop<s8>();
        ThreadStack.Push<s4>(static_cast<s4>(Value));
    }

    template<> FORCEINLINE void CastOnStack<s8, float>(VM::CThreadStack& ThreadStack)
    {
        const s8 Value = ThreadStack.Pop<s8>();
        ThreadStack.Push<float>(static_cast<float>(Value));
    }

    template<> FORCEINLINE void CastOnStack<s8, double>(VM::CThreadStack& ThreadStack)
    {
        const s8 Value = ThreadStack.Pop<s8>();
        ThreadStack.Push<double>(static_cast<double >(Value));
    }

    template<> FORCEINLINE void CastOnStack<float, s4>(VM::CThreadStack& ThreadStack)
    {
        const float Value = ThreadStack.Pop<float>();
        ThreadStack.Push<s4>(static_cast<s4>(Value));
    }

    template<> FORCEINLINE void CastOnStack<float, s8>(VM::CThreadStack& ThreadStack)
    {
        const float Value = ThreadStack.Pop<float>();
        ThreadStack.Push<s8>(static_cast<s8>(Value));
    }

    template<> FORCEINLINE void CastOnStack<float, double>(VM::CThreadStack& ThreadStack)
    {
        const float Value = ThreadStack.Pop<float>();
        ThreadStack.Push<double>(static_cast<double>(Value));
    }

    template<> FORCEINLINE void CastOnStack<double, s4>(VM::CThreadStack& ThreadStack)
    {
        const double Value = ThreadStack.Pop<double>();
        ThreadStack.Push<s4>(static_cast<s4>(Value));
    }

    template<> FORCEINLINE void CastOnStack<double, s8>(VM::CThreadStack& ThreadStack)
    {
        const double Value = ThreadStack.Pop<double>();
        ThreadStack.Push<s8>(static_cast<s8>(Value));
    }

    template<> FORCEINLINE void CastOnStack<double, float>(VM::CThreadStack& ThreadStack)
    {
        const double Value = ThreadStack.Pop<double>();
        ThreadStack.Push<float>(static_cast<float>(Value));
    }
#pragma endregion CastOnStack

    template <typename T, ECompareOperation CompareOperation>
    FORCEINLINE bool GenericCompareImpl(const T Value1, const T Value2)
    {
        static_assert(std::is_same_v<T, s4> || std::is_same_v<T, oop>, "Only signed ints and oops can be compared using this method");

        // There is no constexpr switch yet, partial specialization is not allowed either
        if constexpr (CompareOperation == ECompareOperation::EQ)
        {
            return Value1 == Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::NE)
        {
            return Value1 != Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::LT)
        {
            static_assert(!TIsOop<T>, "< is not supported for oops");
            return Value1 < Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::LE)
        {
            static_assert(!TIsOop<T>, "<= is not supported for oops");
            return Value1 <= Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::GT)
        {
            static_assert(!TIsOop<T>, "> is not supported for oops");
            return Value1 > Value2;
        }
        else if constexpr (CompareOperation == ECompareOperation::GE)
        {
            static_assert(!TIsOop<T>, ">= is not supported for oops");
            return Value1 >= Value2;
        }
        else
        {
            // can't use 'false' -- expression has to depend on a template parameter
            static_assert(!sizeof(T*), "CompareOperation is not supported");
            return false;
        }
    }

    template <ECompareOperation CompareOperation>
    FORCEINLINE bool GenericCompareIntZero(VM::CThreadStack& ThreadStack)
    {
        const s4 Value1 = ThreadStack.template Pop<s4>();
        return GenericCompareImpl<s4, CompareOperation>(Value1, static_cast<s4>(0));
    }

    template <typename T, ECompareOperation CompareOperation>
    FORCEINLINE bool GenericCompare2(VM::CThreadStack& ThreadStack)
    {
        const T Value1 = ThreadStack.template Pop<T>();
        const T Value2 = ThreadStack.template Pop<T>();

        return GenericCompareImpl<T, CompareOperation>(Value1, Value2);
    }

    FORCEINLINE s4 LookupSwitch(s4 Key, CDisposableMemoryReader&& Reader)
    {
        // There's no padding here now
        const s4 DefaultOffset = Reader.ReadNextCopy<s4>();
        const s4 NumPairs = Reader.ReadNextCopy<s4>();

        struct FMatchAndOffset
        {
            const s4 Match;
            const s4 Offset;
        };

        const FMatchAndOffset* const MatchesAndOffsets = Reader.GetMemory<FMatchAndOffset>();

        // TODO: Implement binary search
        for (u4 Index = 0; Index < NumPairs; ++Index)
        {
            const FMatchAndOffset& MatchAndOffset = MatchesAndOffsets[Index];

            if (Key == MatchAndOffset.Match)
            {
                return MatchAndOffset.Offset;
            }
        }

        return DefaultOffset;
    }
}
