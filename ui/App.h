#pragma once
#include "../core/Signal/Signal.h"
#include "../core/Processing/STFT.h"
#include <vector>
#include <complex>
#include <algorithm>

enum class SignalType { Sine, Cosine };
enum class ProcessingMode { None, FFT, STFT };

class App
{
public:
    void run();
private:
    SignalType     currentSignal = SignalType::Sine;
    ProcessingMode currentMode  = ProcessingMode::None;

    Signal                            cachedSignal;
    std::vector<std::complex<double>> cachedFFT;
    STFTResult                        cachedSTFT;
    bool fftDirty  = true;
    bool stftDirty = true;

    Signal makeSignal(SignalType type);
    void updateInput();
    void drawUI();
    void drawSignal();
    void drawFFT();
    void drawSTFT();
};
