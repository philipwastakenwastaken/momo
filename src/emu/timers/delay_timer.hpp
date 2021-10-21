#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>

namespace momo {

class DelayTimer
{
  public:
  private:
      u8 DT = 0;

      std::mutex lock;
      std::thread internal_thread;
};


} // namespace momo