// main.cpp

// Stage 1: Amplitude and phase [V]
// Stage 2: Sum of sines [V]
// Stage 3: FFT [*]
// Stage 5: STFT []

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <cmath>

#include "core/Generators/SineGenerator.h"
#include "core/Processing/SignalOps.h"

#include "ui/ConsoleUI.h"

int main() {

  Signal signal1 = createSineSignalFromUser();

  printSignal(signal1);
  
  return 0;
}
