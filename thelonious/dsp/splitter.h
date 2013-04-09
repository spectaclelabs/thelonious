#ifndef THELONIOUS_SPLITTER_H
#define THELONIOUS_SPLITTER_H

#include "types.h"
#include "source.h"
#include "sink.h"

namespace thelonious {
namespace dsp {

template <size_t N>
class SplitterInput : public Sink<N> {
public:
    SplitterInput(Block<N> &block) : block(block) {}

    void tick(Block<N> &block) {
        this->block = block;
    }

private:
    Block<N> &block;
};

template <size_t N>
class SplitterOutput : public Source<N> {
public:
    SplitterOutput(Block<N> &block) : block(block) {}

    void tick(Block<N> &block) {
        block = this->block;
    }

private:
    Block<N> &block;
};

template <size_t N>
class SplitterN {
public:
    SplitterN() : input(block), output(block) {}

    SplitterInput<N> input;
    SplitterOutput<N> output;

private:
    Block<N> block;
};

typedef SplitterN<1> Splitter;

} // namespace dsp
} // namespace thelonious

#endif
