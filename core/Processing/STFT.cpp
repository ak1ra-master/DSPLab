#include "STFT.h"
#include <cmath>
#include <vector>

STFTResult STFT(const Signal &signal, size_t windowSize, size_t hopSize) {
  STFTResult result;
  result.windowSize = windowSize;
  result.hopSize = hopSize;

  size_t N = signal.getSize();
  
  for (size_t start = 0; start + windowSize <= N; start += hopSize) { // Main loop for sliding window

    std::vector<double_t> windowed(windowSize);

    for (size_t i = 0; i < windowSize; i++) {
      double_t sample = signal.getSample(start + i); // Get current sample from source signal

      double_t hann = 0.5 * (1.0 - std::cos(2.0 * M_PI * i / (windowSize - 1))); // Coefficient of the Hann function

      windowed[i] = sample * hann;
    }

    Signal windowSignal(std::move(windowed), signal.getSampleRate()); 

    std::vector<std::complex<double_t>> spectrum = FFT(windowSignal);

    std::vector<double_t> mag(windowSize / 2);

    for (size_t k = 0; k < windowSize / 2; k++) { // Trimming the second half of the data because the data is mirrored
      mag[k] = std::abs(spectrum[k]); // Amplitude calculation
    }

    result.magnitude.push_back(mag);
  }

  return result;
  
}
