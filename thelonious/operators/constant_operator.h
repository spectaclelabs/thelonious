#ifndef THELONIOUS_OPERATORS_CONSTANT_OPERATOR_H
#define THELONIOUS_OPERATORS_CONSTANT_OPERATOR_H

#include "thelonious/operators/types.h"
#include "thelonious/unit.h"
#include "thelonious/types.h"

namespace thelonious {
namespace operators {

template <class T, size_t M, size_t N, char Op, bool Inverse=false>
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
    void operate(Block<N> &block, Sample value, AdditionOperator op,
                 RegularOperator inverse) {
        block += value;
    }

    // Usage example: unit - 2.0f
    void operate(Block<N> &block, Sample value, SubtractionOperator op,
                 RegularOperator inverse) {
        block -= value;
    }

    // Usage example: 2.0f - unit 
    void operate(Block<N> &block, Sample value, SubtractionOperator op,
                 InverseOperator inverse) {
        block = value - block;
    }

    // Usage example: unit * 2.0f
    void operate(Block<N> &block, Sample value,
                 MultiplicationOperator op, RegularOperator inverse) {
        block *= value;
    }

    // Usage example: unit / 2.0f
    void operate(Block<N> &block, Sample value, DivisionOperator op,
                 RegularOperator inverse) {
        block /= value;
    }

    // Usage example: 2.0f / unit
    void operate(Block<N> &block, Sample value, DivisionOperator op,
                 InverseOperator inverse) {
        block = value / block;
    }

    // Usage example: unit % 2.0f
    void operate(Block<N> &block, Sample value, ModuloOperator op,
                 RegularOperator inverse) {
        block %= block;
    }

    // Usage example: unit % 2.0f
    void operate(Block<N> &block, Sample value, ModuloOperator op,
                 InverseOperator inverse) {
        block = value % block;
    }

    Unit<M, N> *unit;
    Sample value;
};


// TODO: Make this into a macro
// Addition template aliases
template <class T, size_t M, size_t N>
using ConstantAddN = ConstantOperatorN<T, M, N, '+'>;

template <size_t N>
using ConstantSourceAddN = ConstantAddN<AbstractSource<N>, 0, N>;

template <size_t M, size_t N>
using ConstantProcessorAddN = ConstantAddN<Processor<M, N>, M, N>;

// Subtraction template aliases
template <class T, size_t M, size_t N, bool Inverse=false>
using ConstantSubtractN = ConstantOperatorN<T, M, N, '-', Inverse>;

template <size_t N, bool Inverse=false>
using ConstantSourceSubtractN = ConstantSubtractN<AbstractSource<N>, 0, N, Inverse>;

template <size_t M, size_t N, bool Inverse=false>
using ConstantProcessorSubtractN = ConstantSubtractN<Processor<M, N>, M, N,
                                                     Inverse>;

// Multiplication template aliases
template <class T, size_t M, size_t N>
using ConstantMultiplyN = ConstantOperatorN<T, M, N, '*'>;

template <size_t N>
using ConstantSourceMultiplyN = ConstantMultiplyN<AbstractSource<N>, 0, N>;

template <size_t M, size_t N>
using ConstantProcessorMultiplyN = ConstantMultiplyN<Processor<M, N>, M, N>;

// Division template aliases
template <class T, size_t M, size_t N, bool Inverse=false>
using ConstantDivideN = ConstantOperatorN<T, M, N, '/', Inverse>;

template <size_t N, bool Inverse=false>
using ConstantSourceDivideN = ConstantDivideN<AbstractSource<N>, 0, N, Inverse>;

template <size_t M, size_t N, bool Inverse=false>
using ConstantProcessorDivideN = ConstantDivideN<Processor<M, N>, M, N,
                                                 Inverse>;

// Modulo template aliases
template <class T, size_t M, size_t N, bool Inverse=false>
using ConstantModuloN = ConstantOperatorN<T, M, N, '%', Inverse>;

template <size_t N, bool Inverse=false>
using ConstantSourceModuloN = ConstantModuloN<AbstractSource<N>, 0, N, Inverse>;

template <size_t M, size_t N, bool Inverse=false>
using ConstantProcessorModuloN = ConstantModuloN<Processor<M, N>, M, N,
                                                 Inverse>;

} // namespace operators
} // namespace thelonious

#endif
