#include "core/log.hpp"
#include "core/core.hpp"

#include "util/timer.hpp"

#include "emu/instruction_fetcher.hpp"
#include "emu/instruction_decoder.hpp"
#include "emu/emulator.hpp"

#include "render/window.hpp"

#include <chrono>
#include <string>
#include <thread>

using namespace momo;

int main(int /*argc*/, char** /*argv*/)
{
    Log::init();

    Window window;

    window.loop();


    return 0;
}