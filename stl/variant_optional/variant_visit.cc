#include <iostream>
#include <string>
#include <variant>
#include <vector>
using namespace std;

// simplified version:
// visit(lambda, variant)
//         |
//        \/
// lambda(std::get<indices>(variant))
using var_t = variant<int, long, double, string>;

// helper func
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

int main() {
  vector<var_t> vec = {10, 10l, 1.5, "hello"};

  for (auto& v: vec) {
    visit([](auto&& arg){ cout << arg; }, v);
    // double v
    auto w = visit([](auto&& arg) -> var_t { return arg + arg;}, v);
    // visitor pattern
    visit([](auto&& arg) {
      using T = decay_t<decltype(arg)>;
      if constexpr (is_same_v<T, int>) {
        cout << " int double to: " << arg << "\n";
      } else if constexpr (is_same_v<T, long>) {
        cout << " long double to: " << arg << "\n";
      } else if constexpr (is_same_v<T, double>) {
        cout << " double double to: " << arg << "\n";
      } else if constexpr (is_same_v<T, string>) {
        cout << " string double to: " << arg << "\n";
      }
    }, w);
  }

  for (auto& v: vec) {
    visit(overloaded{
      [](auto arg){ cout << " default visit: " << arg << "\n"; },
      [](double arg){ cout << " double visit: " << arg << "\n"; },
      [](long arg){ cout << " long visit: " << arg << "\n"; },
      [](const string& arg){ cout << " string visit: " << arg << "\n"; },
    }, v);
  }
}
