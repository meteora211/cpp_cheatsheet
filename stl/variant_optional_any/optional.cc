#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <complex>

using namespace std;

int main() {
  {
    // set && get
    optional<int> i1 = 10;
    optional<int> i2 = std::nullopt;
    optional<int> i3{};
    optional i4{std::vector<int>{1, 2, 3}};
    // XXX: *i2/*i3 can print value but it's undefined behavior
    cout << "use * to dereference: i1(10): " << *i1 << " i2(nullopt): " << *i2
         << " i3({}): " << *i3 << endl;

    cout << "use has_value to judge value" << endl;
    if (i1.has_value())
      cout << "i1 has: " << i1.value() << endl;
    if (i2)
      cout << "i2 has: " << i2.value() << endl;
    if (!i3)
      cout << "i3.value_or: " << i3.value_or(-1) << endl;
    // XXX: get invalid value got coredump
    // cout << i2.value() << endl;

    cout << "use -> to get member:" << endl;
    cout << "i4 size: " << i4->size() << endl;
  }
  {
    // value && value_or
    optional<int> i2 = std::nullopt;
    cout << "value() return reference, value_or return value" << endl;
    // Following is better than value_or which avoid an copy.
    cout << (i2 ? i2.value() : -1) << endl;
  }
  {
    // compare
    // has_value > nullopt == nullopt
    optional<int> i1 = -10;
    optional<int> i2 = std::nullopt;
    optional<int> i3{};
    cout << "opt<-10> > nullopt: " << (i1 > i2) << endl;
    cout << "nullopt == nullopt: " << (i2 == i3) << endl;
    cout << "nullopt > nullopt: " << (i2 > i3) << endl;
    cout << "opt<-10> == -10: " << (i1 == -10) << endl;
  }
  {
    // changing value
    std::optional<std::complex<double>> oc; // has no value
    std::optional oi{77};                   // optional<int> with 77

    oc = 42; // complex{42, 0}
    oc = {9.9, 4.4}; // complex{9.9, 4.4}
    oc = oi; // complex{77, 0}
    oc = std::nullopt; // no value
    oc.emplace(5, 7); // complex{5, 7}
    oc.reset(); // no value
    oc = {}; // no value
    oc = 1; // {1, 0}
    // *operator returns reference which can also set value, but deref an nullopt cause undefined behavior
    *oc = 2; // {2, 0}
  }
  {
    // move senmatics
    std::optional<std::string> os;
    std::string s1 {"long long long string"};
    os = std::move(s1); // move
    std::string s2 = *os; // copy
    std::string s3 = std::move(*os); // copy
  }
  {
    // spectial
    std::optional<bool> ob {false};
    std::optional<int*> on {nullptr};
    // use ob == false or on == nullptr to judge the condition
    if (ob) cout << "bool(optional<bool>{false}) is true." << endl;
    if (on) cout << "bool(optional<int*>{nullptr}) is true." << endl;
  }
}
