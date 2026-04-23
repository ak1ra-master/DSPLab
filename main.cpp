// main.cpp

// 1. Users input parameters
// 2. Init array with size - n = SampleRate * Duration
// 3. Create a loop over indices
// 3.1. Determine t using the formula - t = n/SampleRate
// 3.2. Determine the value of the sine at time t
// 3.3. Write the received value to each element of the array

#include <iostream>
#include <string>
#include <vector>

#include <cmath>

using namespace std;

vector<double> GenerateSignal(double sampleRate, double frequency, int duration);

int main() {

  double sampleRate, frequency;
  int duration;
  
  // Parameters  
  cout << "Please enter sampleRate: "; cin >> sampleRate;
  cout << "Please enter frequency: "; cin >> frequency;
  cout << "Please enter duration: "; cin >> duration;

  // sine wave generate 
  vector<double> signal = GenerateSignal(sampleRate, frequency, duration);
  
  for (int n = 0; n < signal.size(); n++) {
    printf("n: %d, amplitude: %f \n", n, signal[n]);
  }

  return 0;
}

// Generate a signal based on sampleRate, frequency and duration
vector<double> GenerateSignal(double sampleRate, double frequency, int duration) {

  int signalSize = sampleRate * duration;
  
  vector<double> signal(signalSize);

  for (int n = 0; n < signalSize; n++) {
    signal[n] = sin(2.0 * M_PI * frequency * n / sampleRate);
  }
  
  return signal;
}
