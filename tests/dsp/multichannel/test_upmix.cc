#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/multichannel/upmix.h"

using namespace thelonious;
using namespace thelonious::dsp::multichannel;
using namespace testing;

TEST(UpMixTest, Simple12) {
    Block<1> inBlock;
    inBlock[0].fill(1.f);

    Block<2> outBlock;

    UpMixN<1, 2> upmix;
    upmix.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(1.f)));
}

TEST(UpMixTest, Complex25) {
    Block<2> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);

    Block<5> outBlock;

    UpMixN<2, 5> upmix;

    upmix.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(2.f)));
    ASSERT_THAT(outBlock[2], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[3], Each(FloatEq(2.f)));
    ASSERT_THAT(outBlock[4], Each(FloatEq(1.f)));
}

