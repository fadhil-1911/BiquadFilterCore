#include <BiquadFilterCore.h>

BiquadFilterCore lpf;

void setup() {
  Serial.begin(115200);

  // Sampling rate 48kHz, cutoff 1kHz, Q=0.707
  lpf = BiquadFilterCore::makeLPF(48000.0f, 1000.0f, 0.707f);

  Serial.println("Starting LPF test...");
}

void loop() {
  // Simulated input: sine wave or analogRead
  float input = analogRead(A0);
  float output = lpf.process(input);

  Serial.println(output);

  delay(10); // simulate sampling interval ~100 Hz
}
