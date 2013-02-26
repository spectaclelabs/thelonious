#ifndef THELONIOUS_DELAY_H
#define THELONIOUS_DELAY_H

#include "types.h"
#include "sizes.h"
#include "unit.h"
#include "parameter.h"
#include "util.h"

namespace thelonious {

template <size_t N, size_t bufferSize>
class Delay : public Unit<N> {
public:
    Delay(Buffer<N, bufferSize> &buffer, Sample position=0.0f,
          Sample rate=1.0f):
        rate(rate), buffer(buffer), position(position) {}

    void tick(const Block<N> &block) {
        Chock rateChock = rate.get();

        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
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

}

#endif
