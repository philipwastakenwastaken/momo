#include "render/window.hpp"

#include "emu/specs.hpp"

namespace momo {

Window::Window()
{
    auto result = SDL_Init(SDL_INIT_VIDEO);
    MOMO_ASSERT(result >= 0, "SDL init failed");

    window = SDL_CreateWindow(
        Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    MOMO_ASSERT(window != nullptr, "Window could not be created");

    surface = SDL_GetWindowSurface(window);
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::loop()
{
    SDL_Event e;
    bool quit = false;

    while (!quit)
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                break;
}

} // namespace momo