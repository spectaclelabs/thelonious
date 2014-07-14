#ifndef THELONIOUS_OPERATORS_CONSTANT_OPERATOR_H
#define THELONIOUS_OPERATORS_CONSTANT_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/unit.h"
#include "thelonious/types.h"
#include "thelonious/source.h"
#include "thelonious/processor.h"
#include "thelonious/dsl/buffer.h"

namespace thelonious {
namespace operators {

template <size_t N, Operator Op, bool Inverse=false>
class ConstantOperatorN : public Source<N> {
public:
    ConstantOperatorN(AbstractSource<N> &unit, Sample value):
            unit(&unit), value(value) {}

    void tick(Block<N> &outputBlock) {
        Block<0> tmp;
        unit->tick(tmp, outputBlock);
        operate(outputBlock, value);
    }

private:
    void operate(Block<N> &block, Sample value) {
        OperatorType<Op> op;
        InverseType<Inverse> inverse;
        operate(block, value, op, inverse);
    }

#define OPERATE_FUNCTION(name, uppername, op)                               \
    void operate(Block<N> &block, Sample value, name ## Operator oper,      \
                 RegularOperator inverse) {                                 \
        block = block op value;                                             \
    }

#define INVERSE_OPERATE_FUNCTION(name, uppername, op)                       \
    void operate(Block<N> &block, Sample value, name ## Operator oper,      \
                 InverseOperator inverse) {                                 \
        block = value op block;                                             \
    }

    COMMUTATIVE_OPERATOR_LIST(OPERATE_FUNCTION)
    NON_COMMUTATIVE_OPERATOR_LIST(OPERATE_FUNCTION)
    NON_COMMUTATIVE_OPERATOR_LIST(INVERSE_OPERATE_FUNCTION)

#undef OPERATE_FUNCTION
#undef INVERSE_OPERATE_FUNCTION

    AbstractSource<N> *unit;
    Sample value;
};


#define CONSTANT_OPERATOR_ALIAS(name, uppername, op)                        \
template <size_t N, bool Inverse=false>                                     \
using Constant ## name  ## N = ConstantOperatorN<N, uppername, Inverse>;

OPERATOR_LIST(CONSTANT_OPERATOR_ALIAS)

#undef CONSTANT_OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
