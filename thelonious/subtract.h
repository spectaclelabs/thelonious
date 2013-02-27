#ifndef THELONIOUS_SUBTRACT_H
#define THELONIOUS_SUBTRACT_H

#include "types.h"
#include "unit.h"
#include "parameter.h"

namespace thelonious {

// Subtraction (-) operators

// For Channels

template <size_t N>
Channel<N> operator-(const Channel<N> &a, const Channel<N> &b) {
    Channel<N> channel;
    for (int i=0; i<N; i++) {
        channel[i] = a[i] - b[i];
    }
    return channel;
}

template <size_t N>
Channel<N> operator-(const Channel<N> &a, Sample b) {
    Channel<N> channel;
    for (int i=0; i<N; i++) {
        channel[i] = a[i] - b;
    }
    return channel;
}

template <size_t N>
Channel<N> operator-(Sample a, const Channel<N> &b) {
    Channel<N> channel;
    for (int i=0; i<N; i++) {
        channel[i] = a - b[i];
    }
    return channel;
}

// For Buffers

template <size_t M, size_t N>
Buffer<M, N> operator-(const Buffer<M, N> &a, const Buffer<M, N> &b) {
    Buffer<M, N> buffer;
    for (int i=0; i<M; i++) {
        buffer[i] = a[i] - b[i];
    }
    return buffer;
}

template <size_t M, size_t N>
Buffer<M, N> operator-(const Buffer<M, N> &a, Sample b) {
    Buffer<M, N> buffer;
    for (int i=0; i<M; i++) {
        buffer[i] = a[i] - b;
    }
    return buffer;
}

template <size_t M, size_t N>
Buffer<M, N> operator-(Sample a, const Buffer<M, N> &b) {
    Buffer<M, N> buffer;
    for (int i=0; i<M; i++) {
        buffer[i] = a - b[i];
    }
    return buffer;
}

// End subtraction (-) operators

// Subtraction assignment (-=) operators

// For Channels

template <size_t N>
Channel<N> & operator-=(Channel<N> &a, const Channel<N> &b) {
    for (int i=0; i<N; i++) {
       a[i] -= b[i];
    }
    return a;
}

template <size_t N>
Channel<N> & operator-=(Channel<N> &a, Sample b) {
    for (int i=0; i<N; i++) {
        a[i] -= b;
    }
    return a;
}

// For Buffers

template <size_t M, size_t N>
Buffer<M, N> & operator-=(Buffer<M, N> &a, const Buffer<M, N> &b) {
    for (int i=0; i<M; i++) {
        a[i] -= b[i];
    }
    return a;
} 

template <size_t M, size_t N>
Buffer<M, N> & operator-=(Buffer<M, N> &a, Sample b) {
    for (int i=0; i<M; i++) {
        a[i] -= b;
    }
    return a;
}

// End subtraction assignment (-=) operators

template <size_t N>
class Subtract : public Unit<N> {
public:
    Subtract(Sample value=0.0f): value(value) {}

    void tick(Block<N> &block) {
        Chock valueChock = value.get();

        for (int i=0; i<N; i++) {
            block[i] -= valueChock;
        }
    }

    Parameter value;
};

}

#endif
