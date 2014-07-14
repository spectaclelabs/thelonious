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
auto device = AudioDevice();

// Create a 220Hz sine wave generator
auto sine = Sine(220.0f);

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
auto device = AudioDevice();

// Create a 220Hz sine wave generator
auto sine = Sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
auto lfo = Triangle(1.0f);

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
auto device = AudioDevice();

// Create a 220Hz sine wave generator
auto sine = Sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
auto lfo = Triangle(1.0f);

// Create a percussive envelope, with a half-second attack phase and a 1
// second release phase
auto envelope = PercussiveEnvelope(0.5f, 1.0f);

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
auto device = AudioDevice();

// Create a 110Hz sawtooth wave generator
auto saw = Saw(110.0f);

// Create a percussive envelope, with a short attack and release phase
auto envelope = PercussiveEnvelope(0.05f, 0.05f);

// Create a low-pass filter, with a corner frequency of 220Hz
auto lpf = LowPassFilter(220.0f);

// Create a delay effect.  The empty template arguments (<>) mean that we
// use the default maximum delay time of 0.2 seconds.
auto delay = FeedbackDelay<>();

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

### Multichannel units

So far we have only worked with monophonic (single-channel) sound.  Almost all of the units in Thelonious are also able to work with multi-channel audio data.  The number of channels is supplied as a template parameter to the *N* variants of the units.  So for example to create a two-channel Sine wave generator, rather than using the `Sine` class you would use the `SineN<2>` class.  In this example we will update our "hello sine" example to play a stereo sine wave:

```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create an audio device with no input channels and a stereo output
auto device = AudioDeviceN<0, 2>();

// Create a stereo 220Hz sine wave generator
auto sine = SineN<2>(220.0f);

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

### Creating your own units...

Now that you know how to create and manipulate sounds using Units, how about making some of your own?  In order to create a Unit you need to subclass one of the types of Unit and write a `tick` function which will carry out your audio processing.  In this example we create a kick-drum synthesizer and trigger it on a regular basis using an inequality.

```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// Create the kick class as a subclass of Source
template <size_t N>
class KickN : public Source<N> {
public:
    // Constructor initializes the two envelopes
    // Amplitude envelope goes from 0->1 in 0.01s, and from 1->0 in 0.5s
    // Frequency envelope goes from 80Hz->1Hz in 0.5s
    KickN() :
        amplitudeEnvelope(0.0f, {1.f, 0.0f}, {0.01f, 0.5f}),
        frequencyEnvelope(80.0f, {80.0f, 1.0f}, {0.01f, 0.5f}) {}

    void tick(Block<N> &block) {
        // Fan allows us to use a single trigger parameter to trigger both of the
        // envelopes
        trigger >> fan;
        fan >> frequencyEnvelope.gate;
        fan >> amplitudeEnvelope.gate;

        // Use the frequency envelope to control the frequency of the sine wave
        frequencyEnvelope >> sine.frequency;
        // Tick the kick output into the block
        sine * amplitudeEnvelope >> block;
    }

    // A trigger for the kick
    Parameter trigger;
    Fan fan;

    // The base waveform for our kick
    SineN<N> sine;

    // An amplitude envelope
    EnvelopeN<N> amplitudeEnvelope;
    EnvelopeN<N> frequencyEnvelope;
};

// Typedef the single-channel variant
typedef KickN<1> Kick;


// Create the audio device
auto device = AudioDevice();

// Create the kick
auto kick = Kick();

// Create a sawtooth wave for triggering the kick every second
auto saw = Saw(2);

