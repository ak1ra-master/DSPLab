#include "Signal.h"
#include <cstddef>
#include <utility>

Signal::Signal(std::vector<double_t> &&signal, double_t __sampleRate__)
    : samples(std::move(signal)), sampleRate(__sampleRate__) {}

std::size_t Signal::getSize() const {
  return samples.size();
}

double Signal::getSample(size_t n) const {
  return samples[n];
}

double Signal::getTime(size_t n) const {
  double time = n / sampleRate;

  return time;
}

double Signal::getSampleRate() const {
  return sampleRate;  
}
