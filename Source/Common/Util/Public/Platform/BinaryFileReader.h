//
// Created by ASUS on 26/02/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    enum class EBinaryFileReaderSeekOrigin
    {
        Begin,
        End,
        Current
    };

    class CBinaryFileReader
    {
    public:
        virtual bool IsValid() const = 0;

        virtual usz GetSize() const = 0;

        virtual usz Tell() const = 0;

        virtual bool Seek() = 0;
    };
}