#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/oscillators/constant.h"

using namespace thelonious;
using namespace thelonious::dsp::oscillators;
using namespace testing;

TEST(ConstantTest, Positive) {
    Block<2> block;
    ConstantN<2> constant(5.f);
    constant.tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(5.f)));
    ASSERT_THAT(block[1], Each(FloatEq(5.f)));
}

TEST(ConstantTest, Negative) {
    Block<2> block;
    ConstantN<2> constant(-0.5f);
    constant.tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(-0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(-0.5f)));
}

TEST(ConstantTest, Zero) {
    Block<2> block;
    ConstantN<2> constant(0.f);
    constant.tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}
