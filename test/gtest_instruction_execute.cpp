#include "gtest/gtest.h"

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/emulator.hpp"
#include "emu/specs.hpp"

using namespace momo;

class InstructionExecute : public ::testing::Test
{
    protected:

    void SetUp() override
    {
        emu = Emulator();
    }

    Emulator emu;

};

TEST_F(InstructionExecute, CALL_ADDR_AND_RET)
{
    auto old_PC1 = emu.get_PC();
    u16 new_PC1 = 0x005;
    Instruction ins = 0x2000 | new_PC1;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_NE(old_PC1, new_PC1);
    EXPECT_EQ(new_PC1, emu.get_PC());
    EXPECT_EQ(emu.stack_top(), 0x0);

    auto old_PC2 = emu.get_PC();
    u16 new_PC2 = 0x01C0;
    ins = 0x2000 | new_PC2;
    index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_NE(old_PC2, new_PC2);
    EXPECT_EQ(new_PC2, emu.get_PC());
    EXPECT_EQ(emu.stack_top(), old_PC2);

    ins = 0x00EE;
    index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);
    EXPECT_EQ(old_PC2, emu.get_PC());
    EXPECT_EQ(emu.stack_top(), 0x0);

    ins = 0x00EE;
    index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);
    EXPECT_EQ(old_PC1, emu.get_PC());
    EXPECT_EQ(emu.stack_top(), 0x0);
}

TEST_F(InstructionExecute, SE_VX_BYTE)
{
    emu.set_reg(0, 5);

    auto old_PC = emu.get_PC();
    Instruction ins = 0x3005;

    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_NE(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), 2);

    old_PC = emu.get_PC();
    emu.set_reg(0, 2);
    emu.execute(ins, index);

    EXPECT_EQ(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), 2);
}

TEST_F(InstructionExecute, SNE_VX_BYTE)
{
    emu.set_reg(0, 5);

    auto old_PC = emu.get_PC();
    Instruction ins = 0x4010;

    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_NE(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), 2);

    old_PC = emu.get_PC();
    emu.set_reg(0, 0x10);
    emu.execute(ins, index);

    EXPECT_EQ(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), 2);
}

TEST_F(InstructionExecute, SE_VX_VY)
{
    emu.set_reg(0, 5);
    emu.set_reg(1, 5);

    auto old_PC = emu.get_PC();
    Instruction ins = 0x5010;

    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_NE(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), 2);

    old_PC = emu.get_PC();
    emu.set_reg(1, 6);
    emu.execute(ins, index);

    EXPECT_EQ(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), 2);
}

TEST_F(InstructionExecute, LD_VX_BYTE)
{
    Instruction ins = 0x6034;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 0x34);
}

TEST_F(InstructionExecute, ADD_VX_BYTE)
{
    emu.set_reg(0, 1);

    Instruction ins = 0x7034;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 0x34 + 0x1);
}

TEST_F(InstructionExecute, LD_VX_VY)
{
    emu.set_reg(1, 5);

    Instruction ins = 0x8010;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 5);
    EXPECT_EQ(emu.get_register(1), 5);
}

TEST_F(InstructionExecute, OR_VX_VY)
{
    emu.set_reg(0, 1);
    emu.set_reg(1, 2);

    Instruction ins = 0x8011;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 1 | 2);
    EXPECT_EQ(emu.get_register(1), 2);
}

TEST_F(InstructionExecute, AND_VX_VY)
{
    emu.set_reg(0, 0b1110);
    emu.set_reg(1, 0b1100);

    Instruction ins = 0x8012;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 0b1110 & 0b1100);
    EXPECT_EQ(emu.get_register(1), 0b1100);
}

TEST_F(InstructionExecute, XOR_VX_VY)
{
    emu.set_reg(0, 0b1110);
    emu.set_reg(1, 0b1100);

    Instruction ins = 0x8013;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 0b1110 ^ 0b1100);
    EXPECT_EQ(emu.get_register(1), 0b1100);
}

TEST_F(InstructionExecute, ADD_VX_VY)
{
    emu.set_reg(0, 3);
    emu.set_reg(1, 7);

    Instruction ins = 0x8014;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 3 + 7);
    EXPECT_EQ(emu.get_register(1), 7);
}

TEST_F(InstructionExecute, ADD_VX_VY_VF_CARRY)
{
    emu.set_reg(0, 200);
    emu.set_reg(1, 250);

    Instruction ins = 0x8014;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), (200 + 250) & 0xFF);
    EXPECT_EQ(emu.get_register(0xF), 1);
}

TEST_F(InstructionExecute, SUB_VX_VY)
{
    emu.set_reg(0, 10);
    emu.set_reg(1, 7);

    Instruction ins = 0x8015;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), 10 - 7);
    EXPECT_EQ(emu.get_register(1), 7);
    EXPECT_EQ(emu.get_register(0xF), 1);
}

