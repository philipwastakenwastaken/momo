#include <glad/gl.h>
#include <GLFW/glfw3.h>
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

    Emulator emu;
    emu.set_Ireg(0);

    Window& window = emu.get_window();

    Instruction ins = 0xD015;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    window.render(emu.get_screen_data());

    while (!window.should_close())
    {
        window.poll_events();
    }

    return 0;
}