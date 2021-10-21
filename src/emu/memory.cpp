#include "emu/memory.hpp"
#include "emu/specs.hpp"

namespace momo {

Memory::Memory() noexcept
{
    // Legal since address 0x0 to 0x200 is reserved.
    std::memcpy(mem.data(), FontData.data(), FontDataSize);
}

void Memory::write(u16 addr, const u8* data, u16 write_size)
{
    MOMO_ASSERT(write_size + addr < MemSize, "Address overflow on write");
    MOMO_ASSERT(write_size > 0, "Write size is 0");
    std::memcpy(mem.data() + addr, data, write_size);
}

void Memory::read(u16 addr, u16 read_size, u8* buffer) const
{
    MOMO_ASSERT(read_size > 0, "Read size is 0");
    MOMO_ASSERT(read_size + addr < MemSize, "Address overflow on read");

    std::memcpy(buffer, mem.data() + addr, read_size);
}

} // namespace momo