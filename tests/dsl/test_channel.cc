#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/dsl/channel.h"

using namespace thelonious;
using namespace testing;

class ChannelTest : public Test {
public:
    void SetUp() {
        zeros.fill(0.f);
        ones.fill(1.f);
        twos.fill(2.f);
        threes.fill(3.f);
    }

    Chock zeros;
    Chock ones;
    Chock twos;
    Chock threes;
};


TEST_F(ChannelTest, AddChannel) {
    Chock chock = ones + twos;
    ASSERT_THAT(chock, Each(FloatEq(3.f)));
}

TEST_F(ChannelTest, AddSample) {
    Chock chock = ones + 2.f;
    ASSERT_THAT(chock, Each(FloatEq(3.f)));
}

TEST_F(ChannelTest, AddSample2) {
    Chock chock = 2.f + ones;
    ASSERT_THAT(chock, Each(FloatEq(3.f)));
}

TEST_F(ChannelTest, AddAssignChannel) {
    Chock chock = ones;
    chock += twos;
    ASSERT_THAT(chock, Each(FloatEq(3.f)));
}

TEST_F(ChannelTest, AddAssignSample) {
    Chock chock = ones;
    chock += 2.f;
    ASSERT_THAT(chock, Each(FloatEq(3.f)));
}

TEST_F(ChannelTest, SubtractChannel) {
    Chock chock = threes - twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, SubtractSample) {
    Chock chock = threes - 2.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, SubtractSample2) {
    Chock chock = 3.f - twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, SubtractAssignChannel) {
    Chock chock = threes;
    chock -= twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, SubtractAssignSample) {
    Chock chock = threes;
    chock -= 2.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, MultiplyChannel) {
    Chock chock = twos * threes;
    ASSERT_THAT(chock, Each(FloatEq(6.f)));
}

TEST_F(ChannelTest, MultiplySample) {
    Chock chock = twos * 3.f;
    ASSERT_THAT(chock, Each(FloatEq(6.f)));
}

TEST_F(ChannelTest, MultiplySample2) {
    Chock chock = 3.f * twos;
    ASSERT_THAT(chock, Each(FloatEq(6.f)));
}

TEST_F(ChannelTest, MultiplyAssignChannel) {
    Chock chock = threes;
    chock *= twos;
    ASSERT_THAT(chock, Each(FloatEq(6.f)));
}

TEST_F(ChannelTest, MultiplyAssignSample) {
    Chock chock = threes;
    chock *= 2.f;
    ASSERT_THAT(chock, Each(FloatEq(6.f)));
}

TEST_F(ChannelTest, DivideChannel) {
    Chock chock = threes / twos;
    ASSERT_THAT(chock, Each(FloatEq(1.5f)));
}

TEST_F(ChannelTest, DivideSample) {
    Chock chock = threes / 2.f;
    ASSERT_THAT(chock, Each(FloatEq(1.5f)));
}

TEST_F(ChannelTest, DivideSample2) {
    Chock chock = 3.f / twos ;
    ASSERT_THAT(chock, Each(FloatEq(1.5f)));
}

TEST_F(ChannelTest, DivideAssignChannel) {
    Chock chock = threes;
    chock /= twos;
    ASSERT_THAT(chock, Each(FloatEq(1.5f)));
}

TEST_F(ChannelTest, DivideAssignSample) {
    Chock chock = threes;
    chock /= 2.f;
    ASSERT_THAT(chock, Each(FloatEq(1.5f)));
}

TEST_F(ChannelTest, ModuloChannel) {
    Chock chock = threes % twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, ModuloSample) {
    Chock chock = threes % 2.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, ModuloSample2) {
    Chock chock = 3.f % twos ;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, ModuloAssignChannel) {
    Chock chock = threes;
    chock %= twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, ModuloAssignSample) {
    Chock chock = threes;
    chock %= 2.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, UnaryPlus) {
    Chock chock = +ones ;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, UnaryMinus) {
    Chock chock = -ones ;
    ASSERT_THAT(chock, Each(FloatEq(-1.f)));
}

TEST_F(ChannelTest, EqualChannel) {
    Chock chock = threes == twos;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, EqualSample) {
    Chock chock = threes == 3.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, EqualSample2) {
    Chock chock = 3.f == twos ;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, NotEqualChannel) {
    Chock chock = threes != twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, NotEqualSample) {
    Chock chock = threes != 3.f;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, NotEqualSample2) {
    Chock chock = 3.f != twos ;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LTChannel) {
    Chock chock = threes < twos;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, LTSample) {
    Chock chock = threes < 4.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LTSample2) {
    Chock chock = 3.f < twos ;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}


TEST_F(ChannelTest, GTChannel) {
    Chock chock = threes > twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, GTSample) {
    Chock chock = threes > 3.f;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, GTSample2) {
    Chock chock = 3.f > twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LTEChannel) {
    Chock chock = threes <= twos;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, LTESample) {
    Chock chock = threes <= 3.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LTESample2) {
    Chock chock = 3.f <= twos ;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, GTEChannel) {
    Chock chock = threes >= twos;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, GTESample) {
    Chock chock = threes >= 3.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, GTESample2) {
    Chock chock = 1.f >= twos ;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, LogicalNot) {
    Chock chock = !ones ;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, LogicalAndChannel) {
    Chock chock = ones && zeros;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}

TEST_F(ChannelTest, LogicalAndSample) {
    Chock chock = ones && 1.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LogicalAndSample2) {
    Chock chock = 1.f && ones;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LogicalOrChannel) {
    Chock chock = ones || zeros;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LogicalOrSample) {
    Chock chock = ones || 1.f;
    ASSERT_THAT(chock, Each(FloatEq(1.f)));
}

TEST_F(ChannelTest, LogicalOrSample2) {
    Chock chock = 0.f || zeros;
    ASSERT_THAT(chock, Each(FloatEq(0.f)));
}
