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

---

## Filter Types Overview

LOWPASS
Passes low frequencies. Commonly used for audio smoothing and tone shaping.

HIGHPASS
Removes DC and low tones. Useful for AC coupling and removing low-end rumble.

BANDPASS
Isolates a specific frequency band. Often used for resonance and tone selection.

NOTCH
Removes narrow frequency bands, such as power-line hum (e.g. 50 Hz).

PEAK
Boosts or cuts a specific frequency band. Ideal for EQ band control.

LOWSHELF
Boosts or cuts the low-frequency range. Used for bass adjustment or enhancement.

HIGHSHELF
Boosts or cuts the high-frequency range. Used for treble adjustment or enhancement.

ALLPASS
Changes only the phase response without affecting gain. Useful for delay or phase compensation.
