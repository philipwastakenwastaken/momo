#pragma once

#include "core/core.hpp"
#include "core/hardware.hpp"
#include "core/log.hpp"

#include <algorithm>
#include <climits>

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

// from and to are indexed from one, i.e. least significant bit is 1, not 0.
inline u16 toggle_bit_range(u16 from, u16 to)
{
    MOMO_ASSERT(from > 0 && from <= 16, "Invalid from range");
    MOMO_ASSERT(to > 0 && to <= 16, "Invalid to range");
    MOMO_ASSERT(from <= to, "From must be smaller than or equal to to");
    return u16(UINT_MAX >> (CHAR_BIT * sizeof(int) - to)) & (UINT_MAX << (from - 1));
}


} // namespace momo