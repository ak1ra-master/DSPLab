#pragma once

#include "../Signal/Signal.h"
#include "FFT.h"
#include <cmath>
#include <cstddef>
#include <vector>

struct STFTResult {
  std::vector<std::vector<double_t>> magnitude;
  size_t windowSize;
  size_t hopSize;
};

STFTResult STFT(const Signal &signal, size_t windowSize, size_t hopSize);
