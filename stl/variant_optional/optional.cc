#include <optional>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  {
    // set && get
    optional<int> i1 = 10;
    optional<int> i2 = std::nullopt;
    optional<int> i3 {};
    optional i4{std::vector<int>{1,2,3}};
    // XXX: *i2/*i3 can print value but it's undefined behavior
    cout << "use * to dereference: i1(10): " << *i1
         << " i2(nullopt): " << *i2
         << " i3({}): " << *i3 << endl;

    cout << "use has_value to judge value" << endl;
    if (i1.has_value()) cout << "i1 has: " << i1.value() << endl;
    if (i2) cout << "i2 has: " << i2.value() << endl;
    if (!i3) cout << "i3.value_or: " << i3.value_or(-1) << endl;
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
    optional<int> i3 {};
    cout << "opt<-10> > nullopt: " << (i1 > i2) << endl;
    cout << "nullopt == nullopt: " << (i2 == i3) << endl;
    cout << "nullopt > nullopt: " << (i2 > i3) << endl;
    cout << "opt<-10> == -10: " << (i1 == -10) << endl;
  }
}
