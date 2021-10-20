#include "gtest/gtest.h"
#include "gtest/gtest-death-test.h"

#include "util/bits.hpp"

using namespace momo;

TEST(ToggleBitRange, ValidInput)
{

    u16 x1 = toggle_bit_range(1, 4);
    u16 x1_target = 0xF;

    EXPECT_EQ(x1, x1_target);

    u16 x2 = toggle_bit_range(1, 16);
    u16 x2_target = 0xFFFF;

    EXPECT_EQ(x2, x2_target);

    u16 x3 = toggle_bit_range(1, 1);
    u16 x3_target = 0x1;

    EXPECT_EQ(x3, x3_target);
}

TEST(ToggleBitRange, ToSmallerThanFrom)
{
    EXPECT_DEATH(toggle_bit_range(4, 0), "");
    EXPECT_DEATH(toggle_bit_range(16, 14), "");
    EXPECT_DEATH(toggle_bit_range(7, 3), "");
}

TEST(ToggleBitRange, FromOutOfRange) { EXPECT_DEATH(toggle_bit_range(0, 16), ""); }

TEST(ToggleBitRange, ToOutOfRange) { EXPECT_DEATH(toggle_bit_range(1, 17), ""); }

TEST(ByteSwap, ValidInput)
{
    u16 x1 = 0xE000;
    u16 x1_target = 0x00E0;

    EXPECT_EQ(byte_swap(x1), x1_target);

    u16 x2 = 0x1100;
    u16 x2_target = 0x0011;

    EXPECT_EQ(byte_swap(x2), x2_target);
}