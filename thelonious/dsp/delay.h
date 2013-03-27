#ifndef THELONIOUS_DELAY_H
#define THELONIOUS_DELAY_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/parameter.h"
#include "thelonious/util.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {
namespace dsp {

template <size_t N, size_t bufferSize>
class DelayN : public Unit<N> {
public:
    DelayN(Buffer<N, bufferSize> &buffer, Sample position=0.0f,
          Sample rate=1.0f):
        rate(rate), buffer(buffer), position(position) {}

    void tick(const Block<N> &block) {
        Chock rateChock = rate.get();

        for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
            for (uint32_t j=0; j<N; j++) {
                buffer[j][position] = block[j][i];
            }

            position += rateChock[i];
            position = wrap(position, bufferSize);
        }
    }

    Parameter rate;

private:
    Buffer<N, bufferSize> &buffer;
    Sample position;
};

template <size_t bufferSize>
using Delay = DelayN<1, bufferSize>;

} // namespace dsp
} // namespace thelonious

#endif
