#ifndef THELONIOUS_PARAMETER_H
#define THELONIOUS_PARAMETER_H

#include <algorithm>

#include "dizzy.h"

#include "types.h"

namespace thelonious {

class Parameter {
public:
    Parameter(Sample value=0.0f, Interpolation interpolation=LINEAR) :
        value(value), lastValue(value), interpolation(interpolation),
        isDynamic(false) {}

    const Chock& get() {
        if (isDynamic) {
            isDynamic = false;
            return buffer;
        }

        // TODO: Cubic interpolation
        if (value == lastValue || interpolation == NONE) {
            std::fill(buffer.begin(), buffer.end(), value);
        }
        else {
            dizzy::ramp(buffer, lastValue, value);
            lastValue = value;
        }

        return buffer;
    }

    void set(Chock& chock) {
        std::copy(chock.begin(), chock.end(), buffer.begin());
        isDynamic = true;
    }

    void set(Block<1> &block) {
        set(block[0]);
    }

    void set(Sample value) {
        this->value = value;
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
