option(MOMO_ENABLE_EXCEPTIONS "Enable Exceptions" OFF)
option(MOMO_ENABLE_RTTI "Enable Run-time Type Information" OFF)
option(MOMO_ENABLE_POPCNT "Enable POPCNT hardware instuction" OFF)
option(MOMO_ENABLE_PEXT "Enable PEXT hardware instuction" OFF)
option(MOMO_ENABLE_ALL_EXTENSIONS "Enable all instruction set extensions available for the host" OFF)


# First build a library containing the source files
add_library(momolib STATIC emu/memory.cpp
                           emu/emulator.cpp
                           emu/instruction_fetcher.cpp
                           emu/instruction_decoder.cpp
                           render/window.cpp
                           render/opengl/vertex_buffer.cpp
                           render/opengl/vertex_buffer_layout.cpp
                           render/opengl/vertex_array.cpp
                           render/opengl/index_buffer.cpp
                           render/opengl/gl_shader.cpp
                           util/timer.cpp
                           util/rng.cpp
                           core/log.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


# Now link the source library publicly against spdlog
target_link_libraries(momolib PUBLIC
                              project_options
                              project_warnings
                              glfw
                              glad
                              glm
                              spdlog::spdlog)

# Prefer pthreads on Unix.
if (UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(momolib PRIVATE Threads::Threads)
endif()

# Exceptions
if (NOT MOMO_ENABLE_EXCEPTIONS)
	if (NOT MSVC)
		target_compile_options(momolib PUBLIC -fno-exceptions)
	endif()
endif()

# RTTI
if (NOT MOMO_ENABLE_RTTI)
    if (NOT MSVC)
        target_compile_options(momolib PUBLIC -fno-rtti)
    endif()
endif()


# Instruction set extensions
if (MOMO_ENABLE_POPCNT AND NOT MOMO_ENABLE_ALL_EXTENSIONS)
    add_compile_definitions(MOMO_ENABLE_POPCNT)
	if (NOT MSVC)
		target_compile_options(momolib PUBLIC -mpopcnt)
	endif()
endif()
if (MOMO_ENABLE_PEXT AND NOT MOMO_ENABLE_ALL_EXTENSIONS)
    add_compile_definitions(MOMO_ENABLE_PEXT)
	if (NOT MSVC)
		target_compile_options(momolib PUBLIC -mbmi2)
	endif()
endif()

if (MOMO_ENABLE_ALL_EXTENSIONS)
    add_compile_definitions(MOMO_ENABLE_POPCNT)
    add_compile_definitions(MOMO_ENABLE_PEXT)
	if (NOT MSVC)
		target_compile_options(momolib PUBLIC -march=native)
	endif()
endif()

# Create the final executable
add_executable(momo main.cpp)
target_link_libraries(momo PRIVATE
                            project_options
                            project_warnings
                            momolib)