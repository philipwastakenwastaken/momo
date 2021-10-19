#pragma once
#include <chrono>

namespace momo {

using MILLI = std::chrono::milliseconds;
using MICRO = std::chrono::microseconds;
using NANO = std::chrono::nanoseconds;

class Timer
{

  public:
    void start();
    void stop();

    template<typename T = std::chrono::seconds>
    [[nodiscard]] unsigned long long elapsed() const
    {
        return static_cast<unsigned long long>(std::chrono::duration_cast<T>(end - begin).count());
    }

  private:
    std::chrono::steady_clock::time_point begin, end;
};


} // namespace manni