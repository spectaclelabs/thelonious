#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/dsp/oscillators/constant.h"
#include "thelonious/dsl/constant.h"
#include "thelonious/dsl/unit.h"
#include "thelonious/source.h"
#include "thelonious/duplex.h"

using namespace thelonious;
using namespace testing;

class ConstantSourceTest : public Test {
public:
    ConstantSourceTest() : zeros(0.f), ones(1.f), twos(2.f) {}

    thelonious::dsp::oscillators::ConstantN<2> zeros;
    thelonious::dsp::oscillators::ConstantN<2> ones;
    thelonious::dsp::oscillators::ConstantN<2> twos;
    Block<2> block;
};

TEST_F(ConstantSourceTest, AddLValue) {
    (ones + 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(ConstantSourceTest, AddLValue2) {
    (2.f + ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(ConstantSourceTest, AddRValue) {
    ((ones + ones) + 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, AddRValue2) {
    (2.f + (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, SubtractLValue) {
    (ones - 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(-1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(-1.f)));
}

TEST_F(ConstantSourceTest, SubtractLValue2) {
    (2.f - ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, SubtractRValue) {
    ((ones + ones) - 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, SubtractRValue2) {
    (2.f - (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}


TEST_F(ConstantSourceTest, MultiplyLValue) {
    (ones * 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(ConstantSourceTest, MultiplyLValue2) {
    (2.f * ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(ConstantSourceTest, MultiplyRValue) {
    ((ones + ones) * 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, MultiplyRValue2) {
    (2.f * (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, DivideLValue) {
    (ones / 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(ConstantSourceTest, DivideLValue2) {
    (1.f / twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(ConstantSourceTest, DivideRValue) {
    ((ones + ones) / 8.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.25f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.25f)));
}

TEST_F(ConstantSourceTest, DivideRValue2) {
    (3.f / (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(ConstantSourceTest, ModuloLValue) {
    (ones % 0.4f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.2f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.2f)));
}

TEST_F(ConstantSourceTest, ModuloLValue2) {
    (1.3f % ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.3f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.3f)));
}

TEST_F(ConstantSourceTest, ModuloRValue) {
    ((ones + ones) % 1.5f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(ConstantSourceTest, ModuloRValue2) {
    (3.f % (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, EqualLValue) {
    (ones == 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, EqualLValue2) {
    (2.f == ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, EqualRValue) {
    ((ones + ones) == 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, EqualRValue2) {
    (3.f == (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, NotEqualLValue) {
    (ones != 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, NotEqualLValue2) {
    (2.f != ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, NotEqualRValue) {
    ((ones + ones) != 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, NotEqualRValue2) {
    (3.f != (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LTLValue) {
    (ones < 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, LTLValue2) {
    (2.f < ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, LTRValue) {
    ((ones + ones) < 3.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LTRValue2) {
    (3.f < (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}


TEST_F(ConstantSourceTest, GTLValue) {
    (ones > 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, GTLValue2) {
    (2.f > ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, GTRValue) {
    ((ones + ones) > 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, GTRValue2) {
    (3.f > (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}


TEST_F(ConstantSourceTest, LTELValue) {
    (ones <= 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LTELValue2) {
    (2.f <= ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, LTERValue) {
    ((ones + ones) <= 2.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LTERValue2) {
    (3.f <= (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, GTELValue) {
    (ones >= 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, GTELValue2) {
    (2.f >= ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, GTERValue) {
    ((ones + ones) >= 3.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, GTERValue2) {
    (3.f >= (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LogicalAndLValue) {
    (ones && 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LogicalAndLValue2) {
    (0.f && ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, LogicalAndRValue) {
    ((zeros + zeros) && 3.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, LogicalAndRValue2) {
    (3.f && (ones + zeros)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LogicalOrLValue) {
    (ones || 1.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LogicalOrLValue2) {
    (0.f || ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, LogicalOrRValue) {
    ((zeros + zeros) || 0.f).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, LogicalOrRValue2) {
    (0.f || (ones + zeros)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}
