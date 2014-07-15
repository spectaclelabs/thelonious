#ifndef THELONIOUS_MERGE_H
#define THELONIOUS_MERGE_H

#include "thelonious/types.h"
#include "thelonious/duplex.h"

namespace thelonious {
namespace dsp {

template <size_t M, size_t N>
class MergeN : public Duplex<M, N> {
public:
    MergeN() {}

    void tickOut(Block<N> &block) {
        block = storedBlock;
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

typedef MergeN<1> Merge;

} // namespace dsp
} // namespace thelonious

#endif
