#ifndef THELONIOUS_SOURCE_H
#define THELONIOUS_SOURCE_H

#include "types.h"
#include "unit.h"
#include "processor.h"
#include "sink.h"

namespace thelonious {

template <size_t N>
class Source : public Unit<N> {
};

/**
 * Tick an lvalue source to a sink
 * Usage example: oscillator >> device.output
 */
template <size_t N>
void operator>>(Source<N> &source, Sink<N> &sink) {
    Block<N> block;
    source.tick(block);
    sink.tick(block);
}

/**
 * Tick an rvalue source to a sink
 * Usage example: oscillator1 + oscillator2 >> device.output
 */
template <size_t N>
void operator>>(Source<N> &&source, Sink<N> &sink) {
    Block<N> block;
    source.tick(block);
    sink.tick(block);
}  

/**
 * Tick an lvalue source to a block
 * Usage example: oscillator >> block
 */
template <size_t N>
void operator>>(Source<N> &source, Block<N> &block) {
    source.tick(block);
}

/**
 * Tick an rvalue source to a block
 * Usage example: oscillator1 + oscillator2 >> block
 */
template <size_t N>
void operator>>(Source<N> &&source, Block<N> &block) {
    source.tick(block);
}

} // namespace thelonious

#endif





