#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/specs.hpp"



namespace momo {

class Window
{
    public:
        Window();
        ~Window();

        // Takes a 2d array of pixels which are rendered to the window.
        void render(const ScreenDataArray& screen_data);

        void swap_buffers() { glfwSwapBuffers(window); }
        void poll_events() { glfwPollEvents(); }
        [[nodiscard]] bool should_close() const { return glfwWindowShouldClose(window); }

        [[nodiscard]] GLFWwindow* get_window() { return window; }
    private:
        GLFWwindow* window = nullptr;
        glm::mat4 proj;

};

}