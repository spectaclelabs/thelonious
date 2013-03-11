// Based on fix.hpp from libfixmath

#ifndef THELONIOUS_FIXED_POINT_16_H
#define THELONIOUS_FIXED_POINT_16_H

#include "fix16.h"

class FixedPoint16 {
	public:
		fix16_t value;

		FixedPoint16() { value = 0; }
		FixedPoint16(const FixedPoint16 &inValue)  { value = inValue.value;             }
        FixedPoint16(const fix16_t inValue) { value = inValue;                   }
		FixedPoint16(const float inValue)   { value = fix16_from_float(inValue); }
        FixedPoint16(const uint32_t inValue) { value = fix16_from_int(inValue); }
        FixedPoint16(const size_t inValue) { value = fix16_from_int(inValue); }
        FixedPoint16(const bool inValue) { value = inValue ? fix16_from_int(1) : 0; }

        operator fix16_t() const { return value; }
		operator float()   const { return fix16_to_float(value); }
        operator bool() const { return value != 0; }
        operator uint32_t() const {return fix16_to_int(value); }

		FixedPoint16 & operator=(const FixedPoint16 &rhs)  { value = rhs.value;             return *this; }
		FixedPoint16 & operator=(const float rhs)   { value = fix16_from_float(rhs); return *this; }

		FixedPoint16 & operator+=(const FixedPoint16 &rhs)  { value += rhs.value;             return *this; }
		FixedPoint16 & operator+=(const float rhs)   { value += fix16_from_float(rhs); return *this; }

		FixedPoint16 & operator-=(const FixedPoint16 &rhs)  { value -= rhs.value; return *this; }
		FixedPoint16 & operator-=(const float rhs)   { value -= fix16_from_float(rhs); return *this; }

		FixedPoint16 & operator*=(const FixedPoint16 &rhs)  { value = fix16_mul(value, rhs.value); return *this; }
		FixedPoint16 & operator*=(const float rhs)   { value = fix16_mul(value, fix16_from_float(rhs)); return *this; }

		FixedPoint16 & operator/=(const FixedPoint16 &rhs)  { value = fix16_div(value, rhs.value); return *this; }
		FixedPoint16 & operator/=(const float rhs)   { value = fix16_div(value, fix16_from_float(rhs)); return *this; }

