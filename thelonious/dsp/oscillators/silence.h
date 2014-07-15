#ifndef THELONIOUS_SILENCE_H
#define THELONIOUS_SILENCE_H

#include "thelonious/dsp/oscillators/constant.h"

namespace thelonious {
namespace dsp {
namespace oscillators {

template <size_t N>
class SilenceN : public ConstantN<N> {
public:
    SilenceN(): ConstantN<N>(0) {}
};

typedef SilenceN<1> Silence;

} // namespace oscillators
} // namespace dsp
} // namespace thelonious

#endif
