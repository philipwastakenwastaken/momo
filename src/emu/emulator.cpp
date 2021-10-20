#include "emu/emulator.hpp"

#include "emu/instruction_fetcher.hpp"
#include "emu/specs.hpp"
#include "util/hex.hpp"

namespace momo {


void Emulator::fde_loop()
{
    InstructionFetcher ifetcher(program_path);

    MOMO_ASSERT(false, "Failed");
    while (true)
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
    }
}

void Emulator::execute(Instruction ins, InstructionIndex index)
{
    u16 nnn = ins & 0xFFF;
    u16 x = (ins & 0x0F00) >> 8;
    u16 y = (ins & 0x00F0) >> 4;
    u16 kk = ins & 0x00FF;

    constexpr void* labels[] = { &&CLS,
        &&RET,
        &&SYS_ADDR,
        &&JP_ADDR,
        &&CALL_ADDR,
        &&SE_VX_BYTE,
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

    goto *labels[index];


CLS : {
    (void)ins;
    goto END;
}
RET : {
    SPreg--;
    PC = stack[SPreg];
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
    stack[SPreg] = PC;
    SPreg++;
    PC = nnn;
    goto END;
}
SE_VX_BYTE : {
    goto END;
}
LD_VX_BYTE : {
    goto END;
}
ADD_VX_BYTE : {
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
    regs[0xF] = regs[x] > regs[y];
    regs[x] -= regs[y];
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
    regs[0xF] = regs[x] & 1;
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
    // TODO
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
    u16 hundreds = regs[x] / 100;
    u16 tenths = (regs[x] % 100) / 10;
    u16 ones = regs[x] % 10;

    mem.write(Ireg, reinterpret_cast<u8*>(&hundreds), sizeof(u16));
    mem.write(Ireg + 1, reinterpret_cast<u8*>(&tenths), sizeof(u16));
    mem.write(Ireg + 2, reinterpret_cast<u8*>(&ones), sizeof(u16));
    goto END;
}
LD_I_VX : {
    mem.write(Ireg, reinterpret_cast<u8*>(regs.data()), sizeof(u8) * (regs[x] + 1));
    goto END;
}
LD_VX_I : {
    mem.read(Ireg, regs[x] + 1, regs.data());
    goto END;
}


END:
    return;
}


} // namespace momo