#include <BiquadFilterCore.h>
#include <math.h>

BiquadFilterCore bpf;
float t = 0.0;
const float dt = 1.0 / 48000.0; // 48kHz sampling

void setup() {
  Serial.begin(115200);

  // Band-pass: center 2kHz, Q=1.0
  bpf = BiquadFilterCore::makeBPF(48000.0f, 2000.0f, 1.0f);

  Serial.println("Starting BPF test...");
}

void loop() {
  // Generate synthetic sine + noise signal
  float input = sin(2.0 * M_PI * 1000.0 * t) + 0.1 * ((rand() % 1000) / 1000.0 - 0.5);
  float output = bpf.process(input);

  Serial.println(output);

  t += dt;
  if (t >= 1.0) t = 0; // reset after 1 sec
}
