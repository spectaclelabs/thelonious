# Thelonious

Thelonious is a C++11 audio DSP library.  It make complex audio processing super-simple to program, and easy to understand.

## Using Thelonious

Thelonious is a header-only library. To use Thelonious:

1. Include Thelonious by adding the following to your project:
```cpp
    #include "thelonious.h"
    ```

2. Add the directory which contains `thelonious.h` to your compiler's include path

If you need faster compilation times then you can only include the parts of Thelonious which you need to use, for example:

```cpp
#include "thelonious/dsp/sine.h"
```

## Examples

### Hello sine

The musical eqivalent of a "hello world" program.  This example simply plays a sine wave through your speakers.  Notice how we use the left-shift operator (`>>`) to chain together audio processing blocks.

```cpp
#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 220Hz sine wave generator
Sine sine(220.0f);

int main() {
    while (1) {
        // Play the sine wave through the audio device
        sine >> device;
    }
}
```

### Using parameters

A static sine wave isn't particularly interesting; now let's add some movement to the sound by adding a low-frequency oscillator (LFO).  The LFO will modulate the frequency of the sine wave, adding a vibrato effect.

There are a couple of key things to notice here:

* We set a parameter by shifting another generator into it.
* We can do arithmetic on the audio stream as if they were a normal numeric variable.


```cpp
#include "thelonious.h"

using namespace thelonious;

// Create an audio device
AudioDevice device;

// Create a 220Hz sine wave generator
Sine sine(220.0f);

// Create a 1Hz trigangle wave LFO for a vibrato effect
Triangle lfo(1.0f);

int main() {
    while (1) {
        // Use the LFO to make the frequency of the sine wave oscillate
        // between 210Hz and 230Hz
        lfo * 20.0f + 220.0f >> sine.frequency

        // Play the sine wave through the audio device
        sine >> device;
    }
}
```

### Adding an envelope

Rather than playing a continuous tone, it would be nice to play a shorter note.  A sequence of notes could then be used to produce something more musical.

### Chaining effects

### Multichannel units

### Creating your own units

#### With your own DSP algorithm


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
class UnitN;
```

UnitN is the base class for all units in Thelonious.  It can be operated on using the standard arithmetic operators (which produce UnitOperator units), and can be processed using the left-shift operator.

```cpp
virtual void UnitN::tick(Block<N> &block);
```

Generate the next block of samples by reading and writing values to `block`.

#### Parameter

```cpp
class Parameter;
```

Parameters provide variable streams of values to units.  They can either be static, where they hold a single value, or dynamic, where they use the values taken from an audio source.  Static parameters can be made to interpolate from the previous value when a new value is set in order to give glitch-free changes to the audio.

```cpp
Parameter::Parameter(Sample value=0.0f, Interpolation interpolation=LINEAR);
```

Constructor.  Creates a parameter with an initial static value of `value`, which interpolates between static values using a given interpolation type (NONE, LINEAR or CUBIC).

```cpp
const Chock& Parameter::get();
```

Get a chock containing the values of the parameter for this tick.  Generally only called internally by units.

```cpp
void Parameter::set(Sample value);
```

Set the static value of the parameter.  This can be also be accessed by left-shifting a sample into the parameter, for example `0.5f >> parameter`.

```
void Parameter::set(const Chock& chock);
void Parameter::set(const Block<1> &block);
```
Set the dynamic value of the parameter from either a chock or a single-channel block.  This needs to be called each once per tick.  It can also be accessed by left-shifting an audio stream into the parameter, for example `oscillator >> parameter`.

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

Calculate the linearly interpolation between two samples at a certain position.

### DSP

#### Oscillators

##### Sine

```cpp
template <size_t N>
class SineN : public Unit<N>;

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
class TriangleN : public Unit<N>;

typedef TriangleN<1> Triangle;
```

A triangle wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset.  Between -1 and 1.

```cpp
TriangleN::TriangleN(Sample frequency=440.0f, Sample phase=0.0f)
```

Constructor.  Creates an oscillator with a given initial frequency and phase    offset.

##### Saw

```cpp
template <size_t N>
class SawN : public Unit<N>;

typedef SawN<1> Saw;
```

A sawtooth wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* phase - Phase offset.  Between -1 and 1.

```cpp
SawN::SawN(Sample frequency=440.0f, Sample phase=0.0f)
```

Constructor.  Creates an oscillator with a given initial frequency and phase    offset.

##### Pulse

```cpp
template <size_t N>
class PulseN : public Unit<N>;

typedef PulseN<1> Pulse;
```

A pulse wave oscillator.

*Parameters*:

* frequency - Frequency of the oscillator in Hz.
* width - The duty-cycle of the wave.  Between 0 and 1.  A width of 0.5 gives a square wave.

```cpp
PulseN::PulseN(Sample frequency=440.0f, Sample width=0.5f)
```

Constructor.  Creates an oscillator with a given initial frequency and pulse width.

#### Filters

#### Delays

#### Envelopes


### Operators






