#include <functional>
#include <iostream>
#include <string>
#include <type_traits>

template <typename T> std::string asString(T in) {
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
  if constexpr (sizeof(int) > 4)
    return 42;
}

template <typename T> constexpr auto foo(const T &val) {
  if constexpr (std::is_integral_v<T>) {
    if constexpr (T{} < 10) {
      return val * 2;
    }
  }
  return val;
}

template <typename T> void foo2(const T x) {
  if constexpr (auto obj = foo(x); std::is_same_v<T, decltype(obj)>) {
    std::cout << "foo2: same type with foo" << std::endl;
  } else {
    std::cout << "foo2: diff type with foo" << std::endl;
  }
}

template <typename Callable, typename... Args>
decltype(auto) call(Callable cb, Args &&...args) {
  if constexpr (std::is_void_v<std::invoke_result_t<Callable, Args...>>) {
    cb(std::forward<Args>(args)...);
    // some other operations;
    return;
  } else {
    // some other operations;
    return cb(std::forward<Args>(args)...);
  }
}

// replace tag dispatching
void foobar_impl(int x, std::true_type) {
  std::cout << "foobar true_type: " << x * 2 << std::endl;
}
void foobar_impl(int x, std::false_type) {
  std::cout << "foobar false_type: " << x << std::endl;
}
void foobar(int x) {
  // some type_traits to dispatching
  foobar_impl(x, std::true_type{});
}
// using if constexpr, have no relation with above tag dispatching demo. just to
// show.
template <int X> void foobar_constexpr() {
  if constexpr (X % 2 == 0) {
    std::cout << "foobar_constexpr true_type: " << X * 2 << std::endl;
  } else {
    std::cout << "foobar_constexpr false_type: " << X << std::endl;
  }
}

int main() {
  std::cout << asString("hello") << std::endl;
  std::cout << asString(42) << std::endl;
  std::cout << asString(std::string("hello")) << std::endl;
  std::cout << "foo(\"hi\"): " << foo("hi") << " foo(42): " << foo(42)
            << std::endl;

  std::cout << call(foo<int>, 42) << std::endl;

  foobar_constexpr<42>();
  foobar(42);

  foo2(42);

  if constexpr (std::is_void_v<void>) {
    static_assert(std::is_void_v<void>);
  } else {
    // XXX: compile error. Both if and then branch should be valid in if
    // constexpr even if it will be discard.

    // static_assert(!std::is_void_v<void>);
  }
}
