#ifndef THELONIOUS_UNIT_TICK_H
#define THELONIOUS_UNIT_TICK_H

#include "thelonious/types.h"
#include "thelonious/unit.h"
#include "thelonious/source.h"
#include "thelonious/processor.h"

namespace thelonious {
namespace operators {

template <class T, size_t N>
class UnitTickN : public T {
public:
    UnitTickN(Unit<N> &unitA, Unit<N> &unitB):
            unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &block) {
        unitA->tick(block);
        unitB->tick(block);
    }

    Unit<N> *unitA;
    Unit<N> *unitB;
};

template <class T>
using UnitTick = UnitTickN<T, 1>;

// Aliases for ticking sources and processors
template <size_t N>
using SourceTickN = UnitTickN<Source<N>, N>;

template <size_t N>
using ProcessorTickN = UnitTickN<Processor<N>, N>;

// Overloaded left-shift operators

/**
 * Ticks an lvalue source through an lvalue processor
 * Usage example: oscillator >> effect
 */
template <size_t N>
operators::SourceTickN<N> operator>>(Source<N> &source,
                                   Processor<N> &processor) {
    return operators::SourceTickN<N>(source, processor);
}

/**
 * Ticks an rvalue source through an lvalue processor
 * Usage example: oscillator1 + oscillator2 >> effect
 */

template <size_t N>
operators::SourceTickN<N> operator>>(Source<N> &&source,
                                   Processor<N> &processor) {
    return operators::SourceTickN<N>(source, processor);
}

/**
 * Ticks an lvalue source through an rvalue processor
 * Usage example: oscillator >> effect * 2.0f
 */
template <size_t N>
operators::SourceTickN<N> operator>>(Source<N> &source,
                                   Processor<N> &&processor) {
    return operators::SourceTickN<N>(source, processor);
}

/**
 * Ticks an rvalue source through an rvalue processor
 * Usage example: oscillator1 + oscillator2 >> effect * 2.0f
 */
template <size_t N>
operators::SourceTickN<N> operator>>(Source<N> &&source,
                                   Processor<N> &&processor) {
    return operators::SourceTickN<N>(source, processor);
}

/**
 * Ticks an lvalue processor through an lvalue processor
 * Usage example: oscillator >> effect1 >> effect2
 */
template<size_t N>
operators::ProcessorTickN<N> operator>>(Processor<N> &processorA,
                                   Processor<N> &processorB) {
    return operators::ProcessorTickN<N>(processorA, processorB);
}

/**
 * Ticks an rvalue processor through an lvalue processor
 * Usage example: oscillator >> effect1 * 2.0 >> effect2
 */
template<size_t N>
operators::ProcessorTickN<N> operator>>(Processor<N> &&processorA,
                                   Processor<N> &processorB) {
    return operators::ProcessorTickN<N>(processorA, processorB);
}

/**
 * Ticks an lvalue processor through an rvalue processor
 * Usage example: oscillator >> effect1 >> effect2 * 2.0f
 */
template<size_t N>
operators::ProcessorTickN<N> operator>>(Processor<N> &processorA,
                                   Processor<N> &&processorB) {
    return operators::ProcessorTickN<N>(processorA, processorB);
}

/**
 * Ticks an rvalue processor through an rvalue processor
 * Usage example: oscillator >> effect1 + 1.0f >> effect2 * 2.0f
 */
template<size_t N>
operators::ProcessorTickN<N> operator>>(Processor<N> &&processorA,
                                   Processor<N> &&processorB) {
    return operators::ProcessorTickN<N>(processorA, processorB);
}


} // namespace operators
} // namespace thelonious

#endif
