#include "util/rng.hpp"
#include <random>

namespace momo {


RNG::RNG()
{
    mt = std::mt19937();
    mt.seed(Seed);
    dist = std::uniform_int_distribution<u8>();
}

u8 RNG::rand() { return dist(mt); }


} // namespace momo