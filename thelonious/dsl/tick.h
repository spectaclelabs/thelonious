#ifndef THELONIOUS_DSL_TICK_H
#define THELONIOUS_DSL_TICK_H

#include "thelonious/types.h"
#include "thelonious/operators/unit_tick.h"
#include "thelonious/abstract_source.h"
#include "thelonious/abstract_sink.h"
#include "thelonious/processor.h"

namespace thelonious {

// -------------------
// Source >> Processor
// -------------------

/**
 * Ticks an lvalue source through an lvalue processor
 * Usage example: oscillator >> effect
 */
template <size_t M, size_t N>
operators::UnitTickN<M, N> operator>>(AbstractSource<M> &source,
                                      Processor<M, N> &processor) {
    return operators::UnitTickN<M, N>(source, processor);
}

/**
 * Ticks an rvalue source through an lvalue processor
 * Usage example: oscillator1 + oscillator2 >> effect
 */

template <size_t M, size_t N>
operators::UnitTickN<M, N> operator>>(AbstractSource<M> &&source,
                                      Processor<M, N> &processor) {
    return operators::UnitTickN<M, N>(source, processor);
}

// --------------
// Source >> Sink
// --------------

/**
 * Tick an lvalue source to a sink
 * Usage example: oscillator >> device.output
 */
template <size_t N>
void operator>>(AbstractSource<N> &source, AbstractSink<N> &sink) {
    Block<N> block;
    Block<0> tmp;
    source.tick(tmp, block);
    sink.tick(block, tmp);
}

/**
 * Tick an rvalue source to a sink
 * Usage example: oscillator1 + oscillator2 >> device.output
 */
template <size_t N>
void operator>>(AbstractSource<N> &&source, AbstractSink<N> &sink) {
    Block<N> block;
    Block<0> tmp;
    source.tick(tmp, block);
    sink.tick(block, tmp);
}

// ---------------
// Source >> Block
// ---------------

/**
 * Tick an lvalue source to a block
 * Usage example: oscillator >> block
 */
template <size_t N>
void operator>>(AbstractSource<N> &source, Block<N> &block) {
    Block<0> tmp;
    source.tick(tmp, block);
}

/**
 * Tick an rvalue source to a block
 * Usage example: oscillator1 + oscillator2 >> block
 */
template <size_t N>
void operator>>(AbstractSource<N> &&source, Block<N> &block) {
    Block<0> tmp;
    source.tick(tmp, block);
}


} // namespace thelonious

#endif
