#pragma once

#include "core/hardware.hpp"

namespace momo {

template<typename T>
T byte_swap(T x);

template<>
inline u16 byte_swap<u16>(u16 x)
{
    u16 hi_byte = (x & 0xff00) >> 8;
    u16 lo_byte = x & 0xff;
    return static_cast<u16>(lo_byte << 8 | hi_byte);
}


}