// main.cpp

// Stage 1: Amplitude and phase [V]
// Stage 2: Sum of sines [*]
// Stage 3: FFT []
// Stage 5: STFT []

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <cmath>

std::vector<double> GenerateSignal(double sampleRate, double frequency, double amplitude, double fractionPi, int duration);

int main() {

  double sampleRate, frequency, amplitude, fractionPi;
  int duration;
  
  // Parameters  
  std::cout << "Please enter sampleRate: "; std::cin >> sampleRate;
  std::cout << "Please enter frequency: "; std::cin >> frequency;
  std::cout << "Please enter duration: "; std::cin >> duration;
  std::cout << "Please enter amplitude: "; std::cin >> amplitude;
  std::cout << "Please enter phase(fraction pi): "; std::cin >> fractionPi;
  

  // Sine wave generate 
  std::vector<double> signal = GenerateSignal(sampleRate, frequency, amplitude, fractionPi, duration);
  
  for (int n = 0; n < signal.size(); n++) {
    std::cout << "n: " << n << " Amplitude: " << signal[n] << '\n';
  }

  return 0;
}

// Generate a signal based on sampleRate, frequency and duration
std::vector<double> GenerateSignal(double sampleRate, double frequency,
                                   double amplitude, double fractionPi, int duration) {
  
  int signalSize = sampleRate * duration;

  double phase = fractionPi * M_PI;
  
  std::vector<double> signal(signalSize);

  for (int n = 0; n < signalSize; n++) {
    signal[n] = amplitude *  sin((2.0 * M_PI * frequency * n / sampleRate) + phase);
  }
  
  return signal;
}
