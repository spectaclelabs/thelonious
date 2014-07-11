#ifndef THELONIOUS_OPERATORS_UNIT_OPERATOR_H
#define THELONIOUS_OPERATORS_UNIT_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/source.h"
#include "thelonious/types.h"

namespace thelonious {
namespace operators {

template <size_t N, Operator Op>
class UnitOperatorN : public Source<N> {
public:
    UnitOperatorN(AbstractSource<N> &unitA, AbstractSource<N> &unitB):
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

    void operate(Block<N> &blockA, Block<N> &blockB, AdditionOperator op) {
        blockA += blockB;
    }

    void operate(Block<N> &blockA, Block<N> &blockB, SubtractionOperator op) {
        blockA -= blockB;
    }

    void operate(Block<N> &blockA, Block<N> &blockB,
                 MultiplicationOperator op) {
        blockA *= blockB;
    }

    void operate(Block<N> &blockA, Block<N> &blockB, DivisionOperator op) {
        blockA /= blockB;
    }

    void operate(Block<N> &blockA, Block<N> &blockB, ModuloOperator op) {
        blockA %= blockB;
    }

    AbstractSource<N> *unitA;
    AbstractSource<N> *unitB;
};

// Binary Mathematical
template<size_t N>
using UnitAddN = UnitOperatorN<N, ADDITION>;

template<size_t N>
using UnitSubtractN = UnitOperatorN<N, SUBTRACTION>;

template<size_t N>
using UnitMultiplyN = UnitOperatorN<N, MULTIPLICATION>;

template<size_t N>
using UnitDivideN = UnitOperatorN<N, DIVISION>;

template<size_t N>
using UnitModuloN = UnitOperatorN<N, MODULO>;

} // namespace operators
} // namespace thelonious

#endif
