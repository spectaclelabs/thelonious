#ifndef THELONIOUS_H
#define THELONIOUS_H

/* Core */
#include "thelonious/util.h"
#include "thelonious/unit.h"
#include "thelonious/source.h"
#include "thelonious/processor.h"
#include "thelonious/sink.h"
#include "thelonious/parameter.h"
#include "thelonious/types.h"
#include "thelonious/audio_device.h"

/* Constants */
#include "thelonious/constants/sizes.h"
#include "thelonious/constants/rates.h"

/* Operators */
#include "thelonious/operators/operator.h"
#include "thelonious/operators/unit_binary_operator.h"
#include "thelonious/operators/unit_unary_operator.h"
#include "thelonious/operators/constant_operator.h"
#include "thelonious/operators/unit_tick.h"

/* DSL */
#include "thelonious/dsl/buffer.h"
#include "thelonious/dsl/channel.h"
#include "thelonious/dsl/constant.h"
#include "thelonious/dsl/tick.h"
#include "thelonious/dsl/unit.h"

/* Oscillators */
#include "thelonious/dsp/oscillators/sine.h"
#include "thelonious/dsp/oscillators/saw.h"
#include "thelonious/dsp/oscillators/pulse.h"
#include "thelonious/dsp/oscillators/triangle.h"
#include "thelonious/dsp/oscillators/dpw_saw.h"
#include "thelonious/dsp/oscillators/dpw_pulse.h"
#include "thelonious/dsp/oscillators/dpw_triangle.h"
#include "thelonious/dsp/oscillators/silence.h"

/* Noise */
#include "thelonious/dsp/noise/white_noise.h"

/* Filters */
#include "thelonious/dsp/filters/biquad_filter.h"
#include "thelonious/dsp/filters/low_pass_filter.h"
#include "thelonious/dsp/filters/high_pass_filter.h"
#include "thelonious/dsp/filters/band_pass_filter.h"

/* Delays */
#include "thelonious/dsp/delays/feedback_delay.h"
#include "thelonious/dsp/delays/reverb.h"

/* Envelopes */
#include "thelonious/dsp/envelopes/envelope.h"
#include "thelonious/dsp/envelopes/percussive_envelope.h"
#include "thelonious/dsp/envelopes/asr_envelope.h"
#include "thelonious/dsp/envelopes/adsr_envelope.h"

/* Triggers */
#include "thelonious/dsp/triggers/trigger.h"

/* Multichannel */
#include "thelonious/dsp/multichannel/fan.h"
#include "thelonious/dsp/multichannel/merge.h"
#include "thelonious/dsp/multichannel/split.h"
#include "thelonious/dsp/multichannel/upmix.h"
#include "thelonious/dsp/multichannel/downmix.h"
#include "thelonious/dsp/multichannel/select.h"
#include "thelonious/dsp/multichannel/multiselect.h"

// Flatten namespace hierarchy
namespace thelonious {

using namespace thelonious::operators;
using namespace thelonious::dsp::oscillators;
using namespace thelonious::dsp::noise;
using namespace thelonious::dsp::filters;
using namespace thelonious::dsp::envelopes;
using namespace thelonious::dsp::delays;
using namespace thelonious::dsp::triggers;
using namespace thelonious::dsp::multichannel;

}

#endif
