#ifndef THELONIOUS_CONSTANT_H
#define THELONIOUS_CONSTANT_H

#include "thelonious/types.h"
#include "thelonious/source.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {
namespace dsp {
namespace oscillators {

template <size_t N>
class ConstantN : public Source<N> {
public:
    ConstantN(float value): value(value) {}

    void tick(Block<N> &block) {
        for (uint32_t i=0; i<N; i++) {
            block[i].fill(value);
        }
    }

    float value;
};

typedef ConstantN<1> Constant;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
