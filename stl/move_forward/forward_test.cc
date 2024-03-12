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
  print(t);                     // t=int& -> lref, t=int& && -> lref, t=int&& -> lref
  print(std::forward<T>(t));    // t=int& -> lref, t=int& && -> lref, t=int&& -> rref
  print(std::forward<T&>(t));   // t=int& -> lref, t=int& && -> lref, t=int&& -> lref
  print(std::forward<T&&>(t));  // t=int& -> lref, t=int& && -> lref, t=int&& -> rref
  print(std::move(t));          // t=int& -> rref, t=int& && -> rref, t=int&& -> rref
}

template<typename T>
void test_print_value(T t) {
  print(t);                     // t=int -> lref, t=int& -> lref, t=int&& -> lref
  print(std::forward<T>(t));    // t=int -> rref, t=int& -> rref, t=int&& -> rref
  print(std::forward<T&>(t));   // t=int -> lref, t=int& -> lref, t=int&& -> lref
  print(std::forward<T&&>(t));  // t=int -> rref, t=int& -> rref, t=int&& -> rref
  print(std::move(t));          // t=int -> rref, t=int& -> rref, t=int&& -> rref
}

template<typename T>
struct TestPrint {
  void call(T t) {
    print<T>(std::forward<T>(t));    // t=int -> rref, t=int& -> lref, t=int&& -> rref
  }
};

int main() {
  int x = 1;
  int& xr = x;

  test_print_common(x);
  test_print_common(xr);
  test_print_common(std::move(x));

  test_print_value(x);
  test_print_value(xr);
  test_print_value(std::move(x));

  TestPrint<decltype(x)>().call(x);
  TestPrint<decltype(xr)>().call(xr);
  TestPrint<decltype(std::move(x))>().call(std::move(x));
}