void onAudio() {
    // Trigger the kick when the sawtooth wave passes through zero
    (saw > 0) >> kick.trigger;
    // Play the kick through the output
    kick >> device;
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

#### ...With your own DSP algorithm

You don't need to limit yourself to using the built-in DSP.  It is equally straightforward to write custom DSP code in your `tick` function.  In this example we will write a simple bit crusher which will reduce your sound to glorious 4-bit fidelity.

```cpp
#include <iostream>

#include "thelonious.h"

using namespace thelonious;

// A four-bit crusher
// Receives N channels, and outputs the same number of channels.
template <size_t N>
class FourBitN : public Processor<N, N> {
public:
    void tick(Block<N> &inputBlock, Block<N> &outputBlock) {
        // Loop through each channel
        for (uint32_t i=0; i<N; i++) {
            // Loop through each sample
            for (uint32_t j=0; j<constants::BLOCK_SIZE; j++) {
                // Scale the input to an integer between -8 and +8
                int8_t asFourBit = inputBlock[i][j] * 8;
                // Convert it back to a float send it to the output
                outputBlock[i][j] = asFourBit / 8.f;
            }
        }
    }
};

// Typedef the single-channel variant
typedef FourBitN<1> FourBit;


// Create the audio device
auto device = AudioDevice();

// A 220Hz sine wave
auto sine = Sine(220.f);

// The bit crusher
auto crusher = FourBit();

void onAudio() {
    // Bit crush the sine wave
    sine >> crusher >> device;
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
template<size_t M, size_t N>
class Unit;
```

Unit is the base class for all units in Thelonious.  It is subdivided into four different classes - sources, processors and sinks and duplexes.

```cpp
virtual void Unit::tick(Block<M> &inputBlock, Block<N> &outputBlock);
```

Generate the next block of samples by reading values from `inputBlock` and writing values to `outputBlock`.

#### AbstractSource

```cpp
template <size_t N>
class AbstractSource : public Unit<0, N>;
```

AbstractSource is the class which all objects which generate audio signals inherit from.  They can be operated on using the standard arithmetic operators (which produce UnitOperator sources), and can be processed using the right-shift operator.

#### Source

```cpp
template<size_t N>
class Source : public AbstractSource<N>;
```

Sources are units which only generate audio signals.  They inherit all of the abilities of AbstractSources.

```cpp
virtual void Source::tick(Block<M> &inputBlock, Block<N> &outputBlock);
```

Calls the virtual `Source::tick(Block<N> &block)` function.

```cpp
virtual void Source::tick(Block<N> &block);
```

Generate the next block of samples by writing values to `block`

#### Processor

```cpp
template<size_t M, size_t N>
class Processor : public Unit<M, N>;
```

Processors are units which modify audio signals.  They can be operated on using  the standard arithmetic operators (which produce UnitOperator sources), and can be processed using the right-shift operator.

#### AbstractSink

```cpp
template <size_t N>
class AbstractSink : public Unit<N, 0>;
```

AbstractSink is the class which all objects which receive audio signals inherit from.

#### Sink

```cpp  
template<size_t N>
class Sink : public AbstractSink<N>;
```

Sinks are units which receive audio signals from sources or processors.

```cpp
void Sink::tick(Block<N> &inputBlock, Block<0> &outputBlock);
```

Calls the virtual `Sink::tick(Block<N> &block)` function.

```cpp
virtual void Sink::tick(Block<N> &block);
```

Receive a block of samples by reading from `block`.

#### Duplex

```cpp
template <size_t M, size_t N>
class Duplex : public AbstractSource<N>, public AbstractSink<M>;
```

A duplex is a device which can simultaneously act as a source and a sink.  It is able to both receive samples and generate samples.  Note that this plays a different role to a Processor, as the receiving of samples and generation of samples are two seperate operations.

```cpp
void Duplex::tick(Block<0> &inputBlock, Block<N> &outputBlock);
```

Calls the virtual `Duplex::tickOut(Block<N> &block)` function.

```cpp
void Duplex::tick(Block<M> &inputBlock, Block<0> &outputBlock);
```

Calls the virtual `Duplex::tickIn(Block<M> &block)` function.

```cpp
virtual void Duplex::tickIn(Block<M> &block);
```

Receive a block of samples by reading from `block`.

```cpp
virtual void Duplex::tickOut(Block<N> &block);
```

Generate a block of samples by writing to `block`.

#### Parameter

```cpp
class Parameter : public Duplex<1, 1>;
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
void Parameter::tickOut(Block<1> &block);
```

Get the values of the parameter for this tick.  Generally only called internally by units which are constructed from other units.  It can also be accessed by right-shifting the parameter into an audio stream, for example `parameter >> unit.parameter`.

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

#### AudioDevice

```cpp
template <size_t M, size_t N>
class AudioDeviceN : public Duplex<N, M>;

typedef AudioDeviceN<1, 1> AudioDevice;
```

A unit which uses the RtAudio library to read and write audio from soundcards.  Audio can be output by ticking into a device, for example `oscillator >> device`.  Audio input can be read by ticking out of the device, for example `device >> processor`.  These operations can be combined to allow you to process live audio, for example `device >> processor >> device`.

*Parameters*:

None.

```cpp
AudioDeviceN::AudioDeviceN(int inputDevice=-1, int outputDevice=-1,
                           uint32_t numberOfBuffers=8);
```

Constructor.  Creates a device which reads from the soundcard with the id `inputDevice`, and writes to the soundcard with the id `outputDevice`.  The `numberOfBuffers` argument helps to control the input and output latency - see the [RtAudio documentation](http://www.music.mcgill.ca/~gary/rtaudio/index.html) for more information.

```cpp
void AudioDeviceN::start();
```

Start a stopped audio stream.

```cpp
void AudioDeviceN::stop();
```

Stop a started audio stream.

```cpp
void AudioDeviceN::onAudio(*onAudioCallback)());
```

Set the callback to be fired when audio is needed.


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
class BiquadFilter : public Processor<N, N>
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
class FeedbackDelayN : public Processor<N, N>;

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

##### Fan

```cpp
template <size_t N>
class FanN : public Duplex<N, N>;

typedef FanN<1> Fan;
```

A class used to split audio signals so they can be used in more than once.  For example to trigger two envelopes with one trigger:

```cpp
trigger >> fan;
fan >> frequencyEnvelope.gate;
fan >> amplitudeEnvelope.gate;
```

*Parameters*:

None.

```cpp
FanN::FanN();
```

Constructor.

### Operators

Operator units work in a similar way to the standard mathematical operators, except they are able to take advantage of the interpolation built into the Parameter unit.  They should be used when you need smooth transitions between operands.

Here is the documentation for the addition operator:

```cpp
template <size_t N>
class AddN: public Processor<N, N>;

typedef AddN<1> Add;
```

Adds a value to the audio signal.

*Parameters*:

* value - The value to add to the signal.

```cpp
AddN::AddN(Sample value=0.0f);
```

Constructor.  Creates the unit with a default value.

The full list of operator units is below.  Each of these units have identical methods and parameters to the `Add` unit.

* Add
* Subtract
* Mutliply
* Divide
* Modulo
* EqualTo
* LessThan
* GreaterThan
* LessThanOrEqualTo
* GreaterThanOrEqualTo

