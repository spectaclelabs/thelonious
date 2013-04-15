#ifndef THELONIOUS_DUPLEX_H
#define THELONIOUS_DUPLEX_H

#include "types.h"
#include "source.h"

namespace thelonious {

template <size_t N>
class Duplex : public Source<N> {
public:
    virtual void tickIn(Block<N> &block) = 0;
};

/**
 * Tick an lvalue source to a duplex
 * Usage example: lfo >> oscillator.frequency
 */
template <size_t N>
void operator>>(Source<N> &source, Duplex<N> &duplex) {
    Block<N> block;
    source.tick(block);
    duplex.tickIn(block);
}

/**
 * Tick an rvalue source to a duplex
 * Usage example: lfo * 2.0f >> oscillator.frequency
 */
template <size_t N>
void operator>>(Source<N> &&source, Duplex<N> &duplex) {
    Block<N> block;
    source.tick(block);
    duplex.tickIn(block);
}





} // namespace thelonious

#endif
