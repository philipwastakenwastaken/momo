#include "util/timer.hpp"

namespace momo {

void Timer::start() { begin = std::chrono::steady_clock::now(); }

void Timer::stop() { end = std::chrono::steady_clock::now(); }

} // namespace momo