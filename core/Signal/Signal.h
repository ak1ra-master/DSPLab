#include <cstddef>
#include <vector>
#include <cstdint>

class Signal {
private:
  std::vector<double> samples;
  double sampleRate;
  
public:
  Signal(std::vector<double> &&signal, double __sampleRate__);

  std::size_t getSize() const;
  double getSample(int n) const;
  double getTime(int n) const;
};
