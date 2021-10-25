#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/instruction_decoder.hpp"
#include "emu/instruction_fetcher.hpp"
#include "emu/memory.hpp"
#include "emu/specs.hpp"

#include "util/rng.hpp"

#include "render/window.hpp"


namespace momo {

class Emulator
{

  public:
    explicit Emulator(std::string_view path) : ifetcher(path), program_path(path) {}
    Emulator() = default;

    // Main emulation loop.
    void loop();

    // Execute the given instruction.
    void execute(Instruction ins, InstructionIndex index);

    u16 cpu_tick();
    void timer_tick();

    [[nodiscard]] u8 get_register(u8 idx) const { return regs[idx]; }
    [[nodiscard]] u16 get_PC() const { return PC; }
    [[nodiscard]] u16 get_Ireg() const { return Ireg; }
    [[nodiscard]] u8 get_DTreg() const { return DTreg; }
    [[nodiscard]] u8 get_STreg() const { return STreg; }
    [[nodiscard]] const Memory& get_mem() const { return mem; }
    [[nodiscard]] Memory& get_mem() { return mem; }
    [[nodiscard]] const ScreenDataArray& get_screen_data() const { return screen_data; }
    [[nodiscard]] Window& get_window() { return window; }

    [[nodiscard]] u16 stack_top() const { return stack[SPreg]; }

    void set_reg(u8 idx, u8 value) { regs[idx] = value; }
    void set_Ireg(u16 value) { Ireg = value; }
    void set_DTreg(u8 value) { DTreg = value; }
    void set_STreg(u8 value) { STreg = value; }


  private:
    void poll_events(bool& quit);

    InstructionFetcher ifetcher;
    bool draw_instruction = false;

    RNG rng{};

    Memory mem;

    // General purpose registers (8-bit)
    RegisterArray regs{};

    // Special registers
    u16 Ireg = MemStartAddress;
    u8 DTreg = 0;
    u8 STreg = 0;

    std::array<u16, StackSize> stack{};
    u8 SPreg = 0;

    u16 PC = 0;

    ScreenDataArray screen_data{};
    Window window;

    std::string_view program_path;
};


} // namespace momo