#ifndef PARAMETER_H
#define PARAMETER_H

#include <algorithm>

#include "dizzy.h"

#include "types.h"

namespace thelonious {

class Parameter {
public:
    Parameter(Sample value=0, Interpolation interpolation=LINEAR) :
        value(value), lastValue(value), interpolation(interpolation) {}

    const Chock& get() {
        // TODO: Cubic interpolation
        if (value == lastValue || interpolation == NONE) {
            std::fill(buffer.begin(), buffer.end(), value);
        }
        else {
            dizzy::ramp(buffer, lastValue, value);
            lastValue = value;
        }

        if (dynamicBuffer != nullptr) {
            dizzy::add(buffer, buffer, *dynamicBuffer);
        }
        return buffer;
    }

    void setDynamic(Chock& chock) {
        dynamicBuffer = &chock;
    }

    void setDynamic(Block<1> &block) {
        dynamicBuffer = &block[0];
    }

    void unsetDynamic() {
        dynamicBuffer = nullptr;

        // TODO: Should we interpolate removal of the dynamic buffer.
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
    Chock *dynamicBuffer=nullptr;

    Interpolation interpolation;
};

}

#endif
