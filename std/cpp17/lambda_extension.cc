#include <iostream>
#include <string>

class Foo {
public:
  void foo() {
    auto l1 = [this] { std::cout << "l1: " << name << std::endl;};
    auto l2 = [=] { std::cout << "l2: " << name << std::endl;};
    auto l3 = [&] { std::cout << "l3: " << name << std::endl;};
    auto l4 = [thisCopy = *this] { std::cout << "l4: " << thisCopy.name << std::endl;};
    // XXX: new in c++17
    auto l5 = [*this] { std::cout << "l5: " << name << std::endl;};
    l1(); l2(); l3(); l4(); l5();
  }
  std::string name;
};

int main() {
  {
    // implicit constexpr
    auto squared1 = [](int val) { return val * val; };
    // same with squared1
    auto squared2 = [](int val) constexpr { return val * val; };
    // Different with squared1. squared1 is able to call during compilation
    // and the instance is initialized at runtime where squared3 means it is
    // initialized in compilation.
    constexpr auto squared3 = [](int val) { return val * val; };
    static_assert(squared1(5) == 25);
    static_assert(squared2(5) == 25);
    static_assert(squared3(5) == 25);
  }
  {
    // this pointer
    Foo f{"test"};
    f.foo();
  }
}
