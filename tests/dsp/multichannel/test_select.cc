#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/multichannel/select.h"

using namespace thelonious;
using namespace thelonious::dsp::multichannel;
using namespace testing;

TEST(SelectTest, Simple21) {
    Block<2> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);

    Block<1> outBlock;

    SelectN<2, 1> select;
    select.channel.set(1.f);

    select.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(2.f)));
}

TEST(SelectTest, Under32) {
    Block<3> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    inBlock[2].fill(3.f);

    Block<2> outBlock;

    SelectN<3, 2> select;
    select.channel.set(1.f);

    select.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(2.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(3.f)));
}

TEST(SelectTest, Over32) {
    Block<3> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    inBlock[2].fill(3.f);

    Block<2> outBlock;

    SelectN<3, 2> select;
    select.channel.set(2.f);

    select.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(3.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(0.f)));
}
