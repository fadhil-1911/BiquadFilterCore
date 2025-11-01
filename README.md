# BiquadFilterCore

Version 1.0.0

BiquadFilterCore is an Arduino library for designing and applying biquad filters in audio and signal processing applications.  
It provides a set of easy-to-use factory functions to create **Low-Pass, High-Pass, Band-Pass, Notch, Peaking EQ, Low/High-Shelf, and All-Pass filters** with floating-point precision.

---

## Features

- 8 types of biquad filters:
  - LOWPASS, HIGHPASS, BANDPASS, NOTCH
  - PEAK, LOWSHELF, HIGHSHELF, ALLPASS
- Float-based coefficient precision
- Factory-style constructors for easy filter creation
- Compatible with Arduino IDE and other embedded platforms

---

## Filter Types Overview

**LOWPASS** – Passes low frequencies. Used for audio smoothing and tone shaping.  
**HIGHPASS** – Removes DC and low frequencies. Useful for AC coupling and de-rumbling.  
**BANDPASS** – Isolates a specific frequency band. Ideal for resonance and tone selection.  
**NOTCH** – Removes narrow frequency bands (e.g., 50 Hz hum).  
**PEAK** – Boosts or cuts a specific frequency band. Useful for EQ band control.  
**LOWSHELF** – Boosts or cuts the low-frequency range. Used for bass EQ.  
**HIGHSHELF** – Boosts or cuts the high-frequency range. Used for treble EQ.  
**ALLPASS** – Changes only the phase response without affecting gain. Useful for delay compensation.

---

## Installation

1. Download the latest release from GitHub as a `.zip`.  
2. Open Arduino IDE → Sketch → Include Library → Add .ZIP Library.  
3. Include the library in your sketch:

```cpp
#include <BiquadFilterCore.h>


⸻

API / Functions with Parameter Descriptions

Function	Parameters	Description
makeLPF(fs, f0, Q)	fs = Sampling frequency in Hz, f0 = Cutoff frequency in Hz, Q = Quality factor	Creates a low-pass filter
makeHPF(fs, f0, Q)	Same as above	Creates a high-pass filter
makeBPF(fs, f0, Q)	Same as above	Creates a band-pass filter
makeNotch(fs, f0, Q)	Same as above	Creates a notch filter
makePeak(fs, f0, Q, gainDB)	fs = Sampling frequency in Hz, f0 = Center frequency in Hz, Q = Quality factor, gainDB = Gain in decibels (positive = boost, negative = cut)	Creates a peaking EQ filter
makeLowShelf(fs, f0, Q, gainDB)	fs = Sampling frequency in Hz, f0 = Shelf frequency in Hz, Q = Quality factor, gainDB = Gain in dB	Creates a low-shelf filter
makeHighShelf(fs, f0, Q, gainDB)	Same as above	Creates a high-shelf filter
makeAllPass(fs, f0, Q)	fs = Sampling frequency in Hz, f0 = Center frequency in Hz, Q = Quality factor	Creates an all-pass filter

All functions return a BiquadFilterCore object ready to process samples using .process(sample).

⸻

Input Normalization
	•	Normalized input (0..1): Divide analogRead() by 1023.0. Recommended for audio processing or float filters.
	•	Raw input (0..1023): Use analogRead() directly. Recommended for sensors or DAC output. Ensure gain is adjusted if needed.

float inputNorm = analogRead(A0) / 1023.0f;
float inputRaw  = analogRead(A0);


⸻

Example – Full Test Sketch

#include <BiquadFilterCore.h>

BiquadFilterCore lpf, hpf, bpf, notch, peak, lowShelf, highShelf, allPass;

void setup() {
  Serial.begin(115200);
  
  // Initialize filters with parameters explained
  lpf       = BiquadFilterCore::makeLPF(48000.0f, 1000.0f, 0.707f);       // fs=48kHz, f0=1kHz, Q=0.707
  hpf       = BiquadFilterCore::makeHPF(48000.0f, 500.0f, 0.707f);        // fs=48kHz, f0=500Hz, Q=0.707
  bpf       = BiquadFilterCore::makeBPF(48000.0f, 2000.0f, 1.0f);         // fs=48kHz, f0=2kHz, Q=1
  notch     = BiquadFilterCore::makeNotch(48000.0f, 50.0f, 5.0f);         // fs=48kHz, f0=50Hz, Q=5
  peak      = BiquadFilterCore::makePeak(48000.0f, 1000.0f, 1.0f, 6.0f);  // fs=48kHz, f0=1kHz, Q=1, gain=+6dB
  lowShelf  = BiquadFilterCore::makeLowShelf(48000.0f, 200.0f, 0.7f, 4.0f);// fs=48kHz, f0=200Hz, Q=0.7, gain=+4dB
  highShelf = BiquadFilterCore::makeHighShelf(48000.0f, 5000.0f, 0.7f,-3.0f);// fs=48kHz, f0=5kHz, Q=0.7, gain=-3dB
  allPass   = BiquadFilterCore::makeAllPass(48000.0f, 1000.0f, 0.707f);    // fs=48kHz, f0=1kHz, Q=0.707
  
  Serial.println("BiquadFilterCore full demo started");
}

void loop() {
  float inputNorm = analogRead(A0) / 1023.0f; // normalized
  float inputRaw  = analogRead(A0);          // raw

  // Process filters (normalized)
  float outLPF = lpf.process(inputNorm);
  float outHPF = hpf.process(inputNorm);
  float outBPF = bpf.process(inputNorm);
  float outNotch = notch.process(inputNorm);
  float outPeak = peak.process(inputNorm);
  float outLowShelf = lowShelf.process(inputNorm);
  float outHighShelf = highShelf.process(inputNorm);
  float outAllPass = allPass.process(inputNorm);

  // Print normalized results
  Serial.print("Norm IN: "); Serial.print(inputNorm,3);
  Serial.print(" | LPF: "); Serial.print(outLPF,3);
  Serial.print(" | HPF: "); Serial.print(outHPF,3);
  Serial.print(" | BPF: "); Serial.print(outBPF,3);
  Serial.println();
  
  delay(200);
}


⸻

License

MIT License

---







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
```

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
