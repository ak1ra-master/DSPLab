// main.cpp

// Stage 1: Amplitude and phase [V]
// Stage 2: Sum of sines [*]
// Stage 3: FFT []
// Stage 5: STFT []

//!!!!!Move the input parameters to the Generator class!!!!!!

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <cmath>

#include "core/Generators/SineGenerator.h"
#include "core/Processing/SignalOps.h"

int main() {

  double sampleRate, frequency, amplitude, fractionPi;
  int duration;
  
  // Parameters  
  std::cout << "Please enter sampleRate: "; std::cin >> sampleRate;
  std::cout << "Please enter frequency: "; std::cin >> frequency;
  std::cout << "Please enter duration: "; std::cin >> duration;
  std::cout << "Please enter amplitude: "; std::cin >> amplitude;
  std::cout << "Please enter phase(fraction pi): "; std::cin >> fractionPi;

  SineGenerator sineGen1(sampleRate, frequency, amplitude, fractionPi,
                         duration);
  
  std::cout << "Please enter sampleRate: "; std::cin >> sampleRate;
  std::cout << "Please enter frequency: "; std::cin >> frequency;
  std::cout << "Please enter duration: "; std::cin >> duration;
  std::cout << "Please enter amplitude: "; std::cin >> amplitude;
  std::cout << "Please enter phase(fraction pi): "; std::cin >> fractionPi;

  SineGenerator sineGen2(sampleRate, frequency, amplitude, fractionPi,
                         duration);

  Signal signal1 = sineGen1.getSignal();
  Signal signal2 = sineGen2.getSignal();

  Signal sumSignal = Addition(signal1, signal2);
  
  //Signal sineSignal = sineGen.getSignal();

  for (int n = 0; n < sumSignal.getSize(); n++) {
    std::cout << "n: " << n << " Amplitude: " << sumSignal.getSample(n) << '\n';        
  }
  
  return 0;
}
