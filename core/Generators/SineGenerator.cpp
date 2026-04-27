#include "SineGenerator.h"
#include <cmath>

SineGenerator::SineGenerator(double_t sampleRate, double_t frequency, double_t amplitude,
			     double_t fractionPi, size_t duration)
      : generatedSignal(std::vector<double>(), 0)
  {
    size_t signalSize = static_cast<size_t>(sampleRate * duration);
    double_t phase = fractionPi * M_PI;
    std::vector<double_t> data(signalSize);
    
    for(size_t n = 0; n < signalSize; n++){
      data[n] = amplitude * sin((2.0 * M_PI * frequency * n/sampleRate) + phase);
    }

    generatedSignal = Signal(std::move(data), sampleRate);
  }


  Signal SineGenerator::getSignal(){
    return generatedSignal;
  }
