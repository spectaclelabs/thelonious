#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/types.h"
#include "thelonious/dsp/multichannel/multiselect.h"

using namespace thelonious;
using namespace thelonious::dsp::multichannel;
using namespace testing;

TEST(MultiSelectTest, InitializeWithValues) {
    MultiSelectN<0, 5> select({7.f, 2.f, 1.f, 3.f, 3.f});
    ASSERT_THAT(select.channels[0].get(), Each(FloatEq(7.f)));
    ASSERT_THAT(select.channels[1].get(), Each(FloatEq(2.f)));
    ASSERT_THAT(select.channels[2].get(), Each(FloatEq(1.f)));
    ASSERT_THAT(select.channels[3].get(), Each(FloatEq(3.f)));
    ASSERT_THAT(select.channels[4].get(), Each(FloatEq(3.f)));
}

TEST(MultiSelectTest, InitializeNoValues) {
    MultiSelectN<0, 5> select;
    ASSERT_THAT(select.channels[0].get(), Each(FloatEq(0.f)));
    ASSERT_THAT(select.channels[1].get(), Each(FloatEq(1.f)));
    ASSERT_THAT(select.channels[2].get(), Each(FloatEq(2.f)));
    ASSERT_THAT(select.channels[3].get(), Each(FloatEq(3.f)));
    ASSERT_THAT(select.channels[4].get(), Each(FloatEq(4.f)));
}

TEST(MultiSelectTest, SelectOne) {
    Block<2> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);

    Block<1> outBlock;

    MultiSelectN<2, 1> select({1.f});

    select.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(2.f)));
}

TEST(MultiSelectTest, SelectMultiple) {
    Block<3> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    inBlock[2].fill(3.f);

    Block<2> outBlock;

    MultiSelectN<3, 2> select({2.f, 0.f});

    select.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(3.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(1.f)));
}

TEST(MultiSelectTest, SelectOutside) {
    Block<3> inBlock;
    inBlock[0].fill(1.f);
    inBlock[1].fill(2.f);
    inBlock[2].fill(3.f);

    Block<2> outBlock;

    MultiSelectN<3, 2> select({1.f, 5.f});

    select.tick(inBlock, outBlock);

    ASSERT_THAT(outBlock[0], Each(FloatEq(2.f)));
    ASSERT_THAT(outBlock[1], Each(FloatEq(0.f)));
}
