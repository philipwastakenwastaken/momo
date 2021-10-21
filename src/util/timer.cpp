#include "util/timer.hpp"
#include <chrono>

namespace momo {

void Timer::start() { begin = std::chrono::high_resolution_clock::now(); }

void Timer::stop() { end = std::chrono::high_resolution_clock::now(); }

} // namespace momo