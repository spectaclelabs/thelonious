#ifndef THELONIOUS_UNIT_H
#define THELONIOUS_UNIT_H

#include "types.h"

namespace thelonious {

template <size_t N>
class Unit {
public:
    virtual void tick(Block<N> &block) = 0;

};

/**
 * Tick an lvalue block through an lvalue unit.
 * Usage example: void tick(Block<N> block) { block >> effect }
 */
template <size_t N>
Block<N> & operator>>(Block<N> & block, Unit<N> &unit) {
    unit.tick(block);
    return block;
}

/**
 * Tick an lvalue block through an rvalue unit.
 * Usage example: void tick(Block<N> block) { block >> effect + oscillator}
 */
template <size_t N>
Block<N> & operator>>(Block<N> & block, Unit<N> &&unit) {
    unit.tick(block);
    return block;
}

/**
 * Tick an rvalue block through an lvalue unit.
 * Usage example: oscilltor >> effect1 >> effect2
 */
template <size_t N>
Block<N> operator>>(Block<N> && block, Unit<N> &unit) {
    unit.tick(block);
    return std::move(block);
}
   
/**
 * Tick an rvalue block through an rvalue unit.
 * Usage example: block >> effect1 >> effect2 + oscillator
 */
template <size_t N>
Block<N> operator>>(Block<N> && block, Unit<N> &&unit) {
    unit.tick(block);
    return std::move(block);
}


/**
 * Tick a block through two lvalue units.
 * Usage example: oscillator >> effect;
 */
template<size_t N>
Block<N> operator>>(Unit<N> & a, Unit<N> & b) {
    Block<N> block;
    a.tick(block);
    b.tick(block);
    return block;
}

/**
 * Tick a block through an lvalue and an rvalue unit.
 * Usage example: oscillator1 >> effect + oscillator2;
 */
template<size_t N>
Block<N> operator>>(Unit<N> & a, Unit<N> && b) {
    Block<N> block;
    a.tick(block);
    b.tick(block);
    return block;
}

/**
 * Tick a block through an rvalue and an lvalue unit.
 * Usage example: oscillator1 + oscillator2 >> effect
 */
template<size_t N>
Block<N> operator>>(Unit<N> && a, Unit<N> & b) {
    Block<N> block;
    a.tick(block);
    b.tick(block);
    return block;
}

/**
 * Tick a block through two rvalue units.
 * Usage example: oscillator1 + oscillator2 >> effect + oscillator3
 */
template<size_t N>
Block<N> operator>>(Unit<N> && a, Unit<N> && b) {
    Block<N> block;
    a.tick(block);
    b.tick(block);
    return block;
}

/**
 * Tick a block through an lvalue unit.
 * Usage example: void tick(Block<N> block) { oscillator >> block; }
 */
template <size_t N>
void operator>>(Unit<N> &unit, Block<N> &block) {
    unit.tick(block);
}

/**
 * Tick a block through an rvalue unit.
 * Usage example: void tick(Block<N> block) { osc1 + osc2 >> block; }
 */
template <size_t N>
void operator>>(Unit<N> &&unit, Block<N> &block) {
    unit.tick(block);
}

} // namespace thelonious

#endif
