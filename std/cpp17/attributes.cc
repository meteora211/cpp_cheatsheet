#include <iostream>
#include <string>

[[nodiscard]] bool foo(int x) {
  return x > 0;
}

void foo(int val, [[maybe_unused]] std::string msg) {
  val = 0;
}

namespace [[deprecated]] draftapi {
  enum class City {
    Berlin = 0,
    Mumbai = 1,
    Bombay [[deprecated]] = Mumbai,
  };

  void foo(City c) {
    std::cout << "draft foo: " << int(c) << std::endl;
  }
}

void bar(int val) {
  switch (val) {
    case 1:
      std::cout << "case1" << std::endl;
      [[fallthrough]];
    case 2:
      std::cout << "case2" << std::endl;
      break;
    default:
      std::cout << "default" << std::endl;
      break;
  }
}

int main() {
  // XXX: Return value not used. See compiler warning.
  foo(5);
  foo(5, "test");
  bar(1);
  draftapi::foo(draftapi::City::Bombay);
}
