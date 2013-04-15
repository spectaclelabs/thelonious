#ifndef THELONIOUS_SPLITTER_H
#define THELONIOUS_SPLITTER_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {

template <size_t N>
class SplitterN : public Duplex<N> {
public:
    SplitterN() {}

    void tick(Block<N> &block) {
        block = this->block;
    }

    void tickIn(Block<N> &block) {
        this->block = block;
    }

private:
    Block<N> block;
};

typedef SplitterN<1> Splitter;

} // namespace dsp
} // namespace thelonious

#endif
