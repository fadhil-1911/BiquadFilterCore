#include "BiquadFilterCore.h"

/**
 * @brief Normalize filter coefficients by dividing all by a0
 */
void BiquadFilterCore::normalize(AudioDSPCore& f, float a0) {
  f.b0 /= a0;
  f.b1 /= a0;
  f.b2 /= a0;
  f.a1 /= a0;
  f.a2 /= a0;
}

/**
 * @brief Create a Low-Pass Filter
 * @param fs Sampling frequency (Hz)
 * @param f0 Cutoff frequency (Hz)
 * @param Q  Quality factor
 */
BiquadFilterCore BiquadFilterCore::makeLPF(float fs, float f0, float Q) {
  AudioDSPCore f;
  float w0 = 2.0f * M_PI * f0 / fs;
  float alpha = sin(w0) / (2.0f * Q);
  float cosw0 = cos(w0);

  float a0 = 1 + alpha;
  f.b0 = (1 - cosw0) / 2;
  f.b1 = 1 - cosw0;
  f.b2 = (1 - cosw0) / 2;
  f.a1 = -2 * cosw0;
  f.a2 = 1 - alpha;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create a High-Pass Filter
 */
BiquadFilterCore BiquadFilterCore::makeHPF(float fs, float f0, float Q) {
  AudioDSPCore f;
  float w0 = 2.0f * M_PI * f0 / fs;
  float alpha = sin(w0) / (2.0f * Q);
  float cosw0 = cos(w0);

  float a0 = 1 + alpha;
  f.b0 = (1 + cosw0) / 2;
  f.b1 = -(1 + cosw0);
  f.b2 = (1 + cosw0) / 2;
  f.a1 = -2 * cosw0;
  f.a2 = 1 - alpha;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create a Band-Pass Filter
 */
BiquadFilterCore BiquadFilterCore::makeBPF(float fs, float f0, float Q) {
  AudioDSPCore f;
  float w0 = 2.0f * M_PI * f0 / fs;
  float alpha = sin(w0) / (2.0f * Q);
  float cosw0 = cos(w0);

  float a0 = 1 + alpha;
  f.b0 = Q * alpha;
  f.b1 = 0;
  f.b2 = -Q * alpha;
  f.a1 = -2 * cosw0;
  f.a2 = 1 - alpha;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create a Notch Filter
 */
BiquadFilterCore BiquadFilterCore::makeNotch(float fs, float f0, float Q) {
  AudioDSPCore f;
  float w0 = 2.0f * M_PI * f0 / fs;
  float alpha = sin(w0) / (2.0f * Q);
  float cosw0 = cos(w0);

  float a0 = 1 + alpha;
  f.b0 = 1;
  f.b1 = -2 * cosw0;
  f.b2 = 1;
  f.a1 = -2 * cosw0;
  f.a2 = 1 - alpha;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create a Peaking EQ Filter
 * @param gainDB Gain in decibels (positive = boost, negative = cut)
 */
BiquadFilterCore BiquadFilterCore::makePeak(float fs, float f0, float Q, float gainDB) {
  AudioDSPCore f;
  float A = pow(10.0f, gainDB / 40.0f);
  float w0 = 2.0f * M_PI * f0 / fs;
  float alpha = sin(w0) / (2.0f * Q);
  float cosw0 = cos(w0);

  float a0 = 1 + alpha / A;
  f.b0 = 1 + alpha * A;
  f.b1 = -2 * cosw0;
  f.b2 = 1 - alpha * A;
  f.a1 = -2 * cosw0;
  f.a2 = 1 - alpha / A;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create a Low-Shelf Filter
 */
BiquadFilterCore BiquadFilterCore::makeLowShelf(float fs, float f0, float Q, float gainDB) {
  AudioDSPCore f;
  float A = pow(10.0f, gainDB / 40.0f);
  float w0 = 2.0f * M_PI * f0 / fs;
  float sinw0 = sin(w0);
  float cosw0 = cos(w0);
  float beta = sqrt(A) / Q;

  float a0 = (A + 1) + (A - 1) * cosw0 + beta * sinw0;
  f.b0 = A * ((A + 1) - (A - 1) * cosw0 + beta * sinw0);
  f.b1 = 2 * A * ((A - 1) - (A + 1) * cosw0);
  f.b2 = A * ((A + 1) - (A - 1) * cosw0 - beta * sinw0);
  f.a1 = -2 * ((A - 1) + (A + 1) * cosw0);
  f.a2 = (A + 1) + (A - 1) * cosw0 - beta * sinw0;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create a High-Shelf Filter
 */
BiquadFilterCore BiquadFilterCore::makeHighShelf(float fs, float f0, float Q, float gainDB) {
  AudioDSPCore f;
  float A = pow(10.0f, gainDB / 40.0f);
  float w0 = 2.0f * M_PI * f0 / fs;
  float sinw0 = sin(w0);
  float cosw0 = cos(w0);
  float beta = sqrt(A) / Q;

  float a0 = (A + 1) - (A - 1) * cosw0 + beta * sinw0;
  f.b0 = A * ((A + 1) + (A - 1) * cosw0 + beta * sinw0);
  f.b1 = -2 * A * ((A - 1) + (A + 1) * cosw0);
  f.b2 = A * ((A + 1) + (A - 1) * cosw0 - beta * sinw0);
  f.a1 = 2 * ((A - 1) - (A + 1) * cosw0);
  f.a2 = (A + 1) - (A - 1) * cosw0 - beta * sinw0;

  normalize(f, a0);
  return f;
}

/**
 * @brief Create an All-Pass Filter
 */
BiquadFilterCore BiquadFilterCore::makeAllPass(float fs, float f0, float Q) {
  AudioDSPCore f;
  float w0 = 2.0f * M_PI * f0 / fs;
  float alpha = sin(w0) / (2.0f * Q);
  float cosw0 = cos(w0);

  float a0 = 1 + alpha;
  f.b0 = 1 - alpha;
  f.b1 = -2 * cosw0;
  f.b2 = 1 + alpha;
  f.a1 = -2 * cosw0;
  f.a2 = 1 - alpha;

  normalize(f, a0);
  return f;
}
