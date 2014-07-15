#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/multichannel/merge.h"

using namespace thelonious;
using namespace thelonious::dsp::multichannel;
using namespace testing;

TEST(MergeTest, Simple12) {
    Block<1> inBlock;
    MergeN<1, 2> merge;

    inBlock[0].fill(1.f);
    merge.tickIn(inBlock);
    inBlock[0].fill(2.f);
    merge.tickIn(inBlock);

    Block<2> outBlock;
    merge.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(2.f)));
}

TEST(MergeTest, Tricky25Full) {
    Block<2> inBlock;
    MergeN<2, 5> merge;

    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    merge.tickIn(inBlock);

    inBlock[0].fill(3.f);
    inBlock[1].fill(4.f);
    merge.tickIn(inBlock);

    inBlock[0].fill(5.f);
    inBlock[1].fill(6.f);
    merge.tickIn(inBlock);

    Block<5> outBlock;
    merge.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(2.f)));
    ASSERT_THAT(outBlock[2], Each(FloatEq(3.f)));
    ASSERT_THAT(outBlock[3], Each(FloatEq(4.f)));
    ASSERT_THAT(outBlock[4], Each(FloatEq(5.f)));
}

TEST(MergeTest, Tricky25Empty) {
    Block<2> inBlock;
    MergeN<2, 5> merge;

    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    merge.tickIn(inBlock);

    inBlock[0].fill(3.f);
    inBlock[1].fill(4.f);
    merge.tickIn(inBlock);

    Block<5> outBlock;
    merge.tickOut(outBlock);
    ASSERT_THAT(outBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(2.f)));
    ASSERT_THAT(outBlock[2], Each(FloatEq(3.f)));
    ASSERT_THAT(outBlock[3], Each(FloatEq(4.f)));
    ASSERT_THAT(outBlock[4], Each(FloatEq(0.f)));
}
