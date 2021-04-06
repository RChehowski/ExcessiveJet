//
// Created by ASUS on 05/04/2021.
//

#pragma once

#include "Types.h"
#include <vector>

namespace Service
{
    class CLocalVariable
    {
    public:
        [[nodiscard]]
        FORCEINLINE bool IsInt() const
        {
            // Dummy
            return true;
        }

        [[nodiscard]]
        FORCEINLINE s4 GetInt() const
        {
            // Dummy
            return (s4)0;
        }


        [[nodiscard]]
        FORCEINLINE bool IsLong() const
        {
            // Dummy
            return true;
        }

        [[nodiscard]]
        FORCEINLINE s8 GetLong() const
        {
            // Dummy
            return (s8)0;
        }


        [[nodiscard]]
        FORCEINLINE bool IsFloat() const
        {
            // Dummy
            return true;
        }

        [[nodiscard]]
        FORCEINLINE f4 GetFloat() const
        {
            // Dummy
            return (f4)0;
        }


        [[nodiscard]]
        FORCEINLINE bool IsDouble() const
        {
            // Dummy
            return true;
        }

        [[nodiscard]]
        FORCEINLINE f4 GetDouble() const
        {
            // Dummy
            return (f8)0;
        }


        [[nodiscard]]
        FORCEINLINE bool IsReference() const
        {
            // Dummy
            return true;
        }

        [[nodiscard]]
        FORCEINLINE oop GetReference() const
        {
            // Dummy
            return (oop)0;
        }
    };

    class CLocalVariables
    {
    public:
        FORCEINLINE CLocalVariable& operator[](usz Index)
        {
            return LocalVariables[Index];
        }

        FORCEINLINE const CLocalVariable& operator[](usz Index) const
        {
            return LocalVariables[Index];
        }

    private:
        std::vector<CLocalVariable> LocalVariables;
    };
}

