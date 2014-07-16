#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/dsp/oscillators/constant.h"
#include "thelonious/dsl/constant.h"
#include "thelonious/dsl/unit.h"
#include "thelonious/source.h"
#include "thelonious/duplex.h"

using namespace thelonious;
using namespace testing;

class TestUnit : public Test {
public:
    TestUnit() : zeros(0.f), ones(1.f), twos(2.f), threes(3.f) {}

    thelonious::dsp::oscillators::ConstantN<2> zeros;
    thelonious::dsp::oscillators::ConstantN<2> ones;
    thelonious::dsp::oscillators::ConstantN<2> twos;
    thelonious::dsp::oscillators::ConstantN<2> threes;
    Block<2> block;
};

TEST_F(TestUnit, AddLValue) {
    (ones + twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(TestUnit, AddRValue) {
    ((ones + ones) + twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(TestUnit, AddRValue2) {
    (twos + (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(TestUnit, SubtractLValue) {
    (ones - twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(-1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(-1.f)));
}

TEST_F(TestUnit, SubtractRValue) {
    ((ones + ones) - twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, SubtractRValue2) {
    (twos - (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}


TEST_F(TestUnit, MultiplyLValue) {
    (ones * twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(TestUnit, MultiplyRValue) {
    ((ones + ones) * twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(TestUnit, MultiplyRValue2) {
    (twos * (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(TestUnit, DivideLValue) {
    (ones / twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(TestUnit, DivideRValue) {
    ((ones + ones) / thelonious::dsp::oscillators::ConstantN<2>(8.f)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.25f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.25f)));
}

TEST_F(TestUnit, DivideRValue2) {
    (threes / (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(TestUnit, ModuloLValue) {
    (ones % thelonious::dsp::oscillators::ConstantN<2>(0.4f)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.2f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.2f)));
}

TEST_F(TestUnit, ModuloRValue) {
    ((ones + ones) % thelonious::dsp::oscillators::ConstantN<2>(1.5f)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(TestUnit, ModuloRValue2) {
    (threes % (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, UnaryPlusLValue) {
    (+ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, UnaryPlusRValue) {
    (+(ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(TestUnit, UnaryMinusLValue) {
    (-ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(-1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(-1.f)));
}

TEST_F(TestUnit, UnaryMinusRValue) {
    (-(ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(-2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(-2.f)));
}

TEST_F(TestUnit, EqualLValue) {
    (ones == ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, EqualRValue) {
    ((ones + ones) == twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, EqualRValue2) {
    (threes == (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, NotEqualLValue) {
    (ones != ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, NotEqualRValue) {
    ((ones + ones) != twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, NotEqualRValue2) {
    (threes != (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LTLValue) {
    (ones < ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, LTRValue) {
    ((ones + ones) < threes).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LTRValue2) {
    (threes < (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}


TEST_F(TestUnit, GTLValue) {
    (ones > ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, GTRValue) {
    ((ones + ones) > twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, GTRValue2) {
    (threes > (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}


TEST_F(TestUnit, LTELValue) {
    (ones <= ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LTERValue) {
    ((ones + ones) <= twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LTERValue2) {
    (threes <= (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, GTELValue) {
    (ones >= ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, GTERValue) {
    ((ones + ones) >= threes).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, GTERValue2) {
    (threes >= (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LogicalNotLValue) {
    (!ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, LogicalNotRValue) {
    (!(zeros + zeros)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LogicalAndLValue) {
    (ones && ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LogicalAndRValue) {
    ((ones + ones) && zeros).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, LogicalAndRValue2) {
    (threes && (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LogicalOrLValue) {
    (ones || ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LogicalOrRValue) {
    ((ones + ones) || zeros).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, LogicalOrRValue2) {
    (zeros || (zeros + zeros)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}
