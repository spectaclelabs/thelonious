#ifndef THELONIOUS_DSL_CONSTANT_H
#define THELONIOUS_DSL_CONSTANT_H

#include "thelonious/operators/types.h"
#include "thelonious/operators/constant_operator.h"

// Source

#define SOURCE_SAMPLE_LVALUE(name, uppername, op)                           \
template <size_t N>                                                         \
operators::ConstantSource ## name ## N<N> operator op(AbstractSource<N> &a, \
                                                      Sample b) {           \
    return operators::ConstantSource ## name ## N<N>(a, b);                 \
}

#define SOURCE_SAMPLE_RVALUE(name, uppername, op)                           \
template <size_t N>                                                         \
operators::ConstantSource ## name ## N<N> operator op(AbstractSource<N> &&a,\
                                                      Sample b) {           \
    return operators::ConstantSource ## name ## N<N>(a, b);                 \
}

#define SAMPLE_SOURCE_LVALUE_COMMUTATIVE(name, uppername, op)                          \
template <size_t N>                                                         \
operators::ConstantSource ## name ## N<N> operator op(Sample a,             \
                                                    AbstractSource<N> &b) { \
    return operators::ConstantSource ## name ## N<N>(b, a);                 \
}

#define SAMPLE_SOURCE_LVALUE_NON_COMMUTATIVE(name, uppername, op)           \
template <size_t N>                                                         \
operators::ConstantSource ## name ## N<N, true> operator op(Sample a,       \
                                                    AbstractSource<N> &b) { \
    return operators::ConstantSource ## name ## N<N, true>(b, a);           \
}

#define SAMPLE_SOURCE_RVALUE_COMMUTATIVE(name, uppername, op)               \
template <size_t N>                                                         \
operators::ConstantSource ## name ## N<N> operator op(Sample a,             \
                                                AbstractSource<N> &&b) {    \
    return operators::ConstantSource ## name ## N<N>(b, a);                 \
}

#define SAMPLE_SOURCE_RVALUE_NON_COMMUTATIVE(name, uppername, op)           \
template <size_t N>                                                         \
operators::ConstantSource ## name ## N<N, true> operator op(Sample a,       \
                                                AbstractSource<N> &&b) {    \
    return operators::ConstantSource ## name ## N<N, true>(b, a);           \
}

// Processor

#define PROCESSOR_SAMPLE_LVALUE(name, uppername, op)                        \
template <size_t M, size_t N>                                               \
operators::ConstantProcessor ## name ## N<M, N>                             \
        operator op(Processor<M, N> &a, Sample b) {                         \
    return operators::ConstantProcessor ## name ## N<M, N>(a, b);           \
}

#define PROCESSOR_SAMPLE_RVALUE(name, uppername, op)                        \
template <size_t M, size_t N>                                               \
operators::ConstantProcessor ## name ## N<M, N>                             \
        operator op(Processor<M, N> &&a, Sample b) {                        \
    return operators::ConstantProcessor ## name ## N<M, N>(a, b);           \
}

#define SAMPLE_PROCESSOR_LVALUE_COMMUTATIVE(name, uppername, op)            \
template <size_t M, size_t N>                                               \
operators::ConstantProcessor ## name ## N<M, N> operator op(Sample a,       \
                                                 Processor<M, N> &b) {      \
    return operators::ConstantProcessor ## name ## N<M, N>(b, a);           \
}

#define SAMPLE_PROCESSOR_LVALUE_NON_COMMUTATIVE(name, uppername, op)        \
template <size_t M, size_t N>                                               \
operators::ConstantProcessor ## name ## N<M, N, true> operator op(Sample a, \
                                                    Processor<M, N> &b) {   \
    return operators::ConstantProcessor ## name ## N<M, N, true>(b, a);     \
}

#define SAMPLE_PROCESSOR_RVALUE_COMMUTATIVE(name, uppername, op)            \
template <size_t M, size_t N>                                               \
operators::ConstantProcessor ## name ## N<M, N> operator op(Sample a,       \
                                                 Processor<M, N> &&b) {     \
    return operators::ConstantProcessor ## name ## N<M, N>(b, a);           \
}

#define SAMPLE_PROCESSOR_RVALUE_NON_COMMUTATIVE(name, uppername, op)        \
template <size_t M, size_t N>                                               \
operators::ConstantProcessor ## name ## N<M, N, true> operator op(Sample a, \
                                                    Processor<M, N> &&b) {  \
    return operators::ConstantProcessor ## name ## N<M, N, true>(b, a);     \
}


namespace thelonious {

OPERATOR_LIST(SOURCE_SAMPLE_LVALUE)
OPERATOR_LIST(SOURCE_SAMPLE_RVALUE)
COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_LVALUE_COMMUTATIVE)
NON_COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_LVALUE_NON_COMMUTATIVE)
COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_RVALUE_COMMUTATIVE)
NON_COMMUTATIVE_OPERATOR_LIST(SAMPLE_SOURCE_RVALUE_NON_COMMUTATIVE)

OPERATOR_LIST(PROCESSOR_SAMPLE_LVALUE)
OPERATOR_LIST(PROCESSOR_SAMPLE_RVALUE)
COMMUTATIVE_OPERATOR_LIST(SAMPLE_PROCESSOR_LVALUE_COMMUTATIVE)
NON_COMMUTATIVE_OPERATOR_LIST(SAMPLE_PROCESSOR_LVALUE_NON_COMMUTATIVE)
COMMUTATIVE_OPERATOR_LIST(SAMPLE_PROCESSOR_RVALUE_COMMUTATIVE)
NON_COMMUTATIVE_OPERATOR_LIST(SAMPLE_PROCESSOR_RVALUE_NON_COMMUTATIVE)

} // namespace thelonious

#undef SOURCE_SAMPLE_LVALUE
#undef SOURCE_SAMPLE_RVALUE
#undef SAMPLE_SOURCE_LVALUE_COMMUTATIVE
#undef SAMPLE_SOURCE_LVALUE_NON_COMMUTATIVE
#undef SAMPLE_SOURCE_RVALUE_COMMUTATIVE
#undef SAMPLE_SOURCE_RVALUE_NON_COMMUTATIVE
#undef PROCESSOR_SAMPLE_LVALUE
#undef PROCESSOR_SAMPLE_RVALUE
#undef SAMPLE_PROCESSOR_LVALUE_COMMUTATIVE
#undef SAMPLE_PROCESSOR_LVALUE_NON_COMMUTATIVE
#undef SAMPLE_PROCESSOR_RVALUE_COMMUTATIVE
#undef SAMPLE_PROCESSOR_RVALUE_NON_COMMUTATIVE

#endif

