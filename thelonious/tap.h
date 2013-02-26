#ifndef TAP_H
#define TAP_H

#include "types.h"
#include "sizes.h"
#include "unit.h"
#include "parameter.h"
#include "util.h"

namespace thelonious {

template <size_t N, size_t bufferSize>
class Tap : public Unit<N> {
public:
    Tap(const Buffer<N, bufferSize> &buffer, Sample position=0.0f,
        Sample rate=1.0f, Interpolation interpolation=NONE):
        rate(rate), buffer(buffer), position(position),
        interpolation(interpolation) {}

    void tick(Block<N> &block) {
        Chock rateChock = rate.get();

        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
            for (uint32_t j=0; j<N; j++) {
                // TODO: Interpolation
                block[j][i] = buffer[j][position];
            }

            position += rateChock[i];
            position = wrap(position, bufferSize);
        }
    }

    Parameter rate;

private:
    const Buffer<N, bufferSize> &buffer;
    Sample position;
    Interpolation interpolation;
};
}

#endif
