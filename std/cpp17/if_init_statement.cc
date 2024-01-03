#include <iostream>

struct RAIIPrinter {
  RAIIPrinter() {
    std::cout << "RAII Printer ctor" << std::endl;
  }
  ~RAIIPrinter() {
    std::cout << "RAII Printer dtor" << std::endl;
  }
};

int main() {
  std::cout << "before cond" << std::endl;
  if (auto p = RAIIPrinter(); true) {
    std::cout << "condition body" << std::endl;
  }
  std::cout << "after cond" << std::endl;
}
