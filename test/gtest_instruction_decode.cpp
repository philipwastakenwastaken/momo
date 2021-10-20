#include "gtest/gtest.h"

#include "emu/instruction_decoder.hpp"
#include "emu/instruction_fetcher.hpp"
#include "emu/specs.hpp"

using namespace momo;

TEST(InstructionDecoding, CLS)
{
    Instruction ins = 0x00E0;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("CLS"));
}

TEST(InstructionDecoding, RET)
{
    Instruction ins = 0x00EE;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("RET"));
}

TEST(InstructionDecoding, SYS_ADDR)
{
    Instruction ins = 0x0EFF;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SYS addr"));
}

TEST(InstructionDecoding, JP_ADDR)
{
    Instruction ins = 0x1455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("JP addr"));
}

TEST(InstructionDecoding, CALL_ADDR)
{
    Instruction ins = 0x2455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("CALL addr"));
}

TEST(InstructionDecoding, SE_VX_BYTE)
{
    Instruction ins = 0x3455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SE Vx, byte"));
}

TEST(InstructionDecoding, SNE_VX_BYTE)
{
    Instruction ins = 0x4455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SNE Vx, byte"));
}

TEST(InstructionDecoding, SE_VX_VY)
{
    Instruction ins = 0x5450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SE Vx, Vy"));
}

TEST(InstructionDecoding, LD_VX_BYTE)
{
    Instruction ins = 0x6F78;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD Vx, byte"));
}

TEST(InstructionDecoding, ADD_VX_BYTE)
{
    Instruction ins = 0x7455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("ADD Vx, byte"));
}

TEST(InstructionDecoding, LD_VX_VY)
{
    Instruction ins = 0x8450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD Vx, Vy"));
}

TEST(InstructionDecoding, OR_VX_VY)
{
    Instruction ins = 0x8451;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("OR Vx, Vy"));
}

TEST(InstructionDecoding, AND_VX_VY)
{
    Instruction ins = 0x8452;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("AND Vx, Vy"));
}

TEST(InstructionDecoding, XOR_VX_VY)
{
    Instruction ins = 0x8453;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("XOR Vx, Vy"));
}

TEST(InstructionDecoding, ADD_VX_VY)
{
    Instruction ins = 0x8454;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("ADD Vx, Vy"));
}

TEST(InstructionDecoding, SUB_VX_VY)
{
    Instruction ins = 0x8455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SUB Vx, Vy"));
}

TEST(InstructionDecoding, SHR_VX_VY)
{
    Instruction ins = 0x8456;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SHR Vx {, Vy}"));
}

TEST(InstructionDecoding, SUBN_VX_VY)
{
    Instruction ins = 0x8457;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SUBN Vx, Vy"));
}

TEST(InstructionDecoding, SHL_VX_VY)
{
    Instruction ins = 0x845E;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SHL Vx {, Vy}"));
}

TEST(InstructionDecoding, SNE_VX_VY)
{
    Instruction ins = 0x9450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SNE Vx, Vy"));
}

TEST(InstructionDecoding, LD_I_ADDR)
{
    Instruction ins = 0xA450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD I, addr"));
}

TEST(InstructionDecoding, JP_V0_ADDR)
{
    Instruction ins = 0xB450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("JP V0, addr"));
}

TEST(InstructionDecoding, RND_VX_BYTE)
{
    Instruction ins = 0xC450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("RND Vx, byte"));
}

TEST(InstructionDecoding, DRW_VX_VY_NIBBLE)
{
    Instruction ins = 0xD450;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("DRW Vx, Vy, nibble"));
}

TEST(InstructionDecoding, SKP_VX)
{
    Instruction ins = 0xE49E;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SKP Vx"));
}

TEST(InstructionDecoding, SKNP_VX)
{
    Instruction ins = 0xE4A1;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("SKNP Vx"));
}

TEST(InstructionDecoding, LD_VX_DT)
{
    Instruction ins = 0xF407;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD Vx, DT"));
}

TEST(InstructionDecoding, LD_VX_K)
{
    Instruction ins = 0xF40A;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD Vx, K"));
}

TEST(InstructionDecoding, LD_DT_VX)
{
    Instruction ins = 0xF415;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD DT, Vx"));
}

TEST(InstructionDecoding, LD_ST_VX)
{
    Instruction ins = 0xF418;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD ST, Vx"));
}

TEST(InstructionDecoding, ADD_I_VX)
{
    Instruction ins = 0xF41E;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("ADD I, Vx"));
}

TEST(InstructionDecoding, LD_F_VX)
{
    Instruction ins = 0xF429;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD F, Vx"));
}

TEST(InstructionDecoding, LD_B_VX)
{
    Instruction ins = 0xF433;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD B, Vx"));
}

TEST(InstructionDecoding, LD_BRACKET_I_BRACKET_VX)
{
    Instruction ins = 0xF455;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD [I], Vx"));
}

TEST(InstructionDecoding, LD_VX_BRACKET_I_BRACKET)
{
    Instruction ins = 0xF465;

    InstructionIndex index = InstructionDecoder::decode(ins);

    EXPECT_EQ(index, find_instruction_index("LD Vx, [I]"));
}
