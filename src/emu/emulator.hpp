#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/instruction_decoder.hpp"
#include "emu/memory.hpp"

#include "util/rng.hpp"

namespace momo {

class Emulator
{

  public:
    explicit Emulator(std::string_view path) : program_path(path) {}

    // Fetch/decode/execute loop.
    void fde_loop();

    // Execute the given instruction.
    void execute(Instruction ins, InstructionIndex index);


  private:
    RNG rng{};

    Memory mem;

    // General purpose registers (8-bit)
    RegisterArray regs{};

    // Special registers
    IndexRegister Ireg = 0;
    u8 DTreg = 0;
    u8 STreg = 0;

    std::array<u16, StackSize> stack;
    u8 SPreg = 0;

    u16 PC = 0;

    std::string_view program_path;
};


} // namespace momo