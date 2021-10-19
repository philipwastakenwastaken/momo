#include "emu/instruction_fetcher.hpp"

#include <cstring>
#include <fstream>
#include "util/bits.hpp"

namespace momo {


InstructionFetcher::InstructionFetcher(std::string_view file_path)
{
    MOMO_TRACE(file_path);
    std::ifstream infile(file_path, std::ios_base::binary);
    MOMO_ASSERT(!infile.fail(), "File could not be opened");

    std::vector<char> buffer((std::istreambuf_iterator<char>(infile)),
                              std::istreambuf_iterator<char>() );

    MOMO_TRACE("File contains {0} bytes", buffer.size());

    // Move to a raw pointer.
    program_size = static_cast<u32>(buffer.size());
    program = new u8[buffer.size()];
    std::memcpy(program, buffer.data(), buffer.size());
}


InstructionFetcher::~InstructionFetcher()
{
    MOMO_ASSERT(program, "InstructionFetcher program pointer is null");
    delete[] program;
}

Instruction InstructionFetcher::fetch(u16 PC) const
{
    MOMO_ASSERT(PC < program_size, "PC is larger than program size");
    Instruction ins = 0;

    std::memcpy(&ins, program + PC, InstructionSize);

    // Little endian is assumed.
    ins = byte_swap(ins);
    return ins;
}


}