#include "core/log.hpp"
#include "core/core.hpp"

#include "util/timer.hpp"

#include "emu/instruction_fetcher.hpp"
#include "emu/emulator.hpp"

#include <string>

using namespace momo;

int main(int /*argc*/, char** /*argv*/)
{
    Log::init();

    Emulator emu("/Users/philip/dev/chip8-emu/programs/IBM_Logo.ch8");

    emu.fde_loop();



    return 0;
}