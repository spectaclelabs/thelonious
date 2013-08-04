#ifndef THELONIOUS_DSL_BUFFER_H
#define THELONIOUS_DSL_BUFFER_H

#include "thelonious/types.h"
#include "channel.h"

/**
 * Operate on two buffers.
 * Usage example: bufferA = bufferB + bufferC
 */
#define BUFFER_BUFFER(op)                                                   \
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
#define BUFFER_SAMPLE(op)                                           \
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
#define SAMPLE_BUFFER(op)                                           \
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
#define BUFFER_BUFFER_ASSIGN(op)                                            \
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
#define BUFFER_SAMPLE_ASSIGN(op)                                \
template <size_t M, size_t N>                                   \
Buffer<M, N> & operator op ## =(Buffer<M, N> &a, Sample b) {    \
    for (uint32_t i=0; i<M; i++) {                              \
        a[i] op ## = b;                                         \
    }                                                           \
    return a;                                                   \
}

#define OPERATOR_LIST(function) \
function(+)                     \
function(-)                     \
function(*)                     \
function(/)                     \
function(%)                     \

namespace thelonious {
//namespace dsl {

OPERATOR_LIST(BUFFER_BUFFER)
OPERATOR_LIST(BUFFER_SAMPLE)
OPERATOR_LIST(SAMPLE_BUFFER)
OPERATOR_LIST(BUFFER_BUFFER_ASSIGN)
OPERATOR_LIST(BUFFER_SAMPLE_ASSIGN)

//} // namespace dsl
} // namespace thelonious

#undef OPERATOR_LIST
#undef BUFFER_BUFFER
#undef BUFFER_SAMPLE
#undef BUFFER_BUFFER_ASSIGN
#undef BUFFER_SAMPLE_ASSIGN

#endif

