add_executable(tests gtest_main.cpp
                     gtest_util.cpp
                     gtest_memory.cpp
                     gtest_instruction_execute.cpp
                     gtest_instruction_decode.cpp)

target_link_libraries(tests gtest)
target_link_libraries(tests momolib)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)
include(GoogleTest)
gtest_discover_tests(tests)