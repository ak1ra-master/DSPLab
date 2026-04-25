#pragma once

#include "../Signal/Signal.h"
#include <vector>

class Generator {
public:
  virtual Signal getSignal() = 0;
  virtual ~Generator() = default; 
};
