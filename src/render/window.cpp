#include "render/window.hpp"
#include "GLFW/glfw3.h"
#include "core/core.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "render/opengl/vertex_array.hpp"
#include "render/opengl/vertex_buffer.hpp"
#include "render/opengl/gl_shader.hpp"

#include "util/rng.hpp"

namespace momo {

Window::Window()
{
    auto glfw_result = glfwInit();
    MOMO_ASSERT(glfw_result, "Could not initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef MOMO_PLATFORM_MACOSX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    window = glfwCreateWindow(WindowWidth, WindowHeight, "Momo: Chip-8 emulator", nullptr, nullptr);

    MOMO_ASSERT(window, "Could not initialize GLFW window");

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    auto gl_version = gladLoadGL(glfwGetProcAddress);
    MOMO_ASSERT(gl_version, "Could not initalize glad");
    MOMO_TRACE("Loaded OpenGL version {0}, {1}", GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));


    int h = 0;
    int w = 0;
    glfwGetFramebufferSize(window, &w, &h);
    MOMO_TRACE("w: {0} h {1}", w, h);
    glViewport(0, 0, w, h);

    // (0, 0) at top left
    proj = glm::ortho(0.0f, static_cast<float>(WindowWidth), static_cast<float>(WindowHeight), 0.0f, -1.0f, 1.0f);
}

Window::~Window() { glfwTerminate(); }

void Window::render(const ScreenDataArray& screen_data)
{
    auto* vert = new float[static_cast<u64>(WindowHeight * WindowWidth) * 6];

    constexpr glm::vec3 Black(0, 0, 0);
    constexpr glm::vec3 White(1, 1, 1);
    RNG rng;

    for (int y = 0; y < WindowHeight; y++)
    {
        for (int x = 0; x < WindowWidth; x++)
        {
            int index = (x + y * WindowHeight) * 6;
            vert[index] = static_cast<float>(x);
            vert[index + 1] = static_cast<float>(y);
            vert[index + 2] = 0.0f;

            glm::vec3 col;
            if (screen_data[u64(x)][u64(y)] == 1)
                col = Black;
            else
                col = White;

            vert[index + 3] = 0;
            vert[index + 4] = 0;
            vert[index + 5] = 0;
        }
    }

    u32 index = (62 + 31 * WindowHeight) * 6;
    vert[index + 3] = 1.0;
    vert[index + 4] = 0.0;
    vert[index + 5] = 1.0;

    VertexBuffer vbo(vert, WindowHeight * WindowWidth * 6, sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(3);
    VertexArray vao;
    vao.add_buffer(vbo, layout);

    vao.bind();
    Shader shader("/Users/philip/dev/momo/src/render/shaders/color.shader");
    shader.bind();

    auto loc = glGetUniformLocation(shader.get_render_id(), "proj");
    MOMO_TRACE("LOC: {0}", loc);


    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(1);

    shader.set_uniform_mat4f("proj", proj);
    glDrawArrays(GL_POINTS, 0, WindowHeight * WindowWidth);

    swap_buffers();

    delete[] vert;
}


} // namespace momo