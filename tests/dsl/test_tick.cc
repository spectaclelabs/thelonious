#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "thelonious/dsl/tick.h"
#include "thelonious/dsl/unit.h"
#include "thelonious/dsl/buffer.h"
#include "thelonious/source.h"
#include "thelonious/processor.h"
#include "thelonious/sink.h"

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

template <size_t M, size_t N>
class TestProcessor : public Processor<M, N> {
public:
    TestProcessor() {}

    void tick(Block<M> &inputBlock, Block<N> &outputBlock) {
        outputBlock = inputBlock * 2.f;
    }
};

template <size_t N>
class TestSink : public Sink<N> {
public:
    TestSink() {}

    void tick(Block<N> &block) {
        storedBlock = block;
    }

    Block<N> storedBlock;
};

class TickTest : public Test {
public:
    TickTest() : ones(1.f) {}

    TestSource<2> ones;
    TestProcessor<2, 2> processor;
    TestSink<2> sink;
    Block<2> block;
};

TEST_F(TickTest, SourceProcessorLL) {
    (ones >> processor).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

TEST_F(TickTest, SourceProcessorRL) {
    ((ones + ones) >> processor).tick(block);
    ASSERT_THAT(block[0], Each(FloatEq(4.f)));
    ASSERT_THAT(block[1], Each(FloatEq(4.f)));
}

TEST_F(TickTest, SourceSinkLL) {
    ones >> sink;
    ASSERT_THAT(sink.storedBlock[0], Each(FloatEq(1.f)));
    ASSERT_THAT(sink.storedBlock[1], Each(FloatEq(1.f)));
}

TEST_F(TickTest, SourceSinkRL) {
    (ones + ones) >> sink;
    ASSERT_THAT(sink.storedBlock[0], Each(FloatEq(2.f)));
    ASSERT_THAT(sink.storedBlock[1], Each(FloatEq(2.f)));
}

TEST_F(TickTest, SourceBlockLL) {
    ones >> block;
    ASSERT_THAT(block[0], Each(FloatEq(1.f)));
    ASSERT_THAT(block[1], Each(FloatEq(1.f)));
}

TEST_F(TickTest, SourceBlockRL) {
    (ones + ones) >> block;
    ASSERT_THAT(block[0], Each(FloatEq(2.f)));
    ASSERT_THAT(block[1], Each(FloatEq(2.f)));
}

