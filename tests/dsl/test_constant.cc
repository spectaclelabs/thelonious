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
        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            for (uint32_t j=0; j<2; j++) {
                block[j][i] = value;
            }
        }
    }

    Sample value;
};

template <size_t M, size_t N>
class TestDuplex : public Duplex<M, N> {
public:
    TestDuplex(Sample value=0.f) : value(value) {}

    void tickIn(Block<M> &block) {
    }
    
    void tickOut(Block<N> &block) {
        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            block[i] = value;
        }
    }
    
    Sample value;
};


class ConstantSourceTest : public Test {
public:
    ConstantSourceTest() : ones(1.f), twos(2.f) {}

    TestSource<2> ones;
    TestSource<2> twos;
    Block<2> block;
    Block<0> dummy;
};

TEST_F(ConstantSourceTest, AddLValue) {
    (ones + 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(ConstantSourceTest, AddLValue2) {
    (2.f + ones).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(3.f)));
    ASSERT_THAT(block[1], Each(FloatEq(3.f)));
}

TEST_F(ConstantSourceTest, AddRValue) {
    ((ones + ones) + 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, AddRValue2) {
    (2.f + (ones + ones)).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, SubtractLValue) {
    (ones - 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(-1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(-1.f)));
}

TEST_F(ConstantSourceTest, SubtractLValue2) {
    (2.f - ones).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(ConstantSourceTest, SubtractRValue) {
    ((ones + ones) - 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}

TEST_F(ConstantSourceTest, SubtractRValue2) {
    (2.f - (ones + ones)).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.f)));
}


TEST_F(ConstantSourceTest, MultiplyLValue) {
    (ones * 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(ConstantSourceTest, MultiplyLValue2) {
    (2.f * ones).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(ConstantSourceTest, MultiplyRValue) {
    ((ones + ones) * 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, MultiplyRValue2) {
    (2.f * (ones + ones)).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(ConstantSourceTest, DivideLValue) {
    (ones / 2.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(ConstantSourceTest, DivideLValue2) {
    (1.f / twos).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.5f)));
}

TEST_F(ConstantSourceTest, DivideRValue) {
    ((ones + ones) / 8.f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.25f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.25f)));
}

TEST_F(ConstantSourceTest, DivideRValue2) {
    (3.f / (ones + ones)).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(1.5f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.5f)));
}


TEST_F(ConstantSourceTest, ModuloLValue) {
    (ones % 0.4f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.2f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.2f)));
}

TEST_F(ConstantSourceTest, ModuloLValue2) {
    (1.3f % ones).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.3f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.3f)));
}

TEST_F(ConstantSourceTest, ModuloRValue) {
    ((ones + ones) % 0.4f).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(0.4f)));
    ASSERT_THAT(block[1], Each(FloatEq(0.4f)));
}

TEST_F(ConstantSourceTest, ModuloRValue2) {
    (3.f % (ones + ones)).tick(dummy, block);
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}


    

int main(int argc, char** argv) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
