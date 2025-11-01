#pragma once
#include <Arduino.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class BiquadFilterCore {
public:
  float b0, b1, b2, a1, a2;
  float x1, x2, y1, y2;

  BiquadFilterCore() : b0(1), b1(0), b2(0), a1(0), a2(0),
                   x1(0), x2(0), y1(0), y2(0) {}

  inline float process(float x) {
    float y = b0*x + b1*x1 + b2*x2 - a1*y1 - a2*y2;
    x2 = x1; x1 = x;
    y2 = y1; y1 = y;
    return y;
  }

  // ==============================
  // RBJ Filter Builders
  // ==============================

  static BiquadFilterCore makeLPF(float fs, float f0, float Q);
  static BiquadFilterCore makeHPF(float fs, float f0, float Q);
  static BiquadFilterCore makeBPF(float fs, float f0, float Q);
  static BiquadFilterCore makeNotch(float fs, float f0, float Q);
  static BiquadFilterCore makePeak(float fs, float f0, float Q, float gainDB);
  static BiquadFilterCore makeLowShelf(float fs, float f0, float Q, float gainDB);
  static BiquadFilterCore makeHighShelf(float fs, float f0, float Q, float gainDB);
  static BiquadFilterCore makeAllPass(float fs, float f0, float Q);

private:
  static void normalize(BiquadFilterCore& f, float a0);
};
