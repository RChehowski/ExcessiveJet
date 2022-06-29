//
// Created by ASUS on 05/04/2021.
//

#pragma once

#include "Util/Types.h"
#include "JavaWorld/Oop.h"

#include <vector>


#if USE_64_OOPS
    using LocalVariableValueType = u8;
#else
    using LocalVariableValueType = u4;
#endif // USE_64_OOPS

/** For interpreter */
class CLocalVariablesDynamic
{
public:
    explicit CLocalVariablesDynamic(const u2 NumLocals) : Values(new LocalVariableValueType[NumLocals])
    {
    }

    CLocalVariablesDynamic(const CLocalVariablesDynamic&) = delete;
    CLocalVariablesDynamic(CLocalVariablesDynamic&&) = delete;

    ~CLocalVariablesDynamic()
    {
        delete[] Values;
    }

    CLocalVariablesDynamic operator=(const CLocalVariablesDynamic&) = delete;
    CLocalVariablesDynamic operator=(CLocalVariablesDynamic&&) = delete;

#if USE_64_OOPS
    template <typename T>
    FORCEINLINE void Set(const u2 InIndex, const T InValue)
    {
        static_assert(false, "Not implemented yet!");
    }
#else
    template <typename T>
    FORCEINLINE void Set(const u2 InIndex, const T InValue)
    {
        static_assert(sizeof(T) <= (sizeof(LocalVariableValueType) * 2), "Unsupported type");

        if constexpr (std::is_same_v<T, oop>)
        {
            *(Values + InIndex) = static_cast<LocalVariableValueType>(reinterpret_cast<oop*>(&InValue)->GetValue());
        }
        else if constexpr(sizeof(T) <= sizeof(LocalVariableValueType))
        {
            // byte, short, int or float
            *(Values + InIndex) = static_cast<LocalVariableValueType>(InValue);
        }
        else if constexpr(sizeof(T) == (sizeof(LocalVariableValueType) * 2))
        {
            // long or double
            *reinterpret_cast<u8*>(Values + InIndex) = *reinterpret_cast<u8*>(&InValue);
        }
    }
#endif

    template <typename T>
    FORCEINLINE T Get(const u2 InIndex) const
    {
        static_assert(sizeof(T) <= (sizeof(LocalVariableValueType) * 2), "Unsupported type");

        if constexpr (std::is_same_v<T, oop>)
        {
            return oop { *reinterpret_cast<oopValue*>(Values + InIndex) };
        }
        else if constexpr (sizeof(T) <= sizeof(LocalVariableValueType))
        {
            return static_cast<T>(*reinterpret_cast<u4*>(Values + InIndex));
        }
        else if constexpr(sizeof(T) == (sizeof(LocalVariableValueType) * 2))
        {
            // long or double
            return static_cast<T>(*reinterpret_cast<u8*>(Values + InIndex));
        }
    }

private:
    LocalVariableValueType* const Values;
};

/** For compiler */
template <u2 NumLocals>
class CLocalVariablesStatic
{
public:
    explicit CLocalVariablesStatic() = default;

    CLocalVariablesStatic(const CLocalVariablesStatic&) = delete;
    CLocalVariablesStatic(CLocalVariablesStatic&&) = delete;

    CLocalVariablesDynamic operator=(const CLocalVariablesDynamic&) = delete;
    CLocalVariablesDynamic operator=(CLocalVariablesDynamic&&) = delete;

#if USE_64_OOPS
    template <typename T>
    FORCEINLINE void Set(const u2 InIndex, const T InValue)
    {
        static_assert(false, "Not implemented yet!");
    }
#else
    template <typename T>
    FORCEINLINE void Set(const u2 InIndex, const T InValue)
    {
        static_assert(sizeof(T) <= (sizeof(LocalVariableValueType) * 2), "Unsupported type");

        if constexpr (std::is_same_v<T, oop>)
        {
            *(Values + InIndex) = static_cast<LocalVariableValueType>(reinterpret_cast<oop*>(&InValue)->GetValue());
        }
        else if constexpr(sizeof(T) <= sizeof(LocalVariableValueType))
        {
            // byte, short, int or float
            *(Values + InIndex) = static_cast<LocalVariableValueType>(InValue);
        }
        else if constexpr(sizeof(T) == (sizeof(LocalVariableValueType) * 2))
        {
            // long or double
            *reinterpret_cast<u8*>(Values + InIndex) = *reinterpret_cast<u8*>(&InValue);
        }
    }
#endif

    template <typename T>
    [[nodiscard]] FORCEINLINE T Get(const u2 InIndex) const
    {
        static_assert(sizeof(T) <= (sizeof(LocalVariableValueType) * 2), "Unsupported type");

        if constexpr (std::is_same_v<T, oop>)
        {
            return oop { *reinterpret_cast<const oopValue*>(Values + InIndex) };
        }
        else if constexpr (sizeof(T) <= sizeof(LocalVariableValueType))
        {
            return static_cast<T>(*reinterpret_cast<u4*>(Values + InIndex));
        }
        else if constexpr(sizeof(T) == (sizeof(LocalVariableValueType) * 2))
        {
            // long or double
            return static_cast<T>(*reinterpret_cast<u8*>(Values + InIndex));
        }
    }

private:
    LocalVariableValueType Values[NumLocals];
};


