#include <BiquadFilterCore.h>

BiquadFilterCore peq;

void setup() {
  Serial.begin(115200);

  // Boost 6 dB at 1kHz, Q=1
  peq = BiquadFilterCore::makePeak(48000.0f, 1000.0f, 1.0f, 6.0f);

  Serial.println("Starting Peaking EQ test...");
}

void loop() {
  float input = analogRead(A0) / 1023.0f;
  float output = peq.process(input);

  Serial.println(output);

  delay(10);
}
