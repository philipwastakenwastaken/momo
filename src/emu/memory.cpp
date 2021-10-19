#include "emu/memory.hpp"

namespace momo {

void Memory::write(u16 addr, const u8* data, u16 write_size)
{
    MOMO_ASSERT(write_size + addr < MemSize, "Address overflow on write");
    std::memcpy(mem.data(), data, write_size);
}

} // namespace momo