#pragma once

#include "core/hardware.hpp"

#include <sstream>
#include <string>
#include <iomanip>

namespace momo {

inline std::string to_hex(u16 x)
{
    std::stringstream sstream;
    sstream << std::hex << std::setfill('0') << std::setw(4) << x;
    return sstream.str();
}

} // namespace momo