#pragma once

#include <string>

#include "emu/specs.hpp"

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"


/// IMPORTANT ASSUMPTION!!! ///
// We assume that the host architecture uses little endian, whereas the original
// Chip-8 is big endian. This means that all instructions are converted from big endian to little
// endian internally.

namespace momo {


class InstructionFetcher
{

  public:
    // file_path contains the file_path of the <program-name>.ch8 program to be run.
    explicit InstructionFetcher(std::string_view file_path);
    InstructionFetcher() = default;
    ~InstructionFetcher();

    [[nodiscard]] Instruction fetch(u16 PC) const;

    [[nodiscard]] u32 get_program_size() const { return program_size; }


  private:
    u8* program = nullptr;
    u32 program_size = 0;
};


} // namespace momo