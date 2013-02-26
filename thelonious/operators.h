#ifndef THELONIOUS_OPERATORS_H
#define THELONIOUS_OPERATORS_H

#include "dizzy.h"

#include "types.h"
#include "sizes.h"
#include "unit.h"
#include "parameter.h"
#include "util.h"

namespace thelonious {
template <size_t N>
class Add : public Unit<N> {
public:
    Add(Sample value=0.0f): value(value) {}

    void tick(Block<N> &block) {
        Chock valueChock = value.get();

        auto it=block.begin();
        auto end = block.end();
        for (; it<end; it++) {
            dizzy::add(*it, *it, valueChock);
        }
    }

    Parameter value;
};

template <size_t N>
class Subtract : public Unit<N> {
public:   
    Subtract(Sample value=0.0f): value(value) {}

    void tick(Block<N> &block) {
        Chock valueChock = value.get();

        auto it=block.begin();
        auto end = block.end();
        for (; it<end; it++) {
            dizzy::sub(*it, *it, valueChock);
        }
    }

    Parameter value;
};

template <size_t N>
class Multiply : public Unit<N> {
public:   
    Multiply(Sample value=1.0f): value(value) {}

    void tick(Block<N> &block) {
        Chock valueChock = value.get();

        auto it=block.begin();
        auto end = block.end();
        for (; it<end; it++) {
            dizzy::mul(*it, *it, valueChock);
        }
    }

    Parameter value;
};

template <size_t N>
class Divide : public Unit<N> {
public:   
    Divide(Sample value=1.0f): value(value) {}

    void tick(Block<N> &block) {
        Chock valueChock = value.get();

        auto it=block.begin();
        auto end = block.end();
        for (; it<end; it++) {
            dizzy::div(*it, *it, valueChock);
        }
    }

    Parameter value;
};

template <size_t N>
class Modulo : public Unit<N> {
public:   
    Modulo(Sample value=1.0f): value(value) {}

    void tick(Block<N> &block) {
        Chock valueChock = value.get();

        auto it=block.begin();
        auto end = block.end();
        for (; it!=end; it++) {
            Chock channel = *it;
            for (uint32_t i=0; i<BLOCK_SIZE; i++) {
                channel[i] = wrap(channel[i], valueChock[i]);
            }
        }
    }

    Parameter value;
};
}

#endif
