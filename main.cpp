// main.cpp

// Stage 1: Amplitude and phase [V]
// Stage 2: Sum of sines [V]
// Stage 3: FFT [*]
// Stage 5: STFT []

#include <complex>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <cmath>

#include "core/Generators/SineGenerator.h"

#include "core/Processing/SignalOps.h"
#include "core/Processing/FFT.h"

#include "ui/ConsoleUI.h"

int main() {

  Signal signal = createSineSignalFromUser();

  std::vector<std::complex<double_t>> spectrum = FFT(signal);

  for (size_t k = 0; k < spectrum.size(); k++) {
    std::cout << "k: " << k << " magnitude: " << std::abs(spectrum[k]) << '\n'; 
  }
  
  return 0;
}
