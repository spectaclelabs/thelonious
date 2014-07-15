#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/multichannel/split.h"

using namespace thelonious;
using namespace thelonious::dsp::multichannel;
using namespace testing;

TEST(SplitTest, Simple21) {
    Block<2> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);

    SplitN<2, 1> split;
    split.tickIn(inBlock);

    Block<1> outBlock;
    split.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));

    split.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(2.f)));

    split.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(0.f)));
}

TEST(SplitTest, Tricky52) {
    Block<5> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    inBlock[2].fill(3.f);
    inBlock[3].fill(4.f);
    inBlock[4].fill(5.f);

    SplitN<5, 2> split;
    split.tickIn(inBlock);

    Block<2> outBlock;
    split.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(2.f)));

    split.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(3.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(4.f)));

    split.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(5.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(0.f)));
}
