#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/specs.hpp"

#include <array>
#include <cstring>

namespace momo {


class Memory
{
  public:
    template<typename ReadSize>
    ReadSize read(u16 addr) const;

    void write(u16 addr, const u8* data, u16 write_size);

  private:
    std::array<u16, MemSize> mem{};
};

template<typename ReadSize>
ReadSize Memory::read(u16 addr) const
{
    MOMO_ASSERT(sizeof(ReadSize) + addr < MemSize, "Address overflow on read");

    ReadSize ret = 0;
    std::memcpy(&ret, mem.data() + addr, sizeof(ReadSize));

    return ret;
}


} // namespace momo