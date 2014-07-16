#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/multichannel/downmix.h"

using namespace thelonious;
using namespace thelonious::dsp::multichannel;
using namespace testing;

TEST(UpMixTest, Simple21) {
    Block<2> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);

    Block<1> outBlock;

    DownMixN<2, 1> downmix;
    downmix.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(3.f)));
}

TEST(UpMixTest, Complex52) {
    Block<5> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    inBlock[2].fill(3.f);
    inBlock[3].fill(4.f);
    inBlock[4].fill(5.f);

    Block<2> outBlock;

    DownMixN<5, 2> downmix;

    downmix.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(9.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(6.f)));
}

