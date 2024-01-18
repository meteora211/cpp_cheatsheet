#include <charconv> // from_chars
#include <iostream>
#include <optional>
#include <string_view>
#include <vector>
#include <string>

using namespace std;

// RULE: don't return string when your return type is string_view

template <typename T>
void printElems(const T &coll, std::string_view prefix = {}) {
  for (const auto &elem : coll) {
    if (prefix.data()) { // XXX: avoid nullptr
      std::cout << prefix << " ";
    }
    std::cout << elem << "\n";
  }
}

optional<int> asInt(string_view sv) {
  int val;
  if (auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), val);
      ec != std::errc{}) {
    return std::nullopt;
  }
  return val;
}

std::string retString() {
  return std::string{"temp string"};
}

class Person {
public:
  Person(string name) : name_{std::move(name)} {}
  const string& getName() const {
    return name_;
  }
  // XXX: DON'T
  // Person(string_view name) : name_{name} {}
  // XXX: DON'T
  // Person(string name) {}
  // string_view getName() const {
  //   return name_;
  // }

private:
  string name_;
};

int main() {
  // examples
  printElems<vector<int>>({1, 2, 3}, "elem:");

  for (auto s : {"42", " 077", "hello", "0x33"}) {
    std::optional<int> oi = asInt(s);
    if (oi) {
      std::cout << "convert " << s << " to int: " << oi.value() << "\n";
    } else {
      std::cout << "can't convert " << s << " to int"
                << "\n";
    }
  }

  // dangers
  const string& s1 = retString(); // ok
  // string& s1 = retString(); // error
  string&& s2 = retString(); // ok

  // XXX: dangerous behavior when assign temp return value to a string_view
  // and note the clang warning on following code, which equals to:
  // const char* p = retString().c_str();
  string_view sv = retString();
}
