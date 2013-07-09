#ifndef THELONIOUS_OPERATORS_TYPES_H
#define THELONIOUS_OPERATORS_TYPES_H

#include <type_traits>

namespace thelonious {
namespace operators {

template <char value>
using OperatorType = std::integral_constant<char, value>;

typedef OperatorType<'+'> AdditionOperator;
typedef OperatorType<'-'> SubtractionOperator;
typedef OperatorType<'*'> MultiplicationOperator;
typedef OperatorType<'/'> DivisionOperator;
typedef OperatorType<'%'> ModuloOperator;

template <bool value>
using InverseType = std::integral_constant<bool, value>;

typedef InverseType<true> InverseOperator;
typedef InverseType<false> RegularOperator;


} // namespace operators
} // namespace thelonious

#endif
