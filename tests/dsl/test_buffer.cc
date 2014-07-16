#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/dsl/buffer.h"

using namespace thelonious;
using namespace testing;

class BufferTest : public Test {
public:
    void SetUp() {
        for (uint32_t i=0; i<2; i++) {
            zeros[i].fill(0.f);
            ones[i].fill(1.f);
            twos[i].fill(2.f);
            threes[i].fill(3.f);
        }
    }

    Block<2> zeros;
    Block<2> ones;
    Block<2> twos;
    Block<2> threes;
};


TEST_F(BufferTest, AddBuffer) {
    Block<2> block = ones + twos;
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(BufferTest, AddSample) {
    Block<2> block = ones + 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(BufferTest, AddSample2) {
    Block<2> block = 2.f + ones;
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(BufferTest, AddAssignBuffer) {
    Block<2> block = ones;
    block += twos;
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(BufferTest, AddAssignSample) {
    Block<2> block = ones;
    block += 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(BufferTest, SubtractBuffer) {
    Block<2> block = threes - twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, SubtractSample) {
    Block<2> block = threes - 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, SubtractSample2) {
    Block<2> block = 3.f - twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, SubtractAssignBuffer) {
    Block<2> block = threes;
    block -= twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, SubtractAssignSample) {
    Block<2> block = threes;
    block -= 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, MultiplyBuffer) {
    Block<2> block = twos * threes;
    ASSERT_THAT(block[0], Each(FloatEq(6.f)));
    ASSERT_THAT(block[1], Each(FloatEq(6.f)));
}

TEST_F(BufferTest, MultiplySample) {
    Block<2> block = twos * 3.f;
    ASSERT_THAT(block[0], Each(FloatEq(6.f)));
    ASSERT_THAT(block[1], Each(FloatEq(6.f)));
}

TEST_F(BufferTest, MultiplySample2) {
    Block<2> block = 3.f * twos;
    ASSERT_THAT(block[0], Each(FloatEq(6.f)));
    ASSERT_THAT(block[1], Each(FloatEq(6.f)));
}

TEST_F(BufferTest, MultiplyAssignBuffer) {
    Block<2> block = threes;
    block *= twos;
    ASSERT_THAT(block[0], Each(FloatEq(6.f)));
    ASSERT_THAT(block[1], Each(FloatEq(6.f)));
}

TEST_F(BufferTest, MultiplyAssignSample) {
    Block<2> block = threes;
    block *= 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(6.f)));
    ASSERT_THAT(block[1], Each(FloatEq(6.f)));
}

TEST_F(BufferTest, DivideBuffer) {
    Block<2> block = threes / twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(BufferTest, DivideSample) {
    Block<2> block = threes / 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(BufferTest, DivideSample2) {
    Block<2> block = 3.f / twos ;
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(BufferTest, DivideAssignBuffer) {
    Block<2> block = threes;
    block /= twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(BufferTest, DivideAssignSample) {
    Block<2> block = threes;
    block /= 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(BufferTest, ModuloBuffer) {
    Block<2> block = threes % twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, ModuloSample) {
    Block<2> block = threes % 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, ModuloSample2) {
    Block<2> block = 3.f % twos ;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, ModuloAssignBuffer) {
    Block<2> block = threes;
    block %= twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, ModuloAssignSample) {
    Block<2> block = threes;
    block %= 2.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, UnaryPlus) {
    Block<2> block = +threes;
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(BufferTest, UnaryMinus) {
    Block<2> block = -threes;
    ASSERT_THAT(block[0], Each(FloatEq(-3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(-3.f)));
}

TEST_F(BufferTest, EqualBuffer) {
    Block<2> block = threes == twos;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, EqualSample) {
    Block<2> block = threes == 3.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, EqualSample2) {
    Block<2> block = 3.f == twos ;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, NotEqualBuffer) {
    Block<2> block = threes != twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, NotEqualSample) {
    Block<2> block = threes != 3.f;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, NotEqualSample2) {
    Block<2> block = 3.f != twos ;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LTBuffer) {
    Block<2> block = threes < twos;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, LTSample) {
    Block<2> block = threes < 4.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LTSample2) {
    Block<2> block = 3.f < twos ;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, GTBuffer) {
    Block<2> block = threes > twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, GTSample) {
    Block<2> block = threes > 3.f;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, GTSample2) {
    Block<2> block = 3.f > twos ;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LTEBuffer) {
    Block<2> block = threes <= twos;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, LTEEqualSample) {
    Block<2> block = threes <= 3.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LTESample2) {
    Block<2> block = 3.f <= twos ;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, GTEBuffer) {
    Block<2> block = threes >= twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, GTESample) {
    Block<2> block = threes >= 3.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, GTEESample2) {
    Block<2> block = 3.f >= twos ;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LogicalNot) {
    Block<2> block = !threes;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, LogicalAndBuffer) {
    Block<2> block = threes && twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LogicalAndSample) {
    Block<2> block = threes && 0.f;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, LogicalAndSample2) {
    Block<2> block = 3.f && zeros;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(BufferTest, LogicalOrBuffer) {
    Block<2> block = threes || twos;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LogicalOrSample) {
    Block<2> block = threes || 0.f;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(BufferTest, LogicalOrSample2) {
    Block<2> block = 0.f || zeros;
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}
