#include <array>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

struct MyStruct {
  int i = 0;
  std::string s;
};

class TupleLike {
public:
  TupleLike(std::string name, int val) : name{name}, val{val} {}
  int getValue() const { return val; }
  std::string getName() const { return name; }
  // api for writer
  int &getValue() { return val; }
  std::string &getName() { return name; }

private:
  std::string name;
  int val;
};

// tuple-like api
// getter with const
// XXX: decltype(auto) to return the reference:
// https://zhuanlan.zhihu.com/p/404831186
template <std::size_t I> decltype(auto) get(const TupleLike &t) {
  static_assert(I < 2);
  if constexpr (I == 0) {
    return t.getName();
  } else {
    return t.getValue();
  }
}
// getter with non-const
template <std::size_t I> decltype(auto) get(TupleLike &t) {
  static_assert(I < 2);
  if constexpr (I == 0) {
    return t.getName();
  } else {
    return t.getValue();
  }
}
// tuple_size
template <> struct std::tuple_size<TupleLike> {
  static constexpr int value = 2;
};
// tuple_element
template <> struct std::tuple_element<1, TupleLike> {
  using type = int; // last attr is int;
};
template <std::size_t Idx> struct std::tuple_element<Idx, TupleLike> {
  using type = std::string; // the other attrs is string
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
    int a[2] = {1, 2};
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

    // array
    std::array<int, 4> stdarr{1, 2, 3, 4};
    auto &[i, j, k, l] = stdarr;
    i += 10; // modifies array[0]

    // pair
    std::map<std::string, int> coll;
    if (auto [pos, ok] = coll.insert({"new", 42}); ok) {
      std::cout << "inserted!" << std::endl;
    }

    // tuple
    std::tuple<std::string, int, std::string, int> stdtu{"a", 1, "b", 2};
    auto [a, av, b, bv] = stdtu;
    // assign new values to existing variables by std::tie
    std::tie(a, av, b, bv) = stdtu;
  }
  {
    // Tuple like API:

    // REF: https://en.cppreference.com/w/cpp/utility/tuple/tuple-like
    // tuple-like types implement the tuple protocol, i.e., such types can
    // be used with std::get, std::tuple_element and std::tuple_size. Elements
    // of tuple-like types can be bound with structured binding.
    TupleLike t("tuple", 2);
    auto &[name, val] = t;
    std::cout << "Name: " << name << " value: " << val << std::endl;
    name = "new tuple";
    val = 3;
    std::cout << "Name: " << t.getName() << " value: " << t.getValue()
              << std::endl;
  }
}
