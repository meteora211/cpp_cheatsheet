#pragma once
#include <iostream>

struct PrintHelper {
  PrintHelper() {
    std::cout << "print: " << this << " ctor call" << std::endl;
  }
  PrintHelper(const PrintHelper&) {
    ++cp_ctor_count;
    std::cout << "print: " << this << " copy call " << cp_ctor_count << std::endl;
  }
  PrintHelper(PrintHelper&&) {
    ++mv_ctor_count;
    std::cout << "print: " << this << " move call " << mv_ctor_count << std::endl;
  }
  PrintHelper& operator=(const PrintHelper&) {
    ++cp_asig_count;
    std::cout << "print: " << this << " copy assign call " << cp_asig_count << std::endl;
    return *this;
  }
  PrintHelper& operator=(PrintHelper&&) {
    ++mv_asig_count;
    std::cout << "print: " << this << " move assign call" << mv_asig_count << std::endl;
    return *this;
  }
  ~PrintHelper() {
    std::cout << "print: " << this << " dtor call" << std::endl;
  }
  void print_address() {
    std::cout << this << std::endl;
  }
  static inline int cp_ctor_count = 0;
  static inline int mv_ctor_count = 0;
  static inline int cp_asig_count = 0;
  static inline int mv_asig_count = 0;
};
