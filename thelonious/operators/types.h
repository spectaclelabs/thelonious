#ifndef THELONIOUS_OPERATORS_TYPES_H
#define THELONIOUS_OPERATORS_TYPES_H

#include <type_traits>

namespace thelonious {
namespace operators {

enum Operator {
    // Binary arithmetic
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULO,
    // Binary comparison
    EQUAL_TO,
    NOT_EQUAL_TO,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN_OR_EQUAL_TO
};

template <Operator value>
using OperatorType = std::integral_constant<Operator, value>;

typedef OperatorType<ADDITION> AdditionOperator;
typedef OperatorType<SUBTRACTION> SubtractionOperator;
typedef OperatorType<MULTIPLICATION> MultiplicationOperator;
typedef OperatorType<DIVISION> DivisionOperator;
typedef OperatorType<MODULO> ModuloOperator;

typedef OperatorType<EQUAL_TO> EqualToOperator;
typedef OperatorType<NOT_EQUAL_TO> NotEqualToOperator;
typedef OperatorType<GREATER_THAN> GreaterThanOperator;
typedef OperatorType<LESS_THAN> LessThanOperator;
typedef OperatorType<GREATER_THAN_OR_EQUAL_TO> GreaterThanOrEqualToOperator;
typedef OperatorType<LESS_THAN_OR_EQUAL_TO> LessThanOrEqualToOperator;

template <bool value>
using InverseType = std::integral_constant<bool, value>;

typedef InverseType<true> InverseOperator;
typedef InverseType<false> RegularOperator;


} // namespace operators
} // namespace thelonious

#endif
