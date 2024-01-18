#include <string_view>
#include <string>
#include <iostream>

using namespace std;

int main() {
  {
    string_view sv{"hello"};
    cout << "string_view{'hello'}: " << sv << "\n"
         << ".data(): " << sv.data() << "\n"
         << ".size(): " << sv.size() << "\n"
         << ".at(3): " << sv.at(3) << "\n"
         << "[3]: " << sv[3] << "\n";
  }
  {
    string_view sv;
    auto p = sv.data();
    cout << (p == nullptr) << endl; // nullptr
    // XXX: following code cause cout corrupt, not sure why
    // cout << sv.data() << endl; // nullptr
  }
  {
    // constexpr
    constexpr string_view hello{"hello world"};
  }
  {
    // modify
    string_view s1 = "hello";
    string_view s2 = "world";
    s1.swap(s2);
    cout << s1 << s2 << endl; // worldhello
    s2 = s1;
    cout << s1 << s2 << endl; // helloworld

    string_view sv = "I like my kindergarten";
    sv.remove_prefix(2);
    sv.remove_suffix(8);
    cout << sv << endl; // like my kind
  }
}
