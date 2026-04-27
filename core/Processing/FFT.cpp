#include "FFT.h"
#include <cmath>
#include <cstddef>

static std::vector<std::complex<double_t>>
FFT_recursive(const std::vector<std::complex<double_t>>& data);

static size_t nextPow2(size_t n);

std::vector<std::complex<double_t>> FFT(const Signal &signal) {
  size_t N = signal.getSize();

  N = nextPow2(N);
  
   std::vector<std::complex<double_t>> complexSignal(N);
   for(size_t n = 0; n < signal.getSize(); n++){
     complexSignal[n] = std::complex<double_t>(signal.getSample(n), 0.0);
   }

   for (size_t n = signal.getSize(); n < N; n++) {
    complexSignal[n] = std::complex<double>(0.0, 0.0);
   }   

   return FFT_recursive(complexSignal);   
}

static size_t nextPow2(size_t n){
   size_t p = 1;
   while(p < n){
     p *= 2;
   }
   return p;
}

static std::vector<std::complex<double_t>>
FFT_recursive(const std::vector<std::complex<double_t>>& data){
  size_t N = data.size();
   
  if(N == 1) return data;

  std::vector<std::complex<double_t>> even(N / 2);
  std::vector<std::complex<double_t>> odd(N / 2);
  for(size_t n = 0; n < N / 2; n++){
     even[n] = data[n * 2];
     odd[n] = data[(n * 2) + 1];
     
  }

  std::vector<std::complex<double_t>> E = FFT_recursive(even);
  std::vector<std::complex<double_t>> O = FFT_recursive(odd);
  std::vector<std::complex<double_t>> result(N);
  for (size_t k = 0; k < N / 2; k++) {
    double_t angle = -2.0 * M_PI * k / N;
    std::complex<double_t> W(std::cos(angle), std::sin(angle));

    result[k] = E[k] + W * O[k];
    result[k+N/2] = E[k] - W * O[k];
  }
  return result;
}    
