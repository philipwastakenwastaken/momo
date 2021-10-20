#include "emu/memory.hpp"

namespace momo {

void Memory::write(u16 addr, const u8* data, u16 write_size)
{
    MOMO_ASSERT(write_size + addr < MemSize, "Address overflow on write");
    std::memcpy(mem.data(), data, write_size);
}

void Memory::read(u16 addr, u16 read_size, u8* buffer) const
{
    MOMO_ASSERT(read_size + addr < MemSize, "Address overflow on read");

    std::memcpy(buffer, mem.data() + addr, read_size);
}

} // namespace momo