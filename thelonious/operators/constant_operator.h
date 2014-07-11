#ifndef THELONIOUS_OPERATORS_CONSTANT_OPERATOR_H
#define THELONIOUS_OPERATORS_CONSTANT_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/unit.h"
#include "thelonious/types.h"
#include "thelonious/abstract_source.h"
#include "thelonious/processor.h"
#include "thelonious/dsl/buffer.h"

namespace thelonious {
namespace operators {

template <class T, size_t M, size_t N, Operator Op, bool Inverse=false>
class ConstantOperatorN : public T {
public:
    ConstantOperatorN(Unit<M, N> &unit, Sample value):
            unit(&unit), value(value) {}

    void tick(Block<M> &inputBlock, Block<N> &outputBlock) {
        unit->tick(inputBlock, outputBlock);
        operate(outputBlock, value);
    }

private:
    void operate(Block<N> &block, Sample value) {
        OperatorType<Op> op;
        InverseType<Inverse> inverse;
        operate(block, value, op, inverse);
    }

    // Usage example: unit + 2.0f
    void operate(Block<N> &block, Sample value, AddOperator op,
                 RegularOperator inverse) {
        block += value;
    }

    // Usage example: unit - 2.0f
    void operate(Block<N> &block, Sample value, SubtractOperator op,
                 RegularOperator inverse) {
        block -= value;
    }

    // Usage example: 2.0f - unit 
    void operate(Block<N> &block, Sample value, SubtractOperator op,
                 InverseOperator inverse) {
        block = value - block;
    }

    // Usage example: unit * 2.0f
    void operate(Block<N> &block, Sample value, MultiplyOperator op,
                 RegularOperator inverse) {
        block *= value;
    }

    // Usage example: unit / 2.0f
    void operate(Block<N> &block, Sample value, DivideOperator op,
                 RegularOperator inverse) {
        block /= value;
    }

    // Usage example: 2.0f / unit
    void operate(Block<N> &block, Sample value, DivideOperator op,
                 InverseOperator inverse) {
        block = value / block;
    }

    // Usage example: unit % 2.0f
    void operate(Block<N> &block, Sample value, ModuloOperator op,
                 RegularOperator inverse) {
        block %= value;
    }

    // Usage example: 2.0f % unit
    void operate(Block<N> &block, Sample value, ModuloOperator op,
                 InverseOperator inverse) {
        block = value % block;
    }

    Unit<M, N> *unit;
    Sample value;
};


#define CONSTANT_OPERATOR_ALIAS(name, uppername, op)                        \
template <class T, size_t M, size_t N, bool Inverse=false>                  \
using Constant ## name  ## N = ConstantOperatorN<T, M, N, uppername,        \
                                                 Inverse>;

#define CONSTANT_SOURCE_OPERATOR_ALIAS(name, uppername, op)                 \
template <size_t N, bool Inverse=false>                                     \
using ConstantSource ## name ## N = Constant ## name ## N<AbstractSource<N>,\
                                                          0, N, Inverse>;

#define CONSTANT_PROCESSOR_OPERATOR_ALIAS(name, uppername, op)               \
template <size_t M, size_t N, bool Inverse=false>                            \
using ConstantProcessor ## name ## N = Constant ## name ## N<Processor<M, N>,\
                                                             M, N, Inverse>;

OPERATOR_LIST(CONSTANT_OPERATOR_ALIAS)
OPERATOR_LIST(CONSTANT_SOURCE_OPERATOR_ALIAS)
OPERATOR_LIST(CONSTANT_PROCESSOR_OPERATOR_ALIAS)

#undef CONSTANT_OPERATOR_ALIAS
#undef CONSTANT_SOURCE_OPERATOR_ALIAS
#undef CONSTANT_PROCESSOR_OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
