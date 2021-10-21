#include "gtest/gtest.h"
#include "gtest/gtest-death-test.h"

#include "core/hardware.hpp"
#include "core/log.hpp"
#include "core/core.hpp"

#include "emu/memory.hpp"

using namespace momo;

class MemoryTest : public ::testing::Test
{
  protected:
    void SetUp() override { mem = Memory(); }

    Memory mem;
};

TEST_F(MemoryTest, ReadSingleBytes)
{
    u8* data = mem.data();

    *data = 0x5A;
    *(data + 1) = 0x9C;
    *(data + 2) = 0xC2;

    u8 x1 = 0;
    mem.read(0x0, 1, reinterpret_cast<u8*>(&x1));

    u8 x2 = 0;
    mem.read(0x1, 1, reinterpret_cast<u8*>(&x2));

    u8 x3 = 0;
    mem.read(0x2, 1, reinterpret_cast<u8*>(&x3));

    EXPECT_EQ(*data, x1);
    EXPECT_EQ(*(data + 1), x2);
    EXPECT_EQ(*(data + 2), x3);
}

TEST_F(MemoryTest, ReadMultipleBytes)
{
    u8* data = mem.data();

    *data = 0x5A;
    *(data + 1) = 0x9C;
    *(data + 2) = 0xC2;
    *(data + 3) = 0xFF;

    u8 buffer[4];

    mem.read(0x0, 4, buffer);

    EXPECT_EQ(*data, buffer[0]);
    EXPECT_EQ(*(data + 1), buffer[1]);
    EXPECT_EQ(*(data + 2), buffer[2]);
    EXPECT_EQ(*(data + 3), buffer[3]);
}

TEST_F(MemoryTest, ReadZeroBytes)
{
    u8 buffer[1];
    EXPECT_DEATH(mem.read(0x0, 0, buffer), "");
}

TEST_F(MemoryTest, ReadAddressOverflow)
{
    u8 buffer[10];
    EXPECT_DEATH(mem.read(4090, 10, buffer), "");
}

TEST_F(MemoryTest, WriteSingleByte)
{
    u8* data = mem.data();

    u16 addr1 = 0x34;
    u16 addr2 = 0xFA;
    u16 addr3 = 0x87C;

    u8 write_data[3] = { 1, 10, 187 };

    mem.write(addr1, write_data, 1);
    mem.write(addr2, write_data + 1, 1);
    mem.write(addr3, write_data + 2, 1);

    EXPECT_EQ(*(data + addr1), write_data[0]);
    EXPECT_EQ(*(data + addr2), write_data[1]);
    EXPECT_EQ(*(data + addr3), write_data[2]);
}

TEST_F(MemoryTest, WriteAddressOverflow)
{
    u16 addr = 0x3FAC;

    u8 write_data = 3;
    EXPECT_DEATH(mem.write(addr, &write_data, 1), "");
}

TEST_F(MemoryTest, WriteZeroBytes)
{
    u16 addr = 0x3FAC;

    u8 write_data = 3;
    EXPECT_DEATH(mem.write(addr, &write_data, 0), "");
}

TEST_F(MemoryTest, WriteMultipleBytes)
{
    u8* data = mem.data();

    u16 addr = 0x34;

    u8 write_data[10] = { 1, 10, 187, 192, 28, 29, 1, 23, 0, 99 };

    mem.write(addr, write_data, 10);

    EXPECT_EQ(*(data + addr + 0), write_data[0]);
    EXPECT_EQ(*(data + addr + 1), write_data[1]);
    EXPECT_EQ(*(data + addr + 2), write_data[2]);
    EXPECT_EQ(*(data + addr + 3), write_data[3]);
    EXPECT_EQ(*(data + addr + 4), write_data[4]);
    EXPECT_EQ(*(data + addr + 5), write_data[5]);
    EXPECT_EQ(*(data + addr + 6), write_data[6]);
    EXPECT_EQ(*(data + addr + 7), write_data[7]);
    EXPECT_EQ(*(data + addr + 8), write_data[8]);
    EXPECT_EQ(*(data + addr + 9), write_data[9]);
}