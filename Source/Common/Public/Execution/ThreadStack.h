//
// Created by ASUS on 27/02/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"
#include "Util/Platform/Memory.h"
#include "Util/ExcessiveAssert.h"

#define DEBUG_THREAD_STACK 1
#if DEBUG_THREAD_STACK
    #define DEBUG_THREAD_STACK_CODE(Code) Code
/**
 * Must fit in 2 bits 0b00 - 0b11
 */
enum class EThreadStackValidationMarker : u1
{
    U1 = 0, // 8  bit
    U2 = 1, // 16 bit
    U4 = 2, // 32 bit
    U8 = 3, // 64 bit

    // Must be the last one
    Count
};

/**
 * 2 bit per entry
 */
class CThreadStackValidator
{
private:
    void Push(EThreadStackValidationMarker ThreadStackValidationMarker)
    {
        const usz IndexDiv = Pos / (usz) EThreadStackValidationMarker::Count;
        const usz IndexMod = Pos % (usz) EThreadStackValidationMarker::Count;

        const usz Shift = IndexMod * 2;

        const u1 PosMask = 3 /* 0000 0011 */ << Shift;
        const u1 NegMask = ~PosMask;

        const u1 NextValue = ((u1) ThreadStackValidationMarker << Shift) & PosMask;
        const u1 PrevValue = Array[IndexDiv] & NegMask;

        Array[IndexDiv] = NextValue | PrevValue;

        ++Pos;
    }

    EThreadStackValidationMarker Pop()
    {
        --Pos;

        const usz IndexDiv = Pos / (usz) EThreadStackValidationMarker::Count;
        const usz IndexMod = Pos % (usz) EThreadStackValidationMarker::Count;

        const usz Shift = IndexMod * 2;

        return (EThreadStackValidationMarker) ((Array[IndexDiv] >> Shift) & 3);
    }

public:

private:
    u1 *Array = nullptr;
    usz Pos = 0;
};

static_assert((usz) EThreadStackValidationMarker::Count == (usz) 4);

namespace /* anonymous */
{
#define GENERATE_CONV(SIZE)\
        template <class T> union Conv##SIZE\
        {\
        private:\
            static_assert(sizeof(T) <= (usz)(SIZE), "Size of T is too big, use another PushX()");\
            T   Value;\
            u##SIZE  ValueU##SIZE;\
        public:\
            FORCEINLINE explicit Conv##SIZE(T InValue)    : Value(InValue) {}\
            FORCEINLINE explicit Conv##SIZE(u##SIZE InValueU##SIZE) : ValueU##SIZE(InValueU##SIZE) {}\
            \
            FORCEINLINE explicit operator u##SIZE() const { return ValueU##SIZE; }\
            FORCEINLINE explicit operator T()  const { return Value;   }\
        }

}

GENERATE_CONV(1);
GENERATE_CONV(2);
GENERATE_CONV(4);
GENERATE_CONV(8);

/**
 * Thread stack is a paged FIFO array that has a defined max. size.
 *
 * You can append
 */
class CThreadStack
{
    template<typename T>
    FORCEINLINE void GenericPush(T Value)
    {
        ASSERT_MSG(((u8)(Current - Begin) < (u8)Capacity),
            "Stack overflow. Used %llu bytes, want to push %llu bytes, max size: %llu (too many pushes called)",
            (u8)Current - (u8)Begin,
            (u8)sizeof(T),
            (u8)Capacity
        );

        // Unaligned store
        // TODO: Check if portable
        *((T*)Current) = Value;

        Current += sizeof(T);
    }

    template<typename T>
    FORCEINLINE T GenericPop()
    {
        Current -= sizeof(T);

        ASSERT_MSG((Current >= Begin),
            "Stack underflow by %llu bytes (too many pops called)",
            (u8)Begin - (u8)Current
        );

        return *((T*)Current);
    }

    template <typename TTo, typename TFrom /* = auto detect */>
    static TTo SameSizeBitCast(const TFrom Value)
    {
        static_assert(sizeof(TFrom) == sizeof(TTo), "TFrom and TTo types must have exactly the same size");

        return *(reinterpret_cast<const TTo*>(&Value));
    }

public:
    explicit CThreadStack(usz InCapacity) : Capacity(InCapacity)
    {
        Begin   = Util::CMemory::Malloc<u1>(Capacity, sizeof(void*));
        Current = Begin;
    }

    ~CThreadStack() = default;

    template <class T> FORCEINLINE void Push1(T Value)
    {
        static_assert(sizeof(T) <= 1, "sizeof(T) must be at most 1");

        GenericPush<u1>((u1)Conv1<T>(Value));
    }

