#pragma once

#include <cmath>
#include <cstddef>
#include <vector>
#include <cstdint>

class Signal {
private:
  std::vector<double_t> samples;
  double sampleRate;

public:
  Signal();
      
  Signal(std::vector<double_t> &&signal, double_t __sampleRate__);

  std::size_t getSize() const;
  double getSample(size_t n) const;
  double getTime(size_t n) const;
  double getSampleRate() const;
};
