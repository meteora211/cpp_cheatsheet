#include <iostream>

using namespace std;

class Printer {
public:
  Printer() {
    cout << this << " ctor called" << endl;
  }
  Printer(const Printer& rhs) {
    cout << this << " copy ctor called" << endl;
  }
  Printer(Printer&& rhs) {
    cout << this << " move ctor called" << endl;
  }
  // XXX: C++11 throw compiler error if copy/move ctor is deleted because of URVO is not guaranteed
  // Printer(const Printer& rhs) = delete;
  // Printer(Printer&& rhs) = delete;
  void print() const {
    cout << "Printer address: " << this << endl;
  }
};

void foo(Printer p) {
  p.print();
}

Printer global_printer{};

// XXX: ambiguous call against foo(Printer p)
// void foo(const Printer& p) {
//   cout << "const Printer& called" << endl;
//   p.print();
// }

// URVO: unamed RVO
Printer bar() {
  // stardard optimization since c++17
  return Printer{};
}

// NRVO: named RVO
Printer nbar() {
  // controled by -fno-elide-constructors
  Printer p{};
  return p;
}

Printer globalRVO() {
  return global_printer;
}

Printer directReturn(Printer p) {
  p.print();
  return p;
}

int main() {
  // XXX: C++11 prints same result with C++17 if -fno-elide-constructors(RVO) is not enabled
  cout << "----foo(Printer p)----" << endl;
  foo(Printer());
  cout << "----bar()----" << endl;
  Printer p = bar();
  cout << "----nbar()----" << endl;
  Printer np = nbar();
  cout << "----foo(bar())----" << endl;
  foo(bar());
  cout << "----globalRVO()----" << endl;
  Printer gp = globalRVO();
  cout << "----directReturn(Printer p)----" << endl;
  Printer drp = directReturn(Printer());
}
