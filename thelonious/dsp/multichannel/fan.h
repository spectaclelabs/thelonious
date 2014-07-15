#ifndef THELONIOUS_FAN_H
#define THELONIOUS_FAN_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {

template <size_t N>
class FanN : public Duplex<N, N> {
public:
    FanN() {}

    void tickOut(Block<N> &block) {
        block = this->block;
    }

    void tickIn(Block<N> &block) {
        this->block = block;
    }

private:
    Block<N> block;
};

typedef FanN<1> Fan;

} // namespace dsp
} // namespace thelonious

#endif
