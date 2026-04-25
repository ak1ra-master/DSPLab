#pragma once

#include "../core/Signal/Signal.h"
#include "../core/Generators/SineGenerator.h"

#include <iostream>

Signal createSineSignalFromUser();

void printSignal(const Signal& signal);
