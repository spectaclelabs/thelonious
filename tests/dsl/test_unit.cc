#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/dsl/constant.h"
#include "thelonious/dsl/unit.h"
#include "thelonious/source.h"
#include "thelonious/duplex.h"

using namespace thelonious;
using namespace testing;

template <size_t N>
class TestSource : public Source<N> {
public:
    TestSource(Sample value=0.f) : value(value) {}
    void tick(Block<N> &block) {
        for (uint32_t i=0; i<N; i++) {
            block[i].fill(value);
        }
    }

    Sample value;
};

class TestUnit : public Test {
public:
    TestUnit() : ones(1.f), twos(2.f), threes(3.f) {}

    TestSource<2> ones;
    TestSource<2> twos;
    TestSource<2> threes;
    Block<2> block;
};

TEST_F(TestUnit, AddLValue) {
    (ones + twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(TestUnit, AddLValue2) {
    (twos + ones).tick(block);
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

TEST_F(TestUnit, SubtractLValue2) {
    (twos - ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
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

TEST_F(TestUnit, MultiplyLValue2) {
    (twos * ones).tick(block);
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

TEST_F(TestUnit, DivideLValue2) {
    (ones / twos).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(TestUnit, DivideRValue) {
    ((ones + ones) / TestSource<2>(8.f)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.25f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.25f)));
}

TEST_F(TestUnit, DivideRValue2) {
    (threes / (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}

TEST_F(TestUnit, ModuloLValue) {
    (ones % TestSource<2>(0.4f)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.2f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.2f)));
}

TEST_F(TestUnit, ModuloLValue2) {
    (TestSource<2>(1.3f) % ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.3f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.3f)));
}

TEST_F(TestUnit, ModuloRValue) {
    ((ones + ones) % TestSource<2>(1.5f)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(TestUnit, ModuloRValue2) {
    (threes % (ones + ones)).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, EqualLValue) {
    (ones == ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TestUnit, EqualLValue2) {
    (twos == ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
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

TEST_F(TestUnit, LTLValue) {
    (ones < ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(TestUnit, LTLValue2) {
    (twos < ones).tick(block);
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

TEST_F(TestUnit, GTLValue2) {
    (twos > ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
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

TEST_F(TestUnit, LTELValue2) {
    (twos <= ones).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
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

TEST_F(TestUnit, GTELValue2) {
    (twos >= ones).tick(block);
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

