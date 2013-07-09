#ifndef THELONIOUS_OPERATORS_UNIT_TICK_H
#define THELONIOUS_OPERATORS_UNIT_TICK_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/source.h"
#include "thelonious/processor.h"

namespace thelonious {
namespace operators {

template <size_t M, size_t N>
class UnitTickN : public Source<N> {
public:
    UnitTickN(AbstractSource<M> &source, Processor<M, N> &processor):
            source(&source), processor(&processor) {}

    void tick(Block<N> &outputBlock) {
        Block<M> sourceBlock;
        Block<0> tmp;
        source->tick(tmp, sourceBlock);
        processor->tick(sourceBlock, outputBlock);
    }

    AbstractSource<M> *source;
    Processor<M, N> *processor;
};

} // namespace operators
} // namespace thelonious

#endif
