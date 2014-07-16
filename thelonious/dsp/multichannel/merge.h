#ifndef THELONIOUS_MERGE_H
#define THELONIOUS_MERGE_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {
namespace multichannel {

template <size_t M, size_t N>
class MergeN : public Duplex<M, N> {
public:
    MergeN() : index(0) {}

    void tickOut(Block<N> &block) {
        for (uint32_t i=0; i<N; i++) {
            if (i >= index) {
                block[i].fill(0.f);
                continue;
            }

            block[i] = storedBlock[i];
        }

        index = 0;
    }

    void tickIn(Block<M> &block) {
        for (uint32_t i=0; i<M; i++) {
            if (index >= N) {
                break;
            }

            storedBlock[index] = block[i];
            index++;
        }
    }

private:
    Block<N> storedBlock;
    uint32_t index;
};

typedef MergeN<1, 1> Merge;

} // namespace multichannel
} // namespace dsp
} // namespace thelonious

#endif
