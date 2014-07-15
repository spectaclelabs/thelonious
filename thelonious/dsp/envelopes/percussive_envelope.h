#ifndef THELONIOUS_PERCUSSIVE_ENVELOPE_H
#define THELONIOUS_PERCUSSIVE_ENVELOPE_H

#include "thelonious/types.h"
#include "envelope.h"

namespace thelonious {
namespace dsp {
namespace envelopes {

template <size_t N>
class PercussiveEnvelopeN : public EnvelopeN<N> {
public:
    PercussiveEnvelopeN(float attack, float release) :
            EnvelopeN<N>(0.0f, {1.0f, 0.0f}, {attack, release}) {
    }
};

typedef PercussiveEnvelopeN<1> PercussiveEnvelope;

} // namespace envelopes
} // namespace dsp
} // namespace thelonious

#endif
