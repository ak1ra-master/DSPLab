#pragma once

#include "../Signal/Signal.h"

#include <complex>
#include <vector>
#include <cmath>
#include <cstddef>
#include <math.h>
#include <bit>


std::vector<std::complex<double>> FFT(const Signal& signal);
