#include <iostream>

class Base {
public:
  void a() { std::cout << "base a" << std::endl;}
  void b() { std::cout << "base b" << std::endl;}
  void c() { std::cout << "base c" << std::endl;}
};

// note private derive
class Derived : private Base {
public:
  using Base::a, Base::b, Base::c;
};

int main() {
  Derived().a();
  Derived().b();
  Derived().c();
}