		const FixedPoint16 operator+(const FixedPoint16 &other) const  { FixedPoint16 ret = *this; ret += other; return ret; }
		const FixedPoint16 operator+(const float other) const   { FixedPoint16 ret = *this; ret += other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const FixedPoint16 sadd(const FixedPoint16 &other)  const { FixedPoint16 ret = fix16_sadd(value, other.value);             return ret; }
		const FixedPoint16 sadd(const float other)   const { FixedPoint16 ret = fix16_sadd(value, fix16_from_float(other)); return ret; }
#endif

		const FixedPoint16 operator-(const FixedPoint16 &other) const  { FixedPoint16 ret = *this; ret -= other; return ret; }
		const FixedPoint16 operator-(const float other) const   { FixedPoint16 ret = *this; ret -= other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const FixedPoint16 ssub(const FixedPoint16 &other)  const { FixedPoint16 ret = fix16_sadd(value, -other.value);             return ret; }
		const FixedPoint16 ssub(const float other)   const { FixedPoint16 ret = fix16_sadd(value, -fix16_from_float(other)); return ret; }
#endif

		const FixedPoint16 operator*(const FixedPoint16 &other) const  { FixedPoint16 ret = *this; ret *= other; return ret; }
		const FixedPoint16 operator*(const float other) const   { FixedPoint16 ret = *this; ret *= other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const FixedPoint16 smul(const FixedPoint16 &other)  const { FixedPoint16 ret = fix16_smul(value, other.value);             return ret; }
		const FixedPoint16 smul(const float other)   const { FixedPoint16 ret = fix16_smul(value, fix16_from_float(other)); return ret; }
#endif

		const FixedPoint16 operator/(const FixedPoint16 &other) const  { FixedPoint16 ret = *this; ret /= other; return ret; }
		const FixedPoint16 operator/(const float other) const   { FixedPoint16 ret = *this; ret /= other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const FixedPoint16 sdiv(const FixedPoint16 &other)  const { FixedPoint16 ret = fix16_sdiv(value, other.value);             return ret; }
		const FixedPoint16 sdiv(const float other)   const { FixedPoint16 ret = fix16_sdiv(value, fix16_from_float(other)); return ret; }
#endif

        const FixedPoint16 operator+() const   { return FixedPoint16(*this); }
        const FixedPoint16 operator-() const   { return FixedPoint16(*this) * -1.0f; }

		const int operator==(const FixedPoint16 &other)  const { return (value == other.value);             }
		const int operator==(const float other)   const { return (value == fix16_from_float(other)); }

		const int operator!=(const FixedPoint16 &other)  const { return (value != other.value);             }
		const int operator!=(const float other)   const { return (value != fix16_from_float(other)); }

		const int operator<=(const FixedPoint16 &other)  const { return (value <= other.value);             }
		const int operator<=(const float other)   const { return (value <= fix16_from_float(other)); }

		const int operator>=(const FixedPoint16 &other)  const { return (value >= other.value);             }
		const int operator>=(const float other)   const { return (value >= fix16_from_float(other)); }

		const int operator< (const FixedPoint16 &other)  const { return (value <  other.value);             }
		const int operator< (const float other)   const { return (value <  fix16_from_float(other)); }

		const int operator> (const FixedPoint16 &other)  const { return (value >  other.value);             }
		const int operator> (const float other)   const { return (value >  fix16_from_float(other)); }

};

FixedPoint16 operator+ (float a, const FixedPoint16 & b) {
    return FixedPoint16(fix16_from_float(a)) + b;
}

FixedPoint16 operator- (float a, const FixedPoint16 & b) {
    return FixedPoint16(fix16_from_float(a)) - b; 
}

FixedPoint16 operator* (float a, const FixedPoint16 & b) {
    return FixedPoint16(fix16_from_float(a)) * b;
}

FixedPoint16 operator/ (float a, const FixedPoint16 & b) {
    return FixedPoint16(fix16_from_float(a)) / b;
}


FixedPoint16 sin(const FixedPoint16 &value) {return FixedPoint16(fix16_sin(value));  }
FixedPoint16 cos(const FixedPoint16 &value) { return FixedPoint16(fix16_cos(value));  }
FixedPoint16 tan(const FixedPoint16 &value) { return FixedPoint16(fix16_tan(value));  }
FixedPoint16 asin(const FixedPoint16 &value) { return FixedPoint16(fix16_asin(value)); }
FixedPoint16 acos(const FixedPoint16 &value) { return FixedPoint16(fix16_acos(value)); }
FixedPoint16 atan(const FixedPoint16 &value) { return FixedPoint16(fix16_atan(value)); }
FixedPoint16 atan2(const FixedPoint16 &valueX, const FixedPoint16 &valueY) { return FixedPoint16(fix16_atan2(valueX, valueY)); } 
FixedPoint16 sqrt(const FixedPoint16 &value) { return FixedPoint16(fix16_sqrt(value)); }
FixedPoint16 abs(const FixedPoint16 &value) { return FixedPoint16(fix16_abs(value));  }
FixedPoint16 floor(const FixedPoint16 &value) { return FixedPoint16(fix16_floor(value));  }
FixedPoint16 ceil(const FixedPoint16 &value) { return FixedPoint16(fix16_ceil(value));  }
FixedPoint16 min(const FixedPoint16 &valueA, const FixedPoint16 & valueB) { return FixedPoint16(fix16_min(valueA, valueB)); }
FixedPoint16 max(const FixedPoint16 &valueA, const FixedPoint16 & valueB) { return FixedPoint16(fix16_max(valueA, valueB)); }
FixedPoint16 exp(const FixedPoint16 &value) { return FixedPoint16(fix16_exp(value)); } 
FixedPoint16 log(const FixedPoint16 &value) { return FixedPoint16(fix16_log(value)); }
#endif
