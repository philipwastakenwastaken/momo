#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include <SDL.h>
#include <string>

namespace momo {

class Window
{
    public:
        Window();
        ~Window();

        void loop();


    private:

    char const* Title = "Momo: Chip-8 Emulator";
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;

};


}