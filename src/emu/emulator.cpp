#include "emu/emulator.hpp"

#include "emu/instruction_fetcher.hpp"
#include "util/hex.hpp"

namespace momo {


void Emulator::fde_loop()
{
    InstructionFetcher fetcher(program_path);

    while (true)
    {
        // Fetch instruction
        Instruction ins = fetcher.fetch(PC);
        MOMO_TRACE(to_hex(ins));


        // Increment the PC now so that we don't forget later.
        PC += PCIncrement;

        // Decode instruction

        // Execute instruction

        // Increment program counter and move on to next cycle.

        break;
    }

}



}