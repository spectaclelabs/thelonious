// Based on fix.hpp from libfixmath

#ifndef THELONIOUS_FIXED_POINT_16_H
#define THELONIOUS_FIXED_POINT_16_H

#include "fix16.h"

class Fix16 {
	public:
		fix16_t value;

		Fix16() { value = 0; }
		Fix16(const Fix16 &inValue)  { value = inValue.value;             }
        Fix16(const fix16_t inValue) { value = inValue;                   }
		Fix16(const float inValue)   { value = fix16_from_float(inValue); }
        Fix16(const uint32_t inValue) { value = fix16_from_int(inValue); }
        Fix16(const size_t inValue) { value = fix16_from_int(inValue); }
        Fix16(const bool inValue) { value = inValue ? fix16_from_int(1) : 0; }

        operator fix16_t() const { return value; }
		operator float()   const { return fix16_to_float(value); }
        operator bool() const { return value != 0; }
        operator uint32_t() const {return fix16_to_int(value); }

		Fix16 & operator=(const Fix16 &rhs)  { value = rhs.value;             return *this; }
		Fix16 & operator=(const float rhs)   { value = fix16_from_float(rhs); return *this; }

		Fix16 & operator+=(const Fix16 &rhs)  { value += rhs.value;             return *this; }
		Fix16 & operator+=(const float rhs)   { value += fix16_from_float(rhs); return *this; }

		Fix16 & operator-=(const Fix16 &rhs)  { value -= rhs.value; return *this; }
		Fix16 & operator-=(const float rhs)   { value -= fix16_from_float(rhs); return *this; }

		Fix16 & operator*=(const Fix16 &rhs)  { value = fix16_mul(value, rhs.value); return *this; }
		Fix16 & operator*=(const float rhs)   { value = fix16_mul(value, fix16_from_float(rhs)); return *this; }

		Fix16 & operator/=(const Fix16 &rhs)  { value = fix16_div(value, rhs.value); return *this; }
		Fix16 & operator/=(const float rhs)   { value = fix16_div(value, fix16_from_float(rhs)); return *this; }

		const Fix16 operator+(const Fix16 &other) const  { Fix16 ret = *this; ret += other; return ret; }
		const Fix16 operator+(const float other) const   { Fix16 ret = *this; ret += other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const Fix16 sadd(const Fix16 &other)  const { Fix16 ret = fix16_sadd(value, other.value);             return ret; }
		const Fix16 sadd(const float other)   const { Fix16 ret = fix16_sadd(value, fix16_from_float(other)); return ret; }
#endif

		const Fix16 operator-(const Fix16 &other) const  { Fix16 ret = *this; ret -= other; return ret; }
		const Fix16 operator-(const float other) const   { Fix16 ret = *this; ret -= other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const Fix16 ssub(const Fix16 &other)  const { Fix16 ret = fix16_sadd(value, -other.value);             return ret; }
		const Fix16 ssub(const float other)   const { Fix16 ret = fix16_sadd(value, -fix16_from_float(other)); return ret; }
#endif

		const Fix16 operator*(const Fix16 &other) const  { Fix16 ret = *this; ret *= other; return ret; }
		const Fix16 operator*(const float other) const   { Fix16 ret = *this; ret *= other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const Fix16 smul(const Fix16 &other)  const { Fix16 ret = fix16_smul(value, other.value);             return ret; }
		const Fix16 smul(const float other)   const { Fix16 ret = fix16_smul(value, fix16_from_float(other)); return ret; }
#endif

		const Fix16 operator/(const Fix16 &other) const  { Fix16 ret = *this; ret /= other; return ret; }
		const Fix16 operator/(const float other) const   { Fix16 ret = *this; ret /= other; return ret; }

#ifndef FIXMATH_NO_OVERFLOW
		const Fix16 sdiv(const Fix16 &other)  const { Fix16 ret = fix16_sdiv(value, other.value);             return ret; }
		const Fix16 sdiv(const float other)   const { Fix16 ret = fix16_sdiv(value, fix16_from_float(other)); return ret; }
#endif

        const Fix16 operator+() const   { return Fix16(*this); }
        const Fix16 operator-() const   { return Fix16(*this) * -1.0f; }

		const int operator==(const Fix16 &other)  const { return (value == other.value);             }
		const int operator==(const float other)   const { return (value == fix16_from_float(other)); }

		const int operator!=(const Fix16 &other)  const { return (value != other.value);             }
		const int operator!=(const float other)   const { return (value != fix16_from_float(other)); }

		const int operator<=(const Fix16 &other)  const { return (value <= other.value);             }
		const int operator<=(const float other)   const { return (value <= fix16_from_float(other)); }

		const int operator>=(const Fix16 &other)  const { return (value >= other.value);             }
		const int operator>=(const float other)   const { return (value >= fix16_from_float(other)); }

		const int operator< (const Fix16 &other)  const { return (value <  other.value);             }
		const int operator< (const float other)   const { return (value <  fix16_from_float(other)); }

		const int operator> (const Fix16 &other)  const { return (value >  other.value);             }
		const int operator> (const float other)   const { return (value >  fix16_from_float(other)); }

};

Fix16 operator+ (float a, const Fix16 & b) {
    return Fix16(fix16_from_float(a)) + b;
}

Fix16 operator- (float a, const Fix16 & b) {
    return Fix16(fix16_from_float(a)) - b; 
}

Fix16 operator* (float a, const Fix16 & b) {
    return Fix16(fix16_from_float(a)) * b;
}

Fix16 operator/ (float a, const Fix16 & b) {
    return Fix16(fix16_from_float(a)) / b;
}


Fix16 sin(const Fix16 &value) {return Fix16(fix16_sin(value));  }
Fix16 cos(const Fix16 &value) { return Fix16(fix16_cos(value));  }
Fix16 tan(const Fix16 &value) { return Fix16(fix16_tan(value));  }
Fix16 asin(const Fix16 &value) { return Fix16(fix16_asin(value)); }
Fix16 acos(const Fix16 &value) { return Fix16(fix16_acos(value)); }
Fix16 atan(const Fix16 &value) { return Fix16(fix16_atan(value)); }
Fix16 atan2(const Fix16 &valueX, const Fix16 &valueY) { return Fix16(fix16_atan2(valueX, valueY)); } 
Fix16 sqrt(const Fix16 &value) { return Fix16(fix16_sqrt(value)); }
Fix16 abs(const Fix16 &value) { return Fix16(fix16_abs(value));  }
Fix16 floor(const Fix16 &value) { return Fix16(fix16_floor(value));  }
Fix16 ceil(const Fix16 &value) { return Fix16(fix16_ceil(value));  }
Fix16 min(const Fix16 &valueA, const Fix16 & valueB) { return Fix16(fix16_min(valueA, valueB)); }
Fix16 max(const Fix16 &valueA, const Fix16 & valueB) { return Fix16(fix16_max(valueA, valueB)); }
Fix16 exp(const Fix16 &value) { return Fix16(fix16_exp(value)); } 
Fix16 log(const Fix16 &value) { return Fix16(fix16_log(value)); }
#endif
