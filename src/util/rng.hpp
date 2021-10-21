#pragma once

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include <random>

namespace momo {

constexpr u64 Seed = 9128492;

// Generates random 8-bit numbers
class RNG
{
  public:
    RNG();
    ~RNG() = default;

    u8 rand();

  private:
    std::mt19937 mt;
    std::uniform_int_distribution<u8> dist;
};


} // namespace momo
