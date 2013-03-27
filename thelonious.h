#ifndef THELONIOUS_H
#define THELONIOUS_H

/* Core */
#include "thelonious/util.h"
#include "thelonious/unit.h"
#include "thelonious/parameter.h"
#include "thelonious/types.h"

/* Constants */
#include "thelonious/constants/sizes.h"
#include "thelonious/constants/rates.h"

/* Operators */
#include "thelonious/operators/add.h"
#include "thelonious/operators/subtract.h"
#include "thelonious/operators/multiply.h"
#include "thelonious/operators/divide.h"
#include "thelonious/operators/modulo.h"

/* Unit operators */
#include "thelonious/operators/unit_add.h"
#include "thelonious/operators/unit_subtract.h"
#include "thelonious/operators/unit_multiply.h"
#include "thelonious/operators/unit_divide.h"
#include "thelonious/operators/unit_modulo.h"

/* Constant operators */
#include "thelonious/operators/constant_add.h"
#include "thelonious/operators/constant_subtract.h"
#include "thelonious/operators/constant_multiply.h"
#include "thelonious/operators/constant_divide.h"
#include "thelonious/operators/constant_modulo.h"

/* Oscillators */
#include "thelonious/dsp/sine.h"
#include "thelonious/dsp/saw.h"
#include "thelonious/dsp/pulse.h"
#include "thelonious/dsp/triangle.h"
#include "thelonious/dsp/dpw_saw.h"
#include "thelonious/dsp/dpw_pulse.h"
#include "thelonious/dsp/dpw_triangle.h"

/* Noise */
#include "thelonious/dsp/white_noise.h"

/* Filters */
#include "thelonious/dsp/biquad_filter.h"
#include "thelonious/dsp/low_pass_filter.h"
#include "thelonious/dsp/high_pass_filter.h"
#include "thelonious/dsp/band_pass_filter.h"

/* Delay */
#include "thelonious/dsp/delay.h"
#include "thelonious/dsp/tap.h"

/* Envelopes */
#include "thelonious/dsp/envelope.h"

/* Triggers */
#include "thelonious/dsp/trigger.h"

// Flatten namespace hierarchy
namespace thelonious {

using namespace thelonious::operators;
using namespace thelonious::dsp;

}

#endif
