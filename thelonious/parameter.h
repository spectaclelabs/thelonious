#ifndef THELONIOUS_PARAMETER_H
#define THELONIOUS_PARAMETER_H

#include <algorithm>

#include "dizzy.h"

#include "types.h"
#include "sizes.h"
#include "unit.h"

namespace thelonious {

class Parameter {
public:
    Parameter(Sample value=0.0f, Interpolation interpolation=LINEAR) :
        value(value), lastValue(value), interpolation(interpolation),
        isDynamic(false), needFill(true) {}

    const Chock& get() {
        if (isDynamic) {
            isDynamic = false;
            lastValue = buffer[BLOCK_SIZE - 1];
            return buffer;
        }

        // If the buffer is already filled with the correct constant value,
        // then we don't need to do it again!
        if (!needFill) {
            return buffer;
        }

        // TODO: Cubic interpolation
        if (value == lastValue || interpolation == NONE) {
            std::fill(buffer.begin(), buffer.end(), value);
            needFill = false;
        }
        else {
            dizzy::ramp(buffer, lastValue, value);
        }

        lastValue = value;

        return buffer;
    }

    void set(Chock& chock) {
        std::copy(chock.begin(), chock.end(), buffer.begin());
        isDynamic = true;
        // When we stop setting dynamically we will need to refill with the
        // static value
        needFill = true;
    }

    void set(Block<1> &block) {
        set(block[0]);
    }

    void set(Sample value) {
        this->value = value;
        // Value has changed, so we need to fill the buffer
        needFill = true;
    }

    void setInterpolate(Interpolation interpolation) {
        this->interpolation = interpolation;
    }

    Interpolation getInterpolate() {
        return interpolation;
    }

private:
    Sample value;
    Sample lastValue;

    Chock buffer;

    Interpolation interpolation;

    bool isDynamic;
    bool needFill;
};

template <size_t N>
Block<N> operator>>(Block<N> block, Parameter &parameter) {
    parameter.set(block);
    return block;
}

template <size_t N>
Block<N> operator>>(Unit<N> &unit, Parameter &parameter) {
    Block<N> block;
    unit.tick(block);
    parameter.set(block);
    return block;
}

Sample operator>>(Sample sample, Parameter &parameter) {
    parameter.set(sample);
    return sample;
}

}

#endif
