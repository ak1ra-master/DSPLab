#include "SignalOps.h"
#include <cmath>

Signal Addition(const Signal& signal_1, const Signal& signal_2) {
  
  if (signal_1.getSampleRate() == signal_2.getSampleRate()) {

    size_t size = std::max(signal_1.getSize(), signal_2.getSize());
    std::vector<double_t> newSamples(size);

    size_t size1 = signal_1.getSize();
    size_t size2 = signal_2.getSize();
    
    for(size_t n = 0; n < size; n++){
      double_t in1 = (n < size1) ? signal_1.getSample(n) : 0;
      double_t in2 = (n < size2) ? signal_2.getSample(n) : 0;
      
      newSamples[n] = in1 + in2;
    }
    
    Signal newSignal(std::move(newSamples), signal_1.getSampleRate());

    return newSignal;
    
  } else { 
    throw std::runtime_error("SampleRate mismatch");
  }
}
