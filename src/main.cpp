#include "core/log.hpp"
#include "core/core.hpp"

#include "util/timer.hpp"

#include "emu/memory.hpp"

#include <string>

int main(int /*argc*/, char** /*argv*/)
{
    momo::Log::init();

    MOMO_TRACE("Hello world!");

    return 0;
}