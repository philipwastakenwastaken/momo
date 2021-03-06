#include "emu/emulator.hpp"

#include "emu/instruction_decoder.hpp"
#include "emu/specs.hpp"

#include "util/hex.hpp"
#include "util/timer.hpp"
#include <chrono>
#include <thread>

namespace momo {


void Emulator::loop()
{
    Timer timer;
    u64 accumulated_time = 0;

    constexpr u64 TimerUpdateRate = 16666;

    while (!window.should_close())
    {
        timer.start();
        window.poll_events();

        u16 cpu_time = cpu_tick();


        if (draw_instruction)
            window.render(screen_data);

        timer.stop();
        auto elapsed = timer.elapsed<Micro>();
        accumulated_time += elapsed;

        // Timers update at a rate of 60 Hz.
        if (accumulated_time > TimerUpdateRate)
        {
            timer_tick();
            accumulated_time = 0;
        }

        // We should spend at most cpu_time microseconds each iteration.
        auto sleep_time = std::chrono::microseconds(cpu_time - elapsed);
        std::this_thread::sleep_for(sleep_time);
    }
}


u16 Emulator::cpu_tick()
{
    /// FETCH
    Instruction ins = ifetcher.fetch(PC);
    MOMO_TRACE(to_hex(ins));

    // Increment the PC now so that we don't forget later.
    PC += PCIncrement;

    /// DECODE
    InstructionIndex index = InstructionDecoder::decode(ins);

    // EXECUTE
    execute(ins, index);

    return InstructionTimings[index].time;
}

void Emulator::timer_tick()
{
    if (DTreg > 0)
        DTreg--;
    if (STreg > 0)
        STreg--;
}

void Emulator::execute(Instruction ins, InstructionIndex index)
{
    draw_instruction = false;

    u16 nnn = ins & 0x0FFF;
    u8 n = ins & 0xF;
    u16 x = (ins & 0x0F00) >> 8;
    u16 y = (ins & 0x00F0) >> 4;
    u16 kk = ins & 0x00FF;

    constexpr void* labels[] = { &&CLS,
        &&RET,
        &&SYS_ADDR,
        &&JP_ADDR,
        &&CALL_ADDR,
        &&SE_VX_BYTE,
        &&SNE_VX_BYTE,
        &&SE_VX_VY,
        &&LD_VX_BYTE,
        &&ADD_VX_BYTE,
        &&LD_VX_VY,
        &&OR_VX_VY,
        &&AND_VX_VY,
        &&XOR_VX_VY,
        &&ADD_VX_VY,
        &&SUB_VX_VY,
        &&SHR_VX_VY,
        &&SUBN_VX_VY,
        &&SHL_VX_VY,
        &&SNE_VX_VY,
        &&LD_I_ADDR,
        &&JP_V0_ADDR,
        &&RND_VX_BYTE,
        &&DRW_VX_VY_NIBBLE,
        &&SKP_VX,
        &&SKNP_VX,
        &&LD_VX_DT,
        &&LD_VX_K,
        &&LD_DT_VX,
        &&LD_ST_VX,
        &&ADD_I_VX,
        &&LD_F_VX,
        &&LD_B_VX,
        &&LD_I_VX,
        &&LD_VX_I };

    goto* labels[index];


CLS : {
    (void)ins;
    goto END;
}
RET : {
    PC = stack[SPreg];
    SPreg--;
    goto END;
}
SYS_ADDR : {
    (void)index;
    goto END;
}
JP_ADDR : {
    PC = nnn;
    goto END;
}
CALL_ADDR : {
    SPreg++;
    stack[SPreg] = PC;
    PC = nnn;
    goto END;
}
SE_VX_BYTE : {
    if (regs[x] == kk)
        PC += PCIncrement;
    goto END;
}
SNE_VX_BYTE : {
    if (regs[x] != kk)
        PC += PCIncrement;
    goto END;
}
SE_VX_VY : {
    if (regs[x] == regs[y])
        PC += PCIncrement;
    goto END;
}
LD_VX_BYTE : {
    regs[x] = static_cast<u8>(kk);
    goto END;
}
ADD_VX_BYTE : {
    regs[x] += kk;
    goto END;
}
LD_VX_VY : {
    regs[x] = regs[y];
    goto END;
}
OR_VX_VY : {
    regs[x] |= regs[y];
    goto END;
}
AND_VX_VY : {
    regs[x] &= regs[y];
    goto END;
}
XOR_VX_VY : {
    regs[x] ^= regs[y];
    goto END;
}
ADD_VX_VY : {
    u16 result = regs[x] + regs[y];
    regs[0xF] = result > 255;
    regs[x] = result & 0xFF;
    goto END;
}
SUB_VX_VY : {
    u8 vx = regs[x];
    u8 vy = regs[y];
    regs[0xF] = vx > vy;
    regs[x] = vx - vy;
    goto END;
}
SHR_VX_VY : {
    regs[0xF] = regs[x] & 1;
    regs[x] >>= 1;
    goto END;
}
SUBN_VX_VY : {
    regs[0xF] = regs[y] > regs[x];
    regs[x] = regs[y] - regs[x];
    goto END;
}
SHL_VX_VY : {
    regs[0xF] = bool(regs[x] & 0b10000000);
    regs[x] <<= 1;
    goto END;
}
SNE_VX_VY : {
    if (regs[x] != regs[y])
        PC += PCIncrement;
    goto END;
}
LD_I_ADDR : {
    Ireg = nnn;
    goto END;
}
JP_V0_ADDR : {
    PC = nnn + regs[0x0];
    goto END;
}
RND_VX_BYTE : {
    regs[x] = rng.rand() & kk;
    goto END;
}
DRW_VX_VY_NIBBLE : {
    draw_instruction = true;
    u8 x_coord = regs[x] % 64;
    u8 y_coord = regs[y] % 32;
    regs[0xF] = 0;

    u8 sprite_data[15]{};
    mem.read(Ireg, n, sprite_data);

    for (u32 i = 0; i <= n; ++i)
    {
        u8 row_data = sprite_data[i];

        if (y_coord > WindowHeight)
            break;

        for (u32 j = 0; j < 8; ++j)
        {
            u8 pixel = bool(row_data & 0b10000000);

            // Break if we reach edge of screen.
            if (x_coord >= WindowWidth)
            {
                MOMO_TRACE("Stopping row: {0} {1}", x_coord, y_coord);
                break;
            }

            // If sprite bitmap and corresponding pixel is on, turn pixel off and
            // set 0xF to 1.
            if (pixel && screen_data[x_coord][y_coord])
            {
                MOMO_TRACE("Turned off pixel at: {0}, {1}", x_coord, y_coord);
                screen_data[x_coord][y_coord] = 0;
                regs[0xF] = 1;
            }

            // If sprite bitmap is on, turn the pixel on.
            if (pixel)
            {
                MOMO_TRACE("Drew pixel at: {0}, {1}", x_coord, y_coord);
                screen_data[x_coord][y_coord] = 1;
            }


            ++x_coord;
            row_data <<= 1;
        }

        ++y_coord;
    }


    goto END;
}
SKP_VX : {
    // TODO
    goto END;
}
SKNP_VX : {
    // TODO
    goto END;
}
LD_VX_DT : {
    regs[x] = DTreg;
    goto END;
}
LD_VX_K : {
    // TODO
    goto END;
}
LD_DT_VX : {
    DTreg = regs[x];
    goto END;
}
LD_ST_VX : {
    STreg = regs[x];
    goto END;
}
ADD_I_VX : {
    Ireg += regs[x];
    goto END;
}
LD_F_VX : {
    // TODO
    goto END;
}
LD_B_VX : {
    u8 hundreds = regs[x] / 100;
    u8 tenths = (regs[x] % 100) / 10;
    u8 ones = regs[x] % 10;

    // Pack together to save memcpy calls.
    u8 buffer[3] = { hundreds, tenths, ones };
    mem.write(Ireg, buffer, 3);

    goto END;
}
LD_I_VX : {
    mem.write(Ireg, reinterpret_cast<u8*>(regs.data()), sizeof(u8) * (x + 1));
    goto END;
}
LD_VX_I : {
    // Could technically get away with a single memcpy call here, but I like going through
    // the memory.read() interface for safety.

    u8 buffer[RegCount];
    u16 write_size = x + 1;
    mem.read(Ireg, write_size, buffer);

    std::memcpy(regs.data(), buffer, write_size);
    goto END;
}


END:
    return;
}


} // namespace momo