#include <iostream>

template <auto N> class S {};

// template<auto... VS>
// struct HeteroList {};

// template<auto V1, decltype(V1)... VS>
// struct HomoList {};

template <auto... VS> class HeteroValueList {};
template <auto V1, decltype(V1)... VS> class HomoValueList {};
// XXX: same with above and vals4 also not fail in below version.
// template <int... VS> class HomoValueList {};

template <auto Sep = ' ', typename First, typename... Args>
void print(const First& f, const Args&... args) {
  std::cout << f;
  auto printer = [](const auto& arg){
    std::cout << Sep << arg;
  };
  (..., printer(args));
  std::cout << std::endl;
}

int main() {
  S<42> s1;  // N -> int
  S<'a'> s2; // N -> char
  // s<2.5> s3; // error, double can not be template param

  HeteroValueList<1, 2, 3> vals1;      // ok
  HeteroValueList<1, 'a', true> vals2; // ok

  HomoValueList<1, 2, 3> vals3;      // ok
  // XXX: vals4 has no compile error, not sure why
  HomoValueList<1, 'a', true> vals4; // error

  print(1, "hello", 2);
  print<'-'>(1, "hello", 2);
}
