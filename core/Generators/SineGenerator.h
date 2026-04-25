#pragma once

#include "Generator.h"

#include <vector>
#include <cmath>
#include <utility>

class SineGenerator : public Generator {
private:
  Signal generatedSignal;

public:
  SineGenerator(double sampleRate, double frequency, double amplitude,
                double fractionPi, int duration);

  Signal getSignal() override;
};
