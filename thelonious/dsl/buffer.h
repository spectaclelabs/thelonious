#ifndef THELONIOUS_DSL_BUFFER_H
#define THELONIOUS_DSL_BUFFER_H

#include "thelonious/types.h"
#include "thelonious/operators/types.h"
#include "channel.h"

/**
 * Operate on two buffers.
 * Usage example: bufferA = bufferB + bufferC
 */
#define BUFFER_BUFFER(name, uppername, op)                                  \
template <size_t M, size_t N>                                               \
Buffer<M, N> operator op(const Buffer<M, N> &a, const Buffer<M, N> &b) {    \
    Buffer<M, N> buffer;                                                    \
    for (uint32_t i=0; i<M; i++) {                                          \
        buffer[i] = a[i] op b[i];                                           \
    }                                                                       \
    return buffer;                                                          \
}

/**
 * Operate on a buffer and a sample.
 * Usage example: bufferA = bufferB + sample
 */
#define BUFFER_SAMPLE(name, uppername, op)                          \
template <size_t M, size_t N>                                       \
Buffer<M, N> operator op(const Buffer<M, N> &a, Sample b) {         \
    Buffer<M, N> buffer;                                            \
    for (uint32_t i=0; i<M; i++) {                                  \
        buffer[i] = a[i] op b;                                      \
    }                                                               \
    return buffer;                                                  \
}

/**
 * Operate on a sample and buffer.
 * Usage example: bufferA = sample + bufferB
 */
#define SAMPLE_BUFFER(name, uppername, op)                          \
template <size_t M, size_t N>                                       \
Buffer<M, N> operator op(Sample a, const Buffer<M, N> &b) {         \
    Buffer<M, N> buffer;                                            \
    for (uint32_t i=0; i<M; i++) {                                  \
        buffer[i] = a op b[i];                                      \
    }                                                               \
    return buffer;                                                  \
}

/**
 * Use a compound assignment operator with two buffers.
 * Usage example: bufferA += bufferB
 */
#define BUFFER_BUFFER_ASSIGN(name, uppername, op)                           \
template <size_t M, size_t N>                                               \
Buffer<M, N> & operator op ## =(Buffer<M, N> &a, const Buffer<M, N> &b) {   \
    for (uint32_t i=0; i<M; i++) {                                          \
        a[i] op ## = b[i];                                                  \
    }                                                                       \
    return a;                                                               \
}

/**
 * Use a compound assignment operator with a buffer and a sample.
 * Usage example: bufferA += sample
 */
#define BUFFER_SAMPLE_ASSIGN(name, uppername, op)               \
template <size_t M, size_t N>                                   \
Buffer<M, N> & operator op ## =(Buffer<M, N> &a, Sample b) {    \
    for (uint32_t i=0; i<M; i++) {                              \
        a[i] op ## = b;                                         \
    }                                                           \
    return a;                                                   \
}

/**
 * Unary operate on a buffer
 * Usage example: bufferA = -bufferB
 */
#define BUFFER_UNARY(name, uppername, op)                           \
template <size_t M, size_t N>                                       \
Buffer<M, N> operator op(const Buffer<M, N> &a) {                   \
    Buffer<M, N> buffer;                                            \
    for (uint32_t i=0; i<M; i++) {                                  \
        buffer[i] = op a[i];                                        \
    }                                                               \
    return buffer;                                                  \
}

namespace thelonious {
//namespace dsl {

BINARY_OPERATOR_LIST(BUFFER_BUFFER)
BINARY_OPERATOR_LIST(BUFFER_SAMPLE)
BINARY_OPERATOR_LIST(SAMPLE_BUFFER)
BINARY_COMPOUND_OPERATOR_LIST(BUFFER_BUFFER_ASSIGN)
BINARY_COMPOUND_OPERATOR_LIST(BUFFER_SAMPLE_ASSIGN)

UNARY_OPERATOR_LIST(BUFFER_UNARY)

//} // namespace dsl
} // namespace thelonious

#undef BUFFER_BUFFER
#undef BUFFER_SAMPLE
#undef BUFFER_BUFFER_ASSIGN
#undef BUFFER_SAMPLE_ASSIGN
#undef BUFFER_UNARY

#endif

