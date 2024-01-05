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
  void print() const {
    cout << "Printer address: " << this << endl;
  }
};

void foo(Printer p) {
  p.print();
}

// XXX: ambiguous call against foo(Printer p)
// void foo(const Printer& p) {
//   cout << "const Printer& called" << endl;
//   p.print();
// }

Printer bar() {
  return Printer{};
}

int main() {
  cout << "---------------" << endl;
  foo(Printer());
  cout << "---------------" << endl;
  Printer p = bar();
  cout << "---------------" << endl;
  foo(bar());
}