TEST_F(InstructionExecute, SUB_VX_VY_UNDERFLOW)
{
    u8 x = 7;
    u8 y = 10;
    u8 z = x - y;

    emu.set_reg(0, x);
    emu.set_reg(1, y);

    Instruction ins = 0x8015;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), z);
    EXPECT_EQ(emu.get_register(1), y);
    EXPECT_EQ(emu.get_register(0xF), 0);
}

TEST_F(InstructionExecute, SHR_VX_VY_VF_SET)
{
    u8 x = 8;

    emu.set_reg(0, x);

    Instruction ins = 0x8016;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), x >> 1);
    EXPECT_EQ(emu.get_register(0xF), 0);
}

TEST_F(InstructionExecute, SHR_VX_VY_VF_NOT_SET)
{
    u8 x = 9;

    emu.set_reg(0, x);

    Instruction ins = 0x8016;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), x >> 1);
    EXPECT_EQ(emu.get_register(0xF), 1);
}

TEST_F(InstructionExecute, SUBN_VX_VY_X_GT_Y)
{
    u8 x = 10;
    u8 y = 7;
    u8 z = y - x;

    emu.set_reg(0, x);
    emu.set_reg(1, y);

    Instruction ins = 0x8017;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), z);
    EXPECT_EQ(emu.get_register(1), y);
    EXPECT_EQ(emu.get_register(0xF), 0);
}

TEST_F(InstructionExecute, SUBN_VX_VY_Y_GT_X)
{
    u8 x = 7;
    u8 y = 10;
    u8 z = y - x;

    emu.set_reg(0, x);
    emu.set_reg(1, y);

    Instruction ins = 0x8017;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), z);
    EXPECT_EQ(emu.get_register(1), y);
    EXPECT_EQ(emu.get_register(0xF), 1);
}

TEST_F(InstructionExecute, SHL_VX_VY_VF_SET)
{
    u8 x = 0b10010010;
    u8 result = u8(x << 1);

    emu.set_reg(0, x);

    Instruction ins = 0x801E;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), result);
    EXPECT_EQ(emu.get_register(0xF), 1);
}

TEST_F(InstructionExecute, SHL_VX_VY_VF_NOT_SET)
{
    u8 x = 0b00010010;
    u8 result = u8(x << 1);

    emu.set_reg(0, x);

    Instruction ins = 0x801E;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), result);
    EXPECT_EQ(emu.get_register(0xF), 0);
}

TEST_F(InstructionExecute, SNE_VX_VY_EQUAL)
{
    u8 x = 0xFA;
    u8 y = 0xFA;

    emu.set_reg(0, x);
    emu.set_reg(1, y);

    auto old_pc = emu.get_PC();

    Instruction ins = 0x9010;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), emu.get_register(1));
    EXPECT_EQ(old_pc, emu.get_PC());
}

TEST_F(InstructionExecute, SNE_VX_VY_NOT_EQUAL)
{
    u8 x = 0xFA;
    u8 y = 0xC2;

    emu.set_reg(0, x);
    emu.set_reg(1, y);

    auto old_pc = emu.get_PC();

    Instruction ins = 0x9010;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_NE(emu.get_register(0), emu.get_register(1));
    EXPECT_EQ(old_pc + PCIncrement, emu.get_PC());
    EXPECT_NE(old_pc, emu.get_PC());
}

TEST_F(InstructionExecute, LD_I_ADDR)
{
    u16 nnn = 0x0FAC;

    Instruction ins = 0xA000 | nnn;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_Ireg(), nnn);
}


TEST_F(InstructionExecute, JP_V0_ADDR)
{
    u16 nnn = 0x0FAC;
    u8 x = 0x10;

    emu.set_reg(0, x);

    Instruction ins = 0xB000 | nnn;
    auto index = InstructionDecoder::decode(ins);
    auto old_PC = emu.get_PC();
    emu.execute(ins, index);


    EXPECT_NE(old_PC, emu.get_PC());
    EXPECT_EQ(emu.get_PC(), emu.get_register(0) + nnn);
}

// This only works because RNG uses a fixed seed.
TEST_F(InstructionExecute, RND_VX_BYTE)
{
    RNG rng;

    u8 kk = 0x44;
    u8 rand = rng.rand();

    Instruction ins = 0xC000 | kk;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), kk & rand);
}


TEST_F(InstructionExecute, LD_VX_DT)
{
    u8 DT = 60;

    emu.set_DTreg(DT);

    Instruction ins = 0xF007;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), DT);
}

