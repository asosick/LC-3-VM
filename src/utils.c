//
// Created by August Sosick on 2022-09-05.
//
#include "utils.h"

u16 sign_extend(u16 x, u32 bit_count)
{
    if((x >> (bit_count)) & 0x1)
    {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

u16 swap16(u16 x)
{
    return (x << 8) | (x >> 8);
}