    template <class T> FORCEINLINE void Push2(T Value)
    {
        static_assert(sizeof(T) <= 2, "sizeof(T) must be at most 2");

        GenericPush<u2>((u2)Conv2<T>(Value));
    }

    template <class T> FORCEINLINE void Push4(T Value)
    {
        static_assert(sizeof(T) <= 4, "sizeof(T) must be at most 4");

        GenericPush<u4>((u4)Conv4<T>(Value));
    }

    template <class T> FORCEINLINE void Push8(T Value)
    {
        static_assert(sizeof(T) <= 8, "sizeof(T) must be at most 8");

        GenericPush<u8>((u8)Conv8<T>(Value));
    }

    template <typename T> FORCEINLINE void Push(T Value)
    {
        if constexpr(sizeof(T) == 1)
            Push1(Value);
        else if constexpr(sizeof(T) == 2)
            Push2(Value);
        else if constexpr(sizeof(T) == 4)
            Push4(Value);
        else if constexpr(sizeof(T) == 8)
            Push8(Value);
    }

    FORCEINLINE void PushOOP(const oop Value)
    {
        GenericPush<oop>(Value);
    }

    FORCEINLINE void PushNullOOP()
    {
        PushOOP(oop::Null);
    }


//        template <class T> FORCEINLINE T Pop1()
//        {
//            return (T)Conv1<T>(GenericPop<u1>());
//        }
//
//        template <class T> FORCEINLINE T Pop2()
//        {
//            return (T)Conv2<T>(GenericPop<u2>());
//        }
//
//        template <class T> FORCEINLINE T Pop4()
//        {
//            return (T)Conv4<T>(GenericPop<u4>());
//        }
//
//        template <class T> FORCEINLINE T Pop8()
//        {
//            return (T)Conv8<T>(GenericPop<u8>());
//        }

    template <class T> FORCEINLINE T Pop()
    {
        return GenericPop<T>();
    }

private:
    /**
     *
     */
    u1* Begin   = nullptr;
    u1* Current = nullptr;

    const usz Capacity;
};

// Pop()
template <> FORCEINLINE u1 CThreadStack::Pop<u1>() { return GenericPop<u1>(); }

template <> FORCEINLINE s1 CThreadStack::Pop<s1>() { return SameSizeBitCast<s1>(GenericPop<u1>()); }

template <> FORCEINLINE u2 CThreadStack::Pop<u2>() { return GenericPop<u2>(); }

template <> FORCEINLINE s2 CThreadStack::Pop<s2>() { return SameSizeBitCast<s2>(GenericPop<u2>()); }

template <> FORCEINLINE u4 CThreadStack::Pop<u4>() { return GenericPop<u4>(); }

template <> FORCEINLINE s4 CThreadStack::Pop<s4>() { return SameSizeBitCast<s4>(GenericPop<u4>()); }

template <> FORCEINLINE u8 CThreadStack::Pop<u8>() { return GenericPop<u8>(); }

template <> FORCEINLINE s8 CThreadStack::Pop<s8>() { return SameSizeBitCast<s8>(GenericPop<u8>()); }

// Hand-written implementations for signed and unsigned primitive types for better performance.
// Push()
template <> FORCEINLINE void CThreadStack::Push1<u1>(u1 Value) { GenericPush<u1>(Value); }

template <> FORCEINLINE void CThreadStack::Push1<s1>(s1 Value) { GenericPush<u1>(SameSizeBitCast<u1>(Value)); }

template <> FORCEINLINE void CThreadStack::Push2<u2>(u2 Value) { GenericPush<u2>(Value); }

template <> FORCEINLINE void CThreadStack::Push2<s2>(s2 Value) { GenericPush<u2>(SameSizeBitCast<u2>(Value)); }

template <> FORCEINLINE void CThreadStack::Push4<u4>(u4 Value) { GenericPush<u4>(Value); }

template <> FORCEINLINE void CThreadStack::Push4<s4>(s4 Value) { GenericPush<u4>(SameSizeBitCast<u4>(Value)); }

template <> FORCEINLINE void CThreadStack::Push8<u8>(u8 Value) { GenericPush<u8>(Value); }

template <> FORCEINLINE void CThreadStack::Push8<s8>(s8 Value) { GenericPush<u8>(SameSizeBitCast<u8>(Value)); }

#else
    #define DEBUG_THREAD_STACK_CODE(Code)
#endif // DEBUG_THREAD_STACK