TEST_F(InstructionExecute, LD_DT_VX)
{
    u8 DT = 60;
    u8 x = 10;

    emu.set_DTreg(DT);
    emu.set_reg(0, x);

    Instruction ins = 0xF015;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), x);
    EXPECT_EQ(emu.get_DTreg(), x);
}

TEST_F(InstructionExecute, LD_ST_VX)
{
    u8 ST = 60;
    u8 x = 10;

    emu.set_STreg(ST);
    emu.set_reg(0, x);

    Instruction ins = 0xF018;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), x);
    EXPECT_EQ(emu.get_STreg(), x);
}

TEST_F(InstructionExecute, ADD_I_VX)
{
    u8 x = 0x10;
    u16 Ireg = 0x34;

    emu.set_reg(0, x);
    emu.set_Ireg(Ireg);

    Instruction ins = 0xF01E;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    EXPECT_EQ(emu.get_register(0), x);
    EXPECT_EQ(emu.get_Ireg(), Ireg + x);
}

TEST_F(InstructionExecute, LD_B_VX)
{
    u8 x = 249;

    emu.set_reg(0, x);

    Instruction ins = 0xF033;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    auto mem = emu.get_mem();
    u8 buffer[3];

    mem.read(emu.get_Ireg(), 3, buffer);

    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 9);
}

TEST_F(InstructionExecute, LD_I_VX)
{
    u8 values[15] = {0, 19, 29, 9, 3, 9, 100, 184, 29, 18, 1, 2, 3, 4, 10};

    emu.set_reg(0, values[0]);
    emu.set_reg(1, values[1]);
    emu.set_reg(2, values[2]);
    emu.set_reg(3, values[3]);
    emu.set_reg(4, values[4]);
    emu.set_reg(5, values[5]);
    emu.set_reg(6, values[6]);
    emu.set_reg(7, values[7]);
    emu.set_reg(8, values[8]);
    emu.set_reg(9, values[9]);
    emu.set_reg(10, values[10]);
    emu.set_reg(11, values[11]);
    emu.set_reg(12, values[12]);
    emu.set_reg(13, values[13]);
    emu.set_reg(14, values[14]);

    u16 addr = 0x244;
    emu.set_Ireg(addr);

    Instruction ins = 0xFE55;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);

    auto mem = emu.get_mem();
    u8 buffer[15];

    mem.read(emu.get_Ireg(), 15, buffer);

    EXPECT_EQ(buffer[0], emu.get_register(0));
    EXPECT_EQ(buffer[1], emu.get_register(1));
    EXPECT_EQ(buffer[2], emu.get_register(2));
    EXPECT_EQ(buffer[3], emu.get_register(3));
    EXPECT_EQ(buffer[4], emu.get_register(4));
    EXPECT_EQ(buffer[5], emu.get_register(5));
    EXPECT_EQ(buffer[6], emu.get_register(6));
    EXPECT_EQ(buffer[7], emu.get_register(7));
    EXPECT_EQ(buffer[8], emu.get_register(8));
    EXPECT_EQ(buffer[9], emu.get_register(9));
    EXPECT_EQ(buffer[10], emu.get_register(10));
    EXPECT_EQ(buffer[11], emu.get_register(11));
    EXPECT_EQ(buffer[12], emu.get_register(12));
    EXPECT_EQ(buffer[13], emu.get_register(13));
    EXPECT_EQ(buffer[14], emu.get_register(14));
}

TEST_F(InstructionExecute, LD_VX_I)
{
    u8 values[15] = {0, 19, 29, 9, 3, 9, 100, 184, 29, 18, 1, 2, 3, 4, 10};

    u16 addr = 0x244;
    emu.set_Ireg(addr);

    auto& mem = emu.get_mem();
    mem.write(emu.get_Ireg(), values, 15);

    Instruction ins = 0xFE65;
    auto index = InstructionDecoder::decode(ins);
    emu.execute(ins, index);


    EXPECT_EQ(values[0], emu.get_register(0));
    EXPECT_EQ(values[1], emu.get_register(1));
    EXPECT_EQ(values[2], emu.get_register(2));
    EXPECT_EQ(values[3], emu.get_register(3));
    EXPECT_EQ(values[4], emu.get_register(4));
    EXPECT_EQ(values[5], emu.get_register(5));
    EXPECT_EQ(values[6], emu.get_register(6));
    EXPECT_EQ(values[7], emu.get_register(7));
    EXPECT_EQ(values[8], emu.get_register(8));
    EXPECT_EQ(values[9], emu.get_register(9));
    EXPECT_EQ(values[10], emu.get_register(10));
    EXPECT_EQ(values[11], emu.get_register(11));
    EXPECT_EQ(values[12], emu.get_register(12));
    EXPECT_EQ(values[13], emu.get_register(13));
    EXPECT_EQ(values[14], emu.get_register(14));
}