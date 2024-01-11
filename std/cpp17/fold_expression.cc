#include <type_traits>
#include <iostream>

// 1. typename... Args
template <typename... Args>
// 2. Args... args
auto foldsum(Args... args) {
// 3. unfold
  return (... + args);
}

// XXX: folding forms:
// left: (args op ... [op init]) => (arg3 op (arg2 op (arg1 op init)))
// eg:   (args -  ...  -  10) // args = 1,2,3
// process:
// (args - ... - 10)           // args = 1,2,3
// (args - ... - (1 - 10))     // args = 2,3
// (args - ... (2 - (1 - 10))) // args = 3
// => (3 - (2 - (1 - 10)))

// right: ([init op] ... op args) => (((init op arg1) op arg2) op arg3)
// eg:    ( 10   -   ... -  args) // args = 1,2,3
// process:
// (10 - ... - args)             // args = 1,2,3
// ((10 - 1) - ... - args)       // args = 2,3
// (((10 - 1) - 2) - ... - args) // args = 3
// => (((10 - 1) - 2) - 3)

template<int... N>
constexpr int leftfold = (N - ... - 10);

template<int... N>
constexpr int rightfold = (10 - ... - N);

// example
template<typename T>
const T& spaceBefore(const T& arg) {
  std::cout << " ";
  return arg;
}

template<typename First, typename... Args>
void print(const First& f, const Args&... args) {
  std::cout << f;
  (std::cout << ... << spaceBefore(args)) << std::endl;
}

int main() {
  static_assert(leftfold<1,2,3> == -8);
  static_assert(rightfold<1,2,3> == 4);
  print(1,2,3);
}
