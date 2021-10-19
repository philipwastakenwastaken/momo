#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/memory.hpp"

namespace momo {

class Emulator
{

  public:
    explicit Emulator(std::string_view path) : program_path(path) {}

    // Fetch/decode/execute loop
    void fde_loop();


  private:
    Memory mem;
    RegisterArray regs;

    u16 PC;
    std::string_view program_path;
};


} // namespace momo