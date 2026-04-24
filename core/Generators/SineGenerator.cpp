#include "SineGenerator.h"

SineGenerator::SineGenerator(double sampleRate, double frequency, double amplitude,
                double fractionPi, int duration)
      : generatedSignal(std::vector<double>(), 0)
  {
    int signalSize = static_cast<int>(sampleRate * duration);
    double phase = fractionPi * M_PI;
    std::vector<double> data(signalSize);
    
    for(int n = 0; n < signalSize; n++){
      data[n] = amplitude * sin((2.0 * M_PI * frequency * n/sampleRate) + phase);
    }

    generatedSignal = Signal(std::move(data), sampleRate);
  }


  Signal SineGenerator::getSignal(){
    return generatedSignal;
  }
