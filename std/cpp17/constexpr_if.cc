#include <iostream>
#include <string>
#include <type_traits>
#include <functional>

template<typename T>
std::string asString(T in) {
  if constexpr (std::is_same_v<T, std::string>) {
    return in;
  } else if constexpr (std::is_arithmetic_v<T>) {
    return std::to_string(in);
  } else {
    return std::string(in);
  }
}

// return type differ by constexpr
auto bar() {
  // return type might be int or void
  if constexpr (sizeof(int) > 4) return 42;
}

template<typename T>
constexpr auto foo(const T& val) {
  if constexpr(std::is_integral_v<T>) {
    if constexpr (T{} < 10) {
      return val * 2;
    }
  }
  return val;
}

template<typename Callable, typename... Args>
decltype(auto) call(Callable cb, Args&&... args) {
  if constexpr (std::is_void_v<std::invoke_result_t<Callable, Args...>>) {
    cb(std::forward<Args>(args)...);
    // some other operations;
    return;
  } else {
    // some other operations;
    return cb(std::forward<Args>(args)...);
  }
}

int main() {
  std::cout << asString("hello") << std::endl;
  std::cout << asString(42) << std::endl;
  std::cout << asString(std::string("hello")) << std::endl;
  std::cout << "foo(\"hi\"): " << foo("hi") << " foo(42): " << foo(42) << std::endl;
  std::cout << call(foo<int>, 42) << std::endl;
}
