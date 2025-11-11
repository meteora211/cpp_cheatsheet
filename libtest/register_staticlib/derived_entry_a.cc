#include "derived_entry_a.h"
#include "register.h"

void DerivedEntryA::print() {
  std::cout << "DerivedEntry1" << std::endl;
}

static DerivedEntryA derive_a;

static bool ret = Register::reg("derive_a", derive_a);

