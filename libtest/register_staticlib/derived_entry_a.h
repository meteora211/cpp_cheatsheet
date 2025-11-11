#pragma once
#include <iostream>
#include "entry.h"

class DerivedEntryA : public BaseEntry {
 public:
  void print() override;
};
