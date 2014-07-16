#ifndef THELONIOUS_OPERATORS_UNIT_BINARY_OPERATOR_H
#define THELONIOUS_OPERATORS_UNIT_BINARY_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/source.h"
#include "thelonious/types.h"
#include "thelonious/dsl/buffer.h"

namespace thelonious {
namespace operators {

template <size_t N, Operator Op>
class UnitBinaryOperatorN : public Source<N> {
public:
    UnitBinaryOperatorN(AbstractSource<N> &unitA, AbstractSource<N> &unitB):
            unitA(&unitA), unitB(&unitB) {}

    void tick(Block<N> &blockA) {
        Block<0> tmp;
        unitA->tick(tmp, blockA);

        Block<N> blockB;
        unitB->tick(tmp, blockB);

        operate(blockA, blockB);
    }

private:
    void operate(Block<N> &blockA, Block<N> &blockB) {
        OperatorType<Op> op;
        operate(blockA, blockB, op);
    }

#define OPERATE_FUNCTION(name, uppername, op)                               \
    void operate(Block<N> &blockA, Block<N> &blockB,                        \
                 name ## Operator oper) {                                   \
        blockA = blockA op blockB;                                          \
    }

    BINARY_OPERATOR_LIST(OPERATE_FUNCTION)

#undef OPERATE_FUNCTION

    AbstractSource<N> *unitA;
    AbstractSource<N> *unitB;
};

#define UNIT_BINARY_OPERATOR_ALIAS(name, uppername, op)                            \
template<size_t N>                                                          \
using Unit ## name ## N = UnitBinaryOperatorN<N, uppername>;

BINARY_OPERATOR_LIST(UNIT_BINARY_OPERATOR_ALIAS)

#undef UNIT_BINARY_OPERATOR_ALIAS

} // namespace operators
} // namespace thelonious

#endif
