#include <functional>
#include <type_traits>
#include <iostream>
#include "print_helper.h"

template<typename Callable>
class functor_class {
public:
  functor_class(Callable func) : func_(func) {}

  template<typename... Args>
  decltype(auto) operator()(Args &&... args) {
    return func_(std::forward<Args>(args)...);
  }

private:
  Callable func_;
};

int test_func(PrintHelper&& a) {
  std::cout << "test_func called" << std::endl;
  return 1;
}

int main() {
  auto ret = functor_class(test_func)(PrintHelper{});
  std::cout << "func returns: " << ret << std::endl;
}
