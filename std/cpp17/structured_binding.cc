#include <iostream>
#include <string>

struct MyStruct {
  int i = 0;
  std::string s;
};

int main() {
  {
    // Basic usage
    MyStruct ms{42, "hello"};
    auto [u, v] = ms;
    // auto e = ms;
    // aliasname u = e.i;
    // aliasname v = e.s;
    ms.i = 77;
    std::cout << "[CASE1] ms.i = " << ms.i << " u = " << u << std::endl;
    std::cout << "[CASE1] address of ms.i: " << &ms.i << " address of u: " << &u
              << std::endl;
    std::cout << "address of v: " << &(reinterpret_cast<MyStruct *>(&u)->s)
              << " address of v: " << &v << std::endl;
  }
  {
    // Reference usage
    MyStruct ms{42, "hello"};
    auto &[u, v] = ms;
    // auto e = ms;
    // aliasname u = e.i;
    // aliasname v = e.s;
    ms.i = 77;
    std::cout << "[CASE2] ms.i = " << ms.i << " u = " << u << std::endl;
    std::cout << "[CASE2] address of ms.i: " << &ms.i << " address of u: " << &u
              << std::endl;
  }
  {
    // Move statement
    MyStruct ms{42, "hello"};
    MyStruct ms2{42, "hello"};
    auto &&[u, v] = std::move(ms);
    auto [u2, v2] = std::move(ms2);

    // ms.s still print hello, but is an unspecified value
    std::cout << "ms.s: " << ms.s << "\n";
    std::cout << "v: " << v << "\n";

    // ms2.s is invalid
    std::cout << "ms2.s: " << ms2.s << "\n";
    std::cout << "v2: " << v2 << "\n";
  }
  {
    // Binding an array
    int a[2] = { 1, 2 };
    auto [x, y] = a;
    auto &[xr, yr] = a;
    std::cout << x << y << xr << yr << "\n";
  }

  {
    // Binding to data member
    struct B {
      int a = 1;
      int b = 2;
    };
    struct D1 : B {};
    auto [x, y] = D1{}; // OK

    struct D2 : B {
      int c = 3;
    };
    // auto [i, j, k] = D2{}; // Compile-Time ERROR

    struct S {
      mutable int x1 : 2;
      volatile double y1;
    };
    auto f = []() { return S{1, 2}; };
    const auto [xn, yn] = f();
    xn = -2; // OK
    // yn = -2; // Error: yn is const-qualified
    std::cout << xn << " " << yn << "\n";
  }
  {
    // Binding to tuple like type
  }
}
