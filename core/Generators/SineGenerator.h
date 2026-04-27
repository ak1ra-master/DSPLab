#pragma once

#include "Generator.h"

#include <vector>
#include <cmath>
#include <utility>

class SineGenerator : public Generator {
private:
  Signal generatedSignal;

public:
  SineGenerator(double_t sampleRate, double_t frequency, double_t amplitude,
                double_t fractionPi, size_t duration);

  Signal getSignal() override;
};
