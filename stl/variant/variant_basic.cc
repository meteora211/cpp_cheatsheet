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
  // construct
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
  cout << "0) " << get<int>(var0) << "\n"
       << "1) " << get<0>(var1) << "\n"
       << "2) " << get<1>(var2) << "\n"
       << "3) " << get<string>(var3) << "\n"
       << "4) " << get<1>(var4) << "\n"
       << "5) " << get<string>(var5) << "\n"
       << "6) " << get<vector<int>>(var6) << "\n";
}
