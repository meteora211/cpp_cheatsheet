#include <iostream>

template<typename T>
void print(T& t) {
  std::cout << "lref value" << std::endl;
}

template<typename T>
void print(T&& t) {
  std::cout << "rref value" << std::endl;
}


template<typename T>
void test_print_common(T&& t) {
  print<T>(t);                  // T=int -> lref, T=int& -> lref, T=int&& -> lref
  print(std::forward<T>(t));    // T=int -> lref, T=int& -> lref, T=int&& -> rref
  print(std::forward<T&>(t));   // T=int -> lref, T=int& -> lref, T=int&& -> lref
  print(std::forward<T&&>(t));  // T=int -> lref, T=int& -> lref, T=int&& -> rref
  print(std::move(t));          // T=int -> rref, T=int& -> rref, T=int&& -> rref
}

template<typename T>
void test_print_value(T t) {
  print<T>(t);                  // T=int -> lref, T=int& -> lref, T=int&& -> lref
  print(std::forward<T>(t));    // T=int -> rref, T=int& -> rref, T=int&& -> rref
  print(std::forward<T&>(t));   // T=int -> lref, T=int& -> lref, T=int&& -> lref
  print(std::forward<T&&>(t));  // T=int -> rref, T=int& -> rref, T=int&& -> rref
  print(std::move(t));          // T=int -> rref, T=int& -> rref, T=int&& -> rref
}

int main() {
  int x = 1;
  int& xr = x;

  test_print_common(x);
  test_print_common(xr);
  test_print_common(std::move(x));

  test_print_value(x);
  test_print_value(xr);
  test_print_value(std::move(x));
}
