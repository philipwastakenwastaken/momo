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
    void read(u16 addr, u16 read_size, u8* buffer) const;

    void write(u16 addr, const u8* data, u16 write_size);

  private:
    std::array<u16, MemSize> mem{};
};



} // namespace momo