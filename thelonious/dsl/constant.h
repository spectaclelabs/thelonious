#ifndef THELONIOUS_DSL_CONSTANT_H
#define THELONIOUS_DSL_CONSTANT_H

#include "thelonious/operators/types.h"
#include "thelonious/operators/constant_operator.h"

// Source

#define SOURCE_SAMPLE_LVALUE(name, uppername, op)                           \
template <size_t N>                                                         \
operators::Constant ## name ## N<N> operator op(AbstractSource<N> &a,       \
                                                Sample b) {                 \
    return operators::Constant ## name ## N<N>(a, b);                       \
}

#define SOURCE_SAMPLE_RVALUE(name, uppername, op)                           \
template <size_t N>                                                         \
operators::Constant ## name ## N<N> operator op(AbstractSource<N> &&a,      \
                                                Sample b) {                 \
    return operators::Constant ## name ## N<N>(a, b);                       \
}

#define SAMPLE_SOURCE_LVALUE_COMMUTATIVE(name, uppername, op)                          \
template <size_t N>                                                         \
operators::Constant ## name ## N<N> operator op(Sample a,                   \
                                                AbstractSource<N> &b) {     \
    return operators::Constant ## name ## N<N>(b, a);                       \
}

#define SAMPLE_SOURCE_LVALUE_NON_COMMUTATIVE(name, uppername, op)           \
template <size_t N>                                                         \
operators::Constant ## name ## N<N, true> operator op(Sample a,             \
                                                    AbstractSource<N> &b) { \
    return operators::Constant ## name ## N<N, true>(b, a);                 \
}

#define SAMPLE_SOURCE_RVALUE_COMMUTATIVE(name, uppername, op)               \
template <size_t N>                                                         \
operators::Constant ## name ## N<N> operator op(Sample a,                   \
                                                AbstractSource<N> &&b) {    \
    return operators::Constant ## name ## N<N>(b, a);                       \
}

#define SAMPLE_SOURCE_RVALUE_NON_COMMUTATIVE(name, uppername, op)           \
template <size_t N>                                                         \
operators::Constant ## name ## N<N, true> operator op(Sample a,             \
                                                AbstractSource<N> &&b) {    \
    return operators::Constant ## name ## N<N, true>(b, a);                 \
}

namespace thelonious {

BINARY_OPERATOR_LIST(SOURCE_SAMPLE_LVALUE)
BINARY_OPERATOR_LIST(SOURCE_SAMPLE_RVALUE)
COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_LVALUE_COMMUTATIVE)
NON_COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_LVALUE_NON_COMMUTATIVE)
COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_RVALUE_COMMUTATIVE)
NON_COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_RVALUE_NON_COMMUTATIVE)

} // namespace thelonious

#undef SOURCE_SAMPLE_LVALUE
#undef SOURCE_SAMPLE_RVALUE
#undef SAMPLE_SOURCE_LVALUE_COMMUTATIVE
#undef SAMPLE_SOURCE_LVALUE_NON_COMMUTATIVE
#undef SAMPLE_SOURCE_RVALUE_COMMUTATIVE
#undef SAMPLE_SOURCE_RVALUE_NON_COMMUTATIVE

#endif

