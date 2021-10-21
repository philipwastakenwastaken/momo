#include "core/log.hpp"
#include "core/core.hpp"

#include "util/timer.hpp"

#include "emu/instruction_fetcher.hpp"
#include "emu/instruction_decoder.hpp"
#include "emu/emulator.hpp"

#include <string>

using namespace momo;

int main(int /*argc*/, char** /*argv*/)
{
    Log::init();

    Instruction ins = 0x00E0; // 1NNN, JUMP
    auto index = InstructionDecoder::decode(ins);
    MOMO_TRACE(index);

    // Emulator emu("/Users/philip/dev/momo/programs/IBM_Logo.ch8");
    // emu.fde_loop();


    return 0;
}