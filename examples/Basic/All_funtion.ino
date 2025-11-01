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
