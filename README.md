# Thelonious

Thelonious is a C++11 audio DSP library.  It make complex audio processing super-simple to program, and easy to understand.

## Using Thelonious

Thelonious is a header-only library. It depends on the [RtAudio library](http://www.music.mcgill.ca/~gary/rtaudio/) for audio output.  To use Thelonious:

1. Install RtAudio

2. Include Thelonious by adding the following to your project:
    ```cpp
    #include "thelonious.h"
    ```

3. Add the directory which contains `thelonious.h` to your compiler's include path

4. When compiling your program, link against RtAudio (see [these instructions](http://www.music.mcgill.ca/~gary/rtaudio/compiling.html) for more details).

If you need faster compilation times then you can only include the parts of Thelonious which you need to use, for example:

```cpp
#include "thelonious/dsp/sine.h"
```

## Examples

### Hello sine

The musical eqivalent of a "hello world" program.  This example simply plays a sine wave through your speakers.  Notice how we use the right-shift operator (`>>`) to chain together audio processing blocks.

```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 220Hz sine wave generator
Sine sine(220.0f);

void onAudio() {
    // Play the sine wave through the audio device
    sine >> device;
}

int main() {
    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}
```

### Using parameters

A static sine wave isn't particularly interesting; now let's add some movement to the sound by adding a low-frequency oscillator (LFO).  The LFO will modulate the frequency of the sine wave, adding a vibrato effect.

There are a couple of key things to notice here:

* We set a parameter by shifting another generator into it.
* We can do arithmetic on the audio stream as if it were a normal numeric variable.


```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 220Hz sine wave generator
Sine sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
Triangle lfo(1.0f);

void onAudio() {
    // Use the LFO to make the frequency of the sine wave oscillate
    // between 215Hz and 225Hz
    lfo * 10.0f + 220.0f >> sine.frequency;

    // Play the sine wave through the audio device
    sine >> device;
}

int main() {
    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}
```

### Adding an envelope

Rather than playing a continuous tone, it would be nice to play a shorter note.  A sequence of notes could then be used to produce something more musical.  Notice how we can trigger the envelope by right-shifting a value into its gate parameter.  Also how we can multiply the sine wave and the envelope to control the volume of the oscillator.

```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 220Hz sine wave generator
Sine sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
Triangle lfo(1.0f);

// Create a percussive envelope, with a half-second attack phase and a 1
// second release phase
PercussiveEnvelope envelope(0.5f, 1.0f);

void onAudio() {
    // Use the LFO to make the frequency of the sine wave oscillate
    // between 215Hz and 225Hz
    lfo * 10.0f + 220.0f >> sine.frequency;

    // Apply the envelope to the sine wave, and play it through the audio
    // device
    sine * envelope >> device;
}

int main() {
    // Trigger the envelope
    1.0 >> envelope.gate;

    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}
```


### Chaining effects

Right-shift (>>) operations can be chained together to pass a generator through a series of effects.  In this example we pass a sawtooth wave through a filter and a delay effect.

```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 110Hz sawtooth wave generator
Saw saw(110.0f);

// Create a percussive envelope, with a short attack and release phase
PercussiveEnvelope envelope(0.05f, 0.05f);

// Create a low-pass filter, with a corner frequency of 220Hz
LowPassFilter lpf(220.0f);

// Create a delay effect.  The empty template arguments (<>) mean that we
// use the default maximum delay time of 0.2 seconds.
FeedbackDelay<> delay;

void onAudio() {
    // Apply the envelope to the sawtooth wave, pass it through the
    // filter and delay efects, and play it through the audio device
    saw * envelope >> lpf >> delay >> device;
}

int main() {
    // Trigger the envelope
    1.0f >> envelope.gate;

    // Call the onAudio function when the device needs audio generating
    device.onAudio(onAudio);
    // Start the audio playing
    device.start();

    // Wait for a keypress to exit
    std::cin.get();
}
```

### TODO: Multichannel units

So far we have only worked with monophonic (single-channel) sound.  Almost all of the units in Thelonious are also able to work with multi-channel audio data.

### TODO: Creating your own units

#### TODO: With your own DSP algorithm


## API Documentation

### Core

#### Storage types

```cpp
// A single sample
Sample sample;

// A std::array of 1024 samples
Channel<1024> channel;

// A buffer consisting of two channels of 1024 samples
Buffer<2, 1024> buffer;

// A channel of length BLOCK_SIZE
Chock chock;

// A buffer consisting of of two chocks
Block<2> block;
```

The five fundamental audio storage types used by Thelonious.  Thelonious processes audio using fixed-length buffers - Chock and Block are simply specializations of Channel and Buffer so we save a few keystrokes when doing DSP work.

All of the storage types can be operated on using the standard arithmetic operators.  Arithmetic between channels and buffers must be carried out between equivalent types and sizes.  For example you cannot multiply a buffer by a channel, or add a single-channel buffer to a two-channel buffer.

#### Unit

```cpp
template<size_t N>
class Unit;
```

Unit is the base class for all units in Thelonious.  It is subdivided into three different classes - sources, processors and sinks.

```cpp
virtual void UnitN::tick(Block<N> &block);
```

Generate the next block of samples by reading or writing values from `block`.

#### Source

```cpp
template<size_t N>
class Source : public Unit<N>;
```

Sources are units which generate audio signals.  They can be operated on using the standard arithmetic operators (which produce UnitOperator sources), and can be processed using the right-shift operator.

#### Processor

```cpp
template<size_t N>
class Processor : public Unit<N>;
```

Processors are units which modify audio signals.  They can be operated on using  the standard arithmetic operators (which produce UnitOperator sources), and can be processed using the right-shift operator.

#### Sink

```cpp  
template<size_t N>
class Sink : public Unit<N>;
```

Sinks are units which receive audio signals from sources or processors.

#### Parameter

```cpp
class Parameter : public Duplex<N>;
```

Parameters provide variable streams of values to units.  They can either be static, where they hold a single value, or dynamic, where they use the values taken from an audio source.  Static parameters can be made to interpolate from the previous value when a new value is set in order to give glitch-free changes to the audio.

```cpp
Parameter::Parameter(Sample value=0.0f, Interpolation interpolation=LINEAR);
```

Constructor.  Creates a parameter with an initial static value of `value`, which interpolates between static values using a given interpolation type (NONE, LINEAR or CUBIC).

```cpp
const Chock& Parameter::get();
```

Get a chock containing the values of the parameter for this tick.  Generally only called internally by units which implement their own DSP algorithms.

```cpp
void Parameter::tick(Block<1> &block);
```

Get the values of the parameter for this tick.  Generally only called           internally by units which are constructed from other units.  It can also be     accessed by right-shifting the parameter into an audio stream, for example      `parameter >> unit.parameter`.

```cpp
void Parameter::set(Sample value);
```

Set the static value of the parameter.  This can be also be accessed by right-shifting a sample into the parameter, for example `0.5f >> parameter`.

```cpp
void Parameter::tickIn(Block<1> &block);
```

Set the dynamic value of the parameter from a single-channel block.  This needs to be called each once per tick.  It can also be accessed by right-shifting an audio stream into the parameter, for example `oscillator >> parameter`.

```cpp
Interpolation Parameter::getInterpolation();
```

Return the current interpolation type (NONE, LINEAR or CUBIC).

```cpp
void Parameter::setInterpolation(Interpolation interpolation);
```

Return the current interpolation type (NONE, LINEAR or CUBIC).

#### Utility functions

```cpp
Sample modulo(Sample a, Sample b);
Sample wrap(Sample a, Sample b);
Sample moduloB(Sample a, Sample b);
```

Functions which calcluate a - floor(a / b) * b.  This is slightly different from the standard % modulo as negative numbers wrap to positive numbers (a more common operation in audio DSP).

The moduloB function is designed to be used in situations where both of the following are true:

1. Division is expensive
2. a is likely to be within or very close to b

```cpp
constexpr uint32_t secondsToSamples(float seconds);
```

Calculate the number of samples in a certain period of time.

```cpp
constexpr float samplesToSeconds(uint32_t samples);
```

Calculate the time it would take to play a certain number of samples.

```cpp
Sample linearInterpolate(Sample start, Sample end, Sample position);
```

Calculate the linear interpolation between two samples at a certain position.

### DSP

#### Oscillators

##### Sine

```cpp
template <size_t N>
class SineN : public Source<N>;

typedef SineN<1> Sine;
```

A sine wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset in radians.

```cpp
SineN::SineN(Sample frequency=440.0f, Sample phase=0.0f);
```

Constructor.  Creates an oscillator with a given initial frequency and phase offset.

##### Triangle

```cpp
template <size_t N>
class TriangleN : public Source<N>;

typedef TriangleN<1> Triangle;
```

A triangle wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset.  Between -1 and 1.

```cpp
TriangleN::TriangleN(Sample frequency=440.0f, Sample phase=0.0f);
```

Constructor.  Creates an oscillator with a given initial frequency and phase    offset.

##### Saw

```cpp
template <size_t N>
class SawN : public Source<N>;

typedef SawN<1> Saw;
```

A sawtooth wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset.  Between -1 and 1.

```cpp
SawN::SawN(Sample frequency=440.0f, Sample phase=0.0f);
```

Constructor.  Creates an oscillator with a given initial frequency and phase    offset.

##### Pulse

```cpp
template <size_t N>
class PulseN : public Source<N>;

typedef PulseN<1> Pulse;
```

A pulse wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* width - The duty-cycle of the wave.  Between 0 and 1.  A width of 0.5 gives a square wave.

```cpp
PulseN::PulseN(Sample frequency=440.0f, Sample width=0.5f);
```

Constructor.  Creates an oscillator with a given initial frequency and pulse width.

##### DPWTriangle

```cpp
template <size_t N>
class DPWTriangleN : public Source<N>

typedef DPWTriangleN<1> DPWTriangle;
```

An alias-reduced traingle wave oscillator created using the DPW (Differentiated Parabolic Wave) technique.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset.  Between -1 and 1.

```cpp
DPWTriangleN::DPWTriangleN(Sample frequency=440.0f, Sample phase=0.0f);
```

Constructor.  Creates an oscillator with a given initial frequency and phase    offset.

##### DPWSaw

```cpp
template <size_t N>
class DPWSawN : public Source<N>

typedef DPWSawN<1> DPWSaw;
```

An alias-reduced sawtooth wave oscillator created using the DPW (Differentiated Parabolic Wave) technique.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset.  Between -1 and 1.

```cpp
DPWSawN::DPWSawN(Sample frequency=440.0f, Sample phase=0.0f);
```

Constructor.  Creates an oscillator with a given initial frequency and phase    offset.

##### DPWPulse

```cpp
template <size_t N>
class DPWPulseN : public Source<N>

typedef DPWPulseN<1> DPWPulse;
```

An alias-reduced traingle wave oscillator created using the DPW (Differentiated Parabolic Wave) technique.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* width - The duty-cycle of the wave.  Between 0 and 1.  A width of 0.5 gives a square wave.

```cpp
DPWPulseN::DPWPulseN(Sample frequency=440.0f, Sample width=0.5f);
```

Constructor.  Creates an oscillator with a given initial frequency and pulse    width.

#### Noise

```cpp
template <size_t N>
class WhiteNoiseN : public Source<N>

typedef WhiteNoiseN<1> WhiteNoise;
```

A white noise generator.  Produces random values between -1 and +1.

*Parameters*:

None.

```cpp
WhiteNoise::WhiteNoise();
```

Constructor.

#### Filters

##### BiquadFilter

```cpp
template <size_t N>
class BiquadFilter : public Processor<N>
```

A generic biquad filter.  Designed to be subclassed, overriding the calculateCoefficients method.

*Parameters*:

* frequency - The corner frequency of the filter.
* damping - The damping factor (reciprocal Q) of the filter.

```cpp
BiquadFilter::BiquadFilter(Sample frequency, Sample damping)
```

Constructor.  Sets the initial frequency and damping values.

```cpp
virtual void BiquadFilter::calculateCoefficients(Sample frequency,
                                                 Sample damping) = 0;
```

Pure virtual method.  This should set the biquad coefficients (a0, a1, a2, b0, b1, b2) in the coefficients struct based on the supplied frequency and damping values.

##### LowPassFilter

```cpp
template <size_t N>
class LowPassFilterN : public BiquadFilter<N>

typedef LowPassFilterN<1> LowPassFilter;
```

A low pass biquad filter.

*Parameters*:

* frequency - The corner frequency of the filter.
* damping - The damping factor (reciprocal Q) of the filter.

```cpp
LowPassFilter::LowPassFilterN(Sample frequency=440.0f,
                              Sample damping=2.0f*constants::ROOT_HALF);
```

Constructor.  Creates a low pass filter with a given frequency and damping.  The default damping value creates a filter with a Butterworth response.

##### BandPassFilter

```cpp
template <size_t N>
class BandPassFilterN : public BiquadFilter<N>

typedef BandPassFilterN<1> BandPassFilter;
```

A band pass biquad filter.

*Parameters*:

* frequency - The corner frequency of the filter.
* damping - The damping factor (reciprocal Q) of the filter.


```cpp
BandPassFilter::BandPassFilterN(Sample frequency=440.0f,
                              Sample damping=2.0f*constants::ROOT_HALF);
```

Constructor.  Creates a band pass filter with a given frequency and damping.    The default damping value creates a filter with a Butterworth response.

##### HighPassFilter

```cpp
template <size_t N>
class HighPassFilterN : public BiquadFilter<N>

typedef HighPassFilterN<1> HighPassFilter;
```

A high pass biquad filter.

*Parameters*:

* frequency - The corner frequency of the filter.
* damping - The damping factor (reciprocal Q) of the filter.


```cpp
HighPassFilter::HighPassFilterN(Sample frequency=440.0f,
                              Sample damping=2.0f*constants::ROOT_HALF);
```

Constructor.  Creates a high pass filter with a given frequency and damping.  The default damping value creates a filter with a Butterworth response.

#### Delays

##### FeedbackDelay

```cpp
template <size_t N, size_t bufferSize=secondsToSamples(0.2)>
class FeedbackDelayN : public Processor<N>;

typedef FeedbackDelayN<1> FeedbackDelay;
```

A feedback delay line.  The second template argument determines the size of the fixed-length buffer used in the delay line.

*Parameters*:

* time - The delay time in seconds, ranging between 0 and samplesToSeconds(bufferSize).
* feedback - The level of feedback.

```cpp
FeedbackDelayN::FeedbackDelayN(Sample time=0.2f, Sample feedback=0.5f);
```

Constructor.  Creates a delay with a given delay time and feedback level.

#### Envelopes

##### Envelope

```cpp
template <size_t N>
class EnvelopeN : public Source<N>

typedef EnvelopeN<1> Envelope;
```

A generic envelope consisting of a series of segments.

*Parameters*:

* gate - A simple gate.  A transition between zero and a positive value causes the envelope to trigger, and a transition between a positive value and zero releases the envelope.

```
EnvelopeN::EnvelopeN(Sample initialValue,
                     std::vector<Sample> values,
                     std::vector<Sample> durations, int releaseNode=-1);
```

Constructor.  Creates an envelope with an initial value, and a series of segment end values and segment durations.  After the envelope has been triggered for the first time, any retriggers will cause the envelope to transition to the first value from the existing output value.

If the releaseNode variable is set, the envelope will sustain at the corresponding value until the gate is released.

##### PercussiveEnvelope

```cpp
template <size_t N>
class PercussiveEnvelopeN : public Envelope<N>

typedef PercussiveEnvelopeN<1> PercussiveEnvelope;
```

A simple envelope consisting of an attack phase and a release phase.

*Parameters*:
                                                                                * gate - A simple gate.  A transition between zero and a positive value causes  the envelope to trigger.

```cpp
PercussiveEnvelopeN::PercussiveEnvelopeN(Sample attack, Sample release);
```

Constructor.  Creates an envelope with a given attack and release time.

##### ASREnvelope

```cpp
template <size_t N>
class ASREnvelopeN : public EnvelopeN<N>;
```

An envelope consisting of an attack phase, a sustain phase and a release phase.

*Parameters*:

* gate - A simple gate.  A transition between zero and a positive value causes  the envelope to trigger, and a transition between a positive value and zero     releases the envelope.

```cpp
ASREnvelopeN::ASREnvelopeN(float attack, float sustain, float release);
```

Constructor.  Creates an envelope with a given attack time, a level to sustain at, and a release time.

##### ADSREnvelope

```cpp
template <size_t N>
class ADSREnvelopeN : public EnvelopeN<N>;
```

An envelope consisting of an attack phase, a decay phase, a sustain phase and a release phase.

*Parameters*:

* gate - A simple gate.  A transition between zero and a positive value causes  the envelope to trigger, and a transition between a positive value and zero     releases the envelope.

```cpp
ADSREnvelopeN::ADSREnvelopeN(float attack, float decay, float sustain,
                             float release);
```

Constructor.  Creates an envelope with a given attack time, a delay time, a level to sustain at, and a release time.

#### Triggers

##### Trigger

```cpp
template <size_t N>
class TriggerN : public Source<N>;

typedef TriggerN<1> Trigger;
```

A unit used to generate single-sample impulses when it is triggered.

*Parameters*:

* trigger - Causes a single-sample impulse to be output when it is set to a positive value.

```cpp
TriggerN::TriggerN(Sample trigger=0.0f);
```

Constructor.  Creates a trigger with an initial trigger state.

#### Splitters

##### Splitter

```cpp
template <size_t N>
class SplitterN : public Duplex<N>;

typedef SplitterN<1> Splitter;
```

A class used to split audio signals so they can be used in more than once.  For example to trigger two envelopes with one trigger:

```cpp
trigger >> splitter;
splitter >> frequencyEnvelope.gate;
splitter >> amplitudeEnvelope.gate;
```

*Parameters*:

None.

```cpp
SplitterN()::SplitterN();
```

### TODO: Operators

Operator units work in a similar way to the standard mathematical operators, except they are able to take advantage of the interpolation built into the Parameter unit.  They should be used when you need smooth transitions between operands.





