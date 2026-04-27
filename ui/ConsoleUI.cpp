#include "ConsoleUI.h"
#include <cmath>
#include <cstddef>

Signal createSineSignalFromUser() {
  double_t sampleRate, frequency, amplitude, fractionPi;
  size_t duration;

  // Parameters
  std::cout << "Please enter sampleRate: "; std::cin >> sampleRate;
  std::cout << "Please enter frequency: "; std::cin >> frequency;
  std::cout << "Please enter duration: "; std::cin >> duration;
  std::cout << "Please enter amplitude: "; std::cin >> amplitude;
  std::cout << "Please enter phase(fraction pi): "; std::cin >> fractionPi;

  // Generate signal by user parameters
  SineGenerator ssg(sampleRate, frequency, amplitude, fractionPi, duration);
  Signal sg = ssg.getSignal();
  
  return sg;
}

void printSignal(const Signal& signal) {

  for (size_t n = 0; n < signal.getSize(); n++) {
    std::cout << "n: " << n << " Amplitude: " << signal.getSample(n) << '\n';
  }

}
