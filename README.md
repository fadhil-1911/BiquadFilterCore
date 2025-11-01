# BiquadFilterCore


**BiquadFilterCore** is a lightweight, high-precision digital signal processing (DSP) library for Arduino that implements all standard RBJ biquad filter types.  
Designed for **audio**, **waveform**, and **vibration** processing — ideal for EQs, synths, or DSP experiments.

---

## ✨ Features

- Implements all standard RBJ filters:
  - Low-pass, High-pass, Band-pass, Notch, All-pass
  - Peaking EQ, Low-shelf, High-shelf
- High numerical precision (float-based)
- Independent filter instance per channel
- Portable: works with AVR, ESP32, STM32, RP2040, etc.
- Simple, clean API for fast integration
- Fully documented example for testing and tuning

---

## ⚙️ API Overview

```cpp
#include <BiquadFilterCore.h>

BiquadFilter biquad;

void setup() {
  Serial.begin(115200);

  // Example: 1 kHz sampling, 100 Hz low-pass filter
  biquad.setFilter(BiquadFilter::LOWPASS, 1000.0f, 100.0f, 0.707f);
}

void loop() {
  float input = analogRead(A0) / 512.0f - 1.0f; // normalize signal
  float output = biquad.process(input);
  Serial.println(output);
}


LOWPASS
Passes low frequencies
Audio smoothing, tone shaping
HIGHPASS
Removes DC & low tones
AC coupling, de-rumble
BANDPASS
Isolates a specific frequency band
Resonance, tone selection
NOTCH
Removes narrow frequency bands
Hum rejection (e.g., 50 Hz)
PEAK
Boosts or cuts a frequency band
EQ band control
LOWSHELF
Boosts or cuts the low range
Bass EQ
HIGHSHELF
Boosts or cuts the high range
Treble EQ
ALLPASS
Alters phase without changing gain
Phase or delay compensation



