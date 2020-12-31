//
// Created by ASUS on 30/12/2020.
//

#include "Platform/Misc.h"

namespace Util
{
    u1 BigEndianToNative(u1 Value)
    {
        return Value;
    }

    u2 BigEndianToNative(u2 Value)
    {
        if constexpr(IsLittleEndian())
        {
            union
            {
                u2 U2;
                u1 U1[2];
            } Converter {};

            Converter.U2 = Value;
            std::swap(Converter.U1[0], Converter.U1[1]);
            return Converter.U2;
        }
        else
        {
            return Value;
        }
    }

    u4 BigEndianToNative(u4 Value)
    {
        if constexpr(IsLittleEndian())
        {
            union
            {
                u4 U4;
                u1 U1[4];
            } Converter {};

            Converter.U4 = Value;

            std::swap(Converter.U1[0], Converter.U1[3]);
            std::swap(Converter.U1[1], Converter.U1[2]);

            return Converter.U4;
        }
        else
        {
            return Value;
        }
    }

    u8 BigEndianToNative(u8 Value)
    {
        if constexpr(IsLittleEndian())
        {
            union
            {
                u8 U8;
                u1 U1[8];
            } Converter;

            Converter.U8 = Value;

            std::swap(Converter.U1[0], Converter.U1[7]);
            std::swap(Converter.U1[1], Converter.U1[6]);
            std::swap(Converter.U1[2], Converter.U1[5]);
            std::swap(Converter.U1[3], Converter.U1[4]);

            return Converter.U8;
        }
        else
        {
            return Value;
        }
    }
}