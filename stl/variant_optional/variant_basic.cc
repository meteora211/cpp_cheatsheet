#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <cassert>
using namespace std;

// helper function
auto &operator<<(auto &out, const vector<int> &v) {
  out << "{ ";
  for (int e : v)
    out << e << ' ';
  return out << "}";
}
// variant: a type-safe union

int main() {
  {
    // construct and get
    // value-initializes first alternative
    variant<int, string> var0;
    assert(holds_alternative<int>(var0) and var0.index() == 0 and
           get<int>(var0) == 0);

    // initializes first alternative with int == 42;
    variant<int, string> var1{42};
    assert(var1.index() == 0);

    // initializes second alternative with std::string{"STR"};
    variant<int, string> var2{"STR"};
    assert(var2.index() == 1);

    // XXX: pass more than one value for initialization, use in_place_type and in_place_index
    // initializes first alternative with std::string{4, 'A'};
    std::variant<std::string, vector<int>, float> var3{in_place_type<string>, 4,
                                                       'A'};
    assert(var3.index() == 0);

    // initializes second alternative with std::vector{1,2,3};
    std::variant<std::string, vector<int>, char> var4{in_place_type<vector<int>>,
                                                      {1, 2, 3}};
    assert(var4.index() == 1);

    // initializes first alternative with std::string{"ABCDE", 3};
    std::variant<std::string, vector<int>, bool> var5{in_place_index<0>, "ABCDE",
                                                      3};
    assert(var5.index() == 0);

    // initializes second alternative with std::vector(4, 42);
    std::variant<std::string, vector<int>, char> var6{in_place_index<1>, 4, 42};
    assert(var6.index() == 1);

    // get
    // XXX: get invalid index cause an runtime error: "std::get: wrong index for variant"
    cout << "0) " << get<int>(var0) << "\n"
         << "1) " << get<0>(var1) << "\n"
         << "2) " << get<1>(var2) << "\n"
         << "3) " << get<string>(var3) << "\n"
         << "4) " << get<1>(var4) << "\n"
         << "5) " << get<string>(var5) << "\n"
         << "6) " << get<vector<int>>(var6) << "\n";

    std::variant<int, int, std::string> var7;
    // auto a = std::get<double>(var7); // error: no double
    // auto a = std::get<int>(var7); // error: two int
    // auto a = std::get<4>(var7); // error: out of box
    // auto a = std::get<std::string>(var7); // error: string not set
    // auto a = std::get<1>(var7); // error: index 1 not set

    // get_if
    if (auto ip = get_if<1>(&var7); ip == nullptr) {
      std::cout << "alternative with index 1 not set\n";
    }
  }
  {
    // changing value
    std::variant<int, int, std::string> var; // index = 0, val = 0
    var = "hello"; // index = 2; val = "hello"
    var.emplace<1>(42); // index = 1, val = 42
  }
}
