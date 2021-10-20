#include "util/rng.hpp"
#include <random>

namespace momo {


RNG::RNG()
{
    std::random_device rd;
    mt = std::mt19937(rd);
    dist = std::uniform_int_distribution<u8>();
}

u8 RNG::rand() { return dist(mt); }


} // namespace momo