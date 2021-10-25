#pragma once

#include "core/hardware.hpp"

#include <array>

// Everything inside this file should be constexpr.

namespace momo {

// Upscaled by 10.
constexpr i32 WindowScaleFactor = 10;
constexpr i32 WindowWidth = 64;
constexpr i32 WindowHeight = 32;
using ScreenDataArray = std::array<std::array<u8, WindowHeight>, WindowWidth>;

constexpr u16 MemSize = 4096;
constexpr u16 MemStartAddress = 0x200;

// 16 general purpose 8-bit registers + 1 16-bit index register
constexpr u16 RegCount = 16;
using RegisterArray = std::array<u8, RegCount>;

// Chip-8 fetches 16-bit instructions, which means that the PC
// must be incremented by the same amount (in bytes).
constexpr u16 InstructionSize = 2;
using Instruction = u16;
constexpr u16 PCIncrement = InstructionSize;

constexpr u16 StackSize = 16;


constexpr u16 FontDataSize = 80;
// clang-format off
constexpr std::array<u8, FontDataSize> FontData = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
// clang-format on

} // namespace momo