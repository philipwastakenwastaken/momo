#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/specs.hpp"

// Technical reference used: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#00E0

namespace momo {

using InstructionIndex = u8;

struct BitRange
{
    constexpr BitRange(u8 in_start, u8 in_end): start(in_start), end(in_end) {}
    u8 start;
    u8 end;
};

struct InstructionEncoding
{
    constexpr InstructionEncoding(std::string_view n, u8 c, std::array<BitRange, 2> bt, std::array<u16, 2> t):
    name(n), num_components(c), bit_targets(bt), targets(t) {}
    std::string_view name;
    u8 num_components;
    std::array<BitRange, 2> bit_targets;
    std::array<u16, 2> targets;

    bool operator==(const InstructionEncoding& other) const { return name == other.name; }

};

// All instructions supported by CHIP-8.
constexpr u64 NumInstructions = 35;
constexpr std::array<InstructionEncoding, NumInstructions> InstructionEncodings = {
    InstructionEncoding("CLS", 1, {BitRange(1, 16), BitRange(0, 0)}, {0x00E0, 0}),
    InstructionEncoding("RET", 1, {BitRange(1, 16), BitRange(0, 0)}, {0x00EE, 0}),
    InstructionEncoding("SYS addr", 1, {BitRange(13, 16), BitRange(0, 0)}, {0, 0}),
    InstructionEncoding("JP addr", 1, {BitRange(13, 16), BitRange(0, 0)}, {1, 0}),
    InstructionEncoding("CALL addr", 1, {BitRange(13, 16), BitRange(0, 0)}, {2, 0}),
    InstructionEncoding("SE Vx, byte", 1, {BitRange(13, 16), BitRange(0, 0)}, {3, 0}),
    InstructionEncoding("SNE Vx, byte", 1, {BitRange(13, 16), BitRange(0, 0)}, {4, 0}),
    InstructionEncoding("SE Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {5, 0}),
    InstructionEncoding("LD Vx, byte", 1, {BitRange(13, 16), BitRange(0, 0)}, {6, 0}),
    InstructionEncoding("ADD Vx, byte", 1, {BitRange(13, 16), BitRange(0, 0)}, {7, 0}),
    InstructionEncoding("LD Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 0}),
    InstructionEncoding("OR Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 1}),
    InstructionEncoding("AND Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 2}),
    InstructionEncoding("XOR Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 3}),
    InstructionEncoding("ADD Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 4}),
    InstructionEncoding("SUB Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 5}),
    InstructionEncoding("SHR Vx {, Vy}", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 6}),
    InstructionEncoding("SUBN Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 7}),
    InstructionEncoding("SHL Vx {, Vy}", 2, {BitRange(13, 16), BitRange(1, 4)}, {8, 0xE}),
    InstructionEncoding("SNE Vx, Vy", 2, {BitRange(13, 16), BitRange(1, 4)}, {9, 0}),
    InstructionEncoding("LD I, addr", 1, {BitRange(13, 16), BitRange(0, 0)}, {0xA, 0}),
    InstructionEncoding("JP V0, addr", 1, {BitRange(13, 16), BitRange(0, 0)}, {0xB, 0}),
    InstructionEncoding("RND Vx, byte", 1, {BitRange(13, 16), BitRange(0, 0)}, {0xC, 0}),
    InstructionEncoding("DRW Vx, Vy, nibble", 1, {BitRange(13, 16), BitRange(0, 0)}, {0xD, 0}),
    InstructionEncoding("SKP Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xE, 0x9E}),
    InstructionEncoding("SKNP Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xE, 0xA1}),
    InstructionEncoding("LD Vx, DT", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x07}),
    InstructionEncoding("LD Vx, K", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x0A}),
    InstructionEncoding("LD DT, Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x15}),
    InstructionEncoding("LD ST, Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x18}),
    InstructionEncoding("ADD I, Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x1E}),
    InstructionEncoding("LD F, Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x29}),
    InstructionEncoding("LD B, Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x33}),
    InstructionEncoding("LD [I], Vx", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x55}),
    InstructionEncoding("LD Vx, [I]", 2, {BitRange(13, 16), BitRange(1, 8)}, {0xF, 0x65})
};

// Mainly used for testing. Finds the index of a given instruction in the above InstructionEncodings
// array.
InstructionIndex find_instruction_index(std::string_view name);

class InstructionDecoder
{
  public:
    [[nodiscard]] static InstructionIndex decode(Instruction ins);

  private:
};

} // namespace momo