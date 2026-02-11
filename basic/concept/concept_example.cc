#include <format>
#include <ranges>
#include <concepts>
#include <print>
#include <vector>
#include <set>

struct Foo {
  static void foo() {
    std::println("foo");
  }
};

template<typename T>
concept CFoo = requires (T) {
  T::foo();
};


template<typename CollT>
concept HasPushBack = requires(CollT c, CollT::value_type v) {
  c.push_back(v);
};

// concept constraint on type
// equivalents:
// template<HasPushBack Coll, typename T> void add(Coll& coll, const T& val);
// template<typename CollT, typename T> requires HasPushBack<CollT> void add(CollT& coll, const T& val);
void add(HasPushBack auto& coll, const auto& val) {
  coll.push_back(val);
}

void add(auto& coll, const auto& val) {
  coll.insert(val);
}

// println on ranges needs gcc15
void printcoll(const auto& c) {
  for (const auto& v: c) std::print("{} ", v);
  std::println("");
}

int main() {
  static_assert(CFoo<Foo>);
  Foo::foo();

  std::vector v{1,2,3};
  std::set s{1,2,3};
  add(v, 1); printcoll(v);
  add(s, 1); printcoll(s);
}
