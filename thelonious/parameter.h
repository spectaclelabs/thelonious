#ifndef THELONIOUS_PARAMETER_H
#define THELONIOUS_PARAMETER_H

#include <algorithm>

#include "types.h"
#include "sink.h"
#include "util.h"
#include "thelonious/constants/sizes.h"

namespace thelonious {

class Parameter : public Sink<1> {
public:
    Parameter(Sample value=0.0f, Interpolation interpolation=LINEAR) :
        value(value), lastValue(value), interpolation(interpolation),
        isDynamic(false), needFill(true) {}

    const Chock& get() {
        if (isDynamic) {
            isDynamic = false;
            lastValue = buffer[constants::BLOCK_SIZE - 1];
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
            for (uint32_t i=0; i<constants::BLOCK_SIZE; i++) {
                buffer[i] = linearInterpolate(lastValue, value,
                                              i * constants::INV_BLOCK_SIZE);
            }
        }

        lastValue = value;

        return buffer;
    }

    void tick(Chock& chock) {
        std::copy(chock.begin(), chock.end(), buffer.begin());
        isDynamic = true;
        // When we stop setting dynamically we will need to refill with the
        // static value
        needFill = true;
    }

    void tick(Block<1> &block) {
        tick(block[0]);
    }

    void set(Sample value) {
        this->value = value;
        // Value has changed, so we need to fill the buffer
        needFill = true;
    }

    void setInterpolation(Interpolation interpolation) {
        this->interpolation = interpolation;
    }

    Interpolation getInterpolation() {
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

/**
 * Set the parameter from a sample.
 * Usage example: 440.0f >> oscillator.frequency;
 */
Sample operator>>(Sample sample, Parameter &parameter) {
    parameter.set(sample);
    return sample;
}

} // namespace thelonious

#endif
