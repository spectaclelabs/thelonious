#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/oscillators/silence.h"

using namespace thelonious;
using namespace thelonious::dsp::oscillators;
using namespace testing;

TEST(SilenceTest, Silence) {
    Block<2> block;
    SilenceN<2> silence;
    silence.tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

